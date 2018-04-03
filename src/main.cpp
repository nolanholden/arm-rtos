#include <kinetis.h>
#include <stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

// extern tasks declared elsewhere in program
extern void led_blink_task(void* args);
extern void say_hello_serial_task(void* args);

int main() {
  // create the tasks
  xTaskCreate(led_blink_task, "LT", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(say_hello_serial_task, "ST", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  // start scheduler, main should stop functioning here
  vTaskStartScheduler();

  for (;;) {}

  return 0;
}
