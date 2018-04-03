#include <kinetis.h>
#include <FreeRTOS.h>
#include <task.h>

#include <type_traits>


#define LED_PORT_DATA_OUT_REGISTER   GPIOC_PDOR
using register_type = std::decay<decltype(LED_PORT_DATA_OUT_REGISTER)>::type;

constexpr auto LED_CONFIG = register_type{ 0x00000102 };
constexpr auto LED_MASK   = register_type{ 0x00000020 };

void init_led_port_output() {
  PORTC_PCR5 = LED_CONFIG;
  GPIOC_PDDR |= LED_MASK;
}

void led_blink_task(void* args) {
  init_led_port_output();

  for (auto turn_on = true; ; turn_on = ~turn_on) {
    if (turn_on)
      GPIOC_PDOR |= LED_MASK;
    else
      GPIOC_PDOR &= ~LED_MASK;

    vTaskDelay(500);
  }
}
