#include "ductsense.hpp"

namespace ductfan {

StatefullButton::StatefullButton(
    std::unique_ptr<button_handle_t> button_handle) {
  m_button = std::move(button_handle);
}

} // namespace ductfan
