#include <stdio.h>
#include "pico/stdlib.h"

#include "picosystem_hardware.h"

extern struct picosystem_hw pshw;

int main() 
{
  // const uint led_pin = 25;
  uint led_pin = 0;  // PICOSYSTEM_PIN_RED;

#if 0
  gpio_init(PICOSYSTEM_PIN_GREEN);
  gpio_set_dir(PICOSYSTEM_PIN_GREEN, GPIO_OUT);
  gpio_init(PICOSYSTEM_PIN_RED);
  gpio_set_dir(PICOSYSTEM_PIN_RED, GPIO_OUT);
  gpio_init(PICOSYSTEM_PIN_BLUE);
  gpio_set_dir(PICOSYSTEM_PIN_BLUE, GPIO_OUT);
#else
  picosystem_init();
#endif

  // Initialize chosen serial port
  stdio_init_all();

  printf("Hello PicoSystem!\r\n");
  // Keep the screen off
  picosystem_backlight(0);
  picosystem_flip();
  // Wait fot the DMA transfer to finish
  while(picosystem_is_flipping()) { sleep_ms(1); }
  // Wait for the screen to update
  picosystem_wait_vsync();
  picosystem_wait_vsync();
  picosystem_backlight(75);

  pshw.io = picosystem_gpio_get();

  color_t c = picosystem_rgb(15, 15, 15, 15);
  uint32_t x = 0;
  uint32_t y = 0;
  uint32_t v = 1;
  uint32_t elapse = 0;

  // Loop forever
  while (true) {
    uint32_t start_tick_us = picosystem_time_us();

    pshw.lio = pshw.io;
    pshw.io = picosystem_gpio_get();

    while(picosystem_is_flipping()) {}

#if 0
    // Blink LED
    printf("LED on!\r\n");
    // gpio_put(led_pin + PICOSYSTEM_PIN_GREEN, true);
    picosystem_led(0, 15, 0);
    sleep_ms(1000);
    printf("LED off!\r\n");
    // gpio_put(led_pin + PICOSYSTEM_PIN_GREEN, false);
    picosystem_led(15, 0, 15);
    sleep_ms(1000);
    // led_pin = (led_pin + 1) % 3;
#else
    picosystem_clear(0);
    picosystem_draw_line(NULL, x, 0, PICOSYSTEM_SCREEN_WIDTH - x - 1, PICOSYSTEM_SCREEN_HEIGHT - 1, c); 
    x += v;
    if ((x >= PICOSYSTEM_SCREEN_WIDTH) || (x <= 0)) {
      v = -v;
      x += v;
    }
    picosystem_flip();
    uint32_t end_tick_us = picosystem_time_us();
    elapse += end_tick_us - start_tick_us;
    if (x % 8 == 0) {
      printf("elapse: %d\r\n", elapse >> 3);
      elapse = 0;
    }
#endif
  }
}