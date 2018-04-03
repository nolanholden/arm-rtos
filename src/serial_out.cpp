#include <FreeRTOS.h>
#include <task.h>

#include <Arduino.h>
#include <usb_dev.h>

using byte_t = uint8_t;

void init_serial_out() {
  usb_init();
  Serial.begin(9600);
}

inline void write_to_serial(byte_t b) { Serial.write(b); }

void write_to_serial(const byte_t* bytes, size_t size) { 
	while (size--) write_to_serial(*bytes++);
}

void say_hello_serial_task(void* args) {
  const byte_t hello_world[] = "hello, arm rtos world!";
  const auto num_bytes = (sizeof(hello_world)/sizeof(*hello_world));
  for (;;) {
    write_to_serial(hello_world, num_bytes);
    vTaskDelay(1000);
  }
}
