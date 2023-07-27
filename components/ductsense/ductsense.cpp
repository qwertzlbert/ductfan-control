#include "ductsense.hpp"

namespace ductfan {

StatefullButton::StatefullButton(button_config_t &button_config_t) {
  m_button = iot_button_create(&button_config_t);
  m_state = 0;
  m_last_event = BUTTON_NONE_PRESS;
}

int StatefullButton::get_current_value() {

  button_event_t b_event = iot_button_get_event(m_button);

  bool change_event = false;

  // BUTTON_SINGLE_CLICK will change state
  // BUTTON_DOUBLE_CLICK will do nothing
  // BUTTON_PRESS_REPEAT needs to be counted to check if internal state needs to
  // change
  switch (b_event) {
  case BUTTON_PRESS_DOWN:
    if (m_last_event != b_event) {
      m_last_event = b_event;
      change_event = true;
      // should be moved to logging mechanism
      printf("PRESSED DOWN\n");
    }
    break;

  case BUTTON_PRESS_UP:
    if (m_last_event != b_event) {
      m_last_event = b_event;
      // should be moved to logging mechanism
      printf("PRESSED UP\n");
    }
    break;

  default:
    break;
  }

  // will cycle state between 0 and 1
  if (change_event) {
    m_state = (m_state + 1) % 2;
  }

  return m_state;
}

FanTachoSensor::FanTachoSensor(int gpio_pin, int max_speed) {

  m_speed = 0;
  m_pin_number = gpio_pin;
  m_max_speed = max_speed;
  m_pcnt_unit = NULL;
  m_pcnt_chan = NULL;
  m_taskHandle = NULL;

  pcnt_unit_config_t unit_config = {
      .low_limit = -1,
      .high_limit = m_max_speed,
  };

  ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &m_pcnt_unit));

  pcnt_chan_config_t chan_a_config = {
      .edge_gpio_num = m_pin_number,
      .level_gpio_num = -1,
  };

  ESP_ERROR_CHECK(pcnt_new_channel(m_pcnt_unit, &chan_a_config, &m_pcnt_chan));

  ESP_ERROR_CHECK(
      pcnt_channel_set_edge_action(m_pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_HOLD,
                                   PCNT_CHANNEL_EDGE_ACTION_INCREASE));
}

void FanTachoSensor::update_speed_task() {
  static portMUX_TYPE my_spinlock = portMUX_INITIALIZER_UNLOCKED;

  int pulse_count = 0;

  printf("Enable clear and start counter \n");
  // enable clear and start counter
  ESP_ERROR_CHECK(pcnt_unit_enable(m_pcnt_unit));
  ESP_ERROR_CHECK(pcnt_unit_clear_count(m_pcnt_unit));
  ESP_ERROR_CHECK(pcnt_unit_start(m_pcnt_unit));

  // sleep for 10s
  vTaskDelay(10000 / portTICK_PERIOD_MS);

  printf("Stop get count and disable counter \n");
  // stop counter get counter value and disable counter
  ESP_ERROR_CHECK(pcnt_unit_stop(m_pcnt_unit));
  ESP_ERROR_CHECK(pcnt_unit_get_count(m_pcnt_unit, &pulse_count));
  ESP_ERROR_CHECK(pcnt_unit_disable(m_pcnt_unit));

  // entering critical region as we are updating the speed value
  taskENTER_CRITICAL(&my_spinlock);
  // update rpm value
  m_speed = pulse_count * 6;
  taskEXIT_CRITICAL(&my_spinlock);

  // delete the task after it finished
  vTaskDelete(NULL);
}

void FanTachoSensor::start_update_speed_task_wrapper(void *_this) {

  FanTachoSensor *sensor = reinterpret_cast<FanTachoSensor *>(_this);
  sensor->update_speed_task();
}

int FanTachoSensor::get_current_value() {

  // get state of task
  eTaskState state = eDeleted;
  if (m_taskHandle != NULL) {
    state = eTaskGetState(m_taskHandle);
  }

  // only run when no task is currently running
  // NULL = not existing
  // 4 == DELETED
  if (state == eDeleted) {

    // spawn background task with 4096 bytes as stack
    xTaskCreate(this->start_update_speed_task_wrapper, "Fan - Update Speed",
                4096, this, 10, &m_taskHandle);
  }

  return m_speed;
}

} // namespace ductfan
