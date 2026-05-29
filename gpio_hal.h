#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/gpio.h>
#include <hal/gpio_types.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Set value to pin
 */
static inline bool gpio_set(const int8_t pin, const uint8_t value) {
  return gpio_set_level(pin, value) == ESP_OK;
}

/**
 * @brief Configure pin as input or output
 */
static inline bool gpio_configure(const int8_t pin, const gpio_mode_t mode) {
  if (pin < 0) {
    return false;
  }

  if (gpio_reset_pin(pin) != ESP_OK) {
    return false;
  }

  return gpio_set_direction(pin, mode) == ESP_OK;
}

/**
 * @brief Configure pin as input or output and set initial value
 */
static inline bool gpio_configure_and_set(const int8_t pin,
                                          const gpio_mode_t mode,
                                          const uint8_t value) {
  if (gpio_configure(pin, mode)) {
    return gpio_set(pin, value);
  }
  return false;
}

static inline uint8_t gpio_get(const int8_t pin) { return gpio_get_level(pin); }

static inline void gpio_enable_interrupt(const int8_t pin,
                                         gpio_isr_t isr_handler, void* args) {
  // Attach the ISR to the GPIO interrupt
  gpio_isr_handler_add(pin, isr_handler, NULL);
  // Enable the Interrupt
  gpio_intr_enable(pin);
}

static inline void gpio_disable_interrupt(const int8_t pin) {
  gpio_intr_disable(pin);
  gpio_isr_handler_remove(pin);
}

static inline void gpio_set_interrupt(const int8_t pin,
                                      gpio_int_type_t intr_type,
                                      gpio_isr_t isr_handler) {
  // Reset the pin
  gpio_reset_pin(pin);

  // Set the GPIOs to Output mode
  gpio_set_direction(pin, GPIO_MODE_INPUT);

  // Enable Pullup for Input Pin
  gpio_pullup_en(pin);

  // Disable pulldown for Input Pin
  gpio_pulldown_dis(pin);

  // Configure Raising Edge detection Interrupt for Input Pin
  gpio_set_intr_type(pin, intr_type);

  // install gpio isr service to default values
  gpio_install_isr_service(0);

  gpio_enable_interrupt(pin, isr_handler, NULL);
}

#ifdef __cplusplus
}
#endif