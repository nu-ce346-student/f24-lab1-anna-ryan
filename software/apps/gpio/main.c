// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");

  // Turn on all LEDs on the back of the Microbit
  // Add code here
  gpio_config(21, 0);
  gpio_config(22, 0);
  gpio_config(15, 0);
  gpio_config(24, 0);
  gpio_config(19, 0);
  gpio_config(28, 0);
  gpio_config(11, 0);
  gpio_config(31, 0);
  gpio_config(37, 0);
  gpio_config(30, 0);

  gpio_set(21);
  gpio_set(22);
  gpio_set(15);
  gpio_set(24);
  gpio_set(19);
  gpio_clear(28);
  gpio_clear(11);
  gpio_clear(31);
  gpio_clear(37);
  gpio_clear(30);

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here
  *(uint32_t*)(0x50000514) = 0x00100000; // DIR
  *(uint32_t*)(0x50000504) = 0x00100000; // OUT



  // loop forever
  printf("Looping\n");
  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here

    gpio_print();

    

    nrf_delay_ms(100);
  }
}

