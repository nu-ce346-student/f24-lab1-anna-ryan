#include "gpio.h"
#include <stdio.h>

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t _unused0[0x504/4];
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t _unused1[(0x700-0x524)/4-1];
  uint32_t PIN_CNF[32];
} gpio_reg_t;

volatile gpio_reg_t *port_0 = (gpio_reg_t*)0x50000000;
volatile gpio_reg_t *port_1 = (gpio_reg_t*)0x50000300;

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  uint32_t port = gpio_num >> 5;
  uint32_t gpio_pin = gpio_num & 0x1F;
  if (port == 0) {
    if (!dir) {
      // printf("gpio_config port 0 input\n");
      port_0->PIN_CNF[gpio_pin] = 0;
    }
    else {
      port_0->PIN_CNF[gpio_pin] = 3;
    }
  } else {
    if (!dir) {
      port_1->PIN_CNF[gpio_pin] = 0;
    }
    else {
      port_1->PIN_CNF[gpio_pin] = 3;
    }
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured
  uint32_t gpio_pin = gpio_num & 0x1F;
  uint32_t port = gpio_num >> 5;

  if (!port) {
    port_0->OUTSET = 1 << gpio_pin;
  } else {
    port_1->OUTSET = 1 << gpio_pin;
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  uint32_t gpio_pin = gpio_num & 0x1F;
  uint32_t port = gpio_num >> 5;
  if (!port) {
    port_0->OUTCLR = 1 << gpio_pin;
  } else {
    port_1->OUTCLR = 1 << gpio_pin;
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured
  uint32_t gpio_pin = gpio_num & 0x1F;
  uint32_t port = gpio_num >> 5;
  if (!port) {
    return port_0->IN & (1 << gpio_pin);
  } else {
    return port_1->IN & (1 << gpio_pin);
  }
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
  // printf("port_0_DIR: %p\tport_0_pincnf[18]: %p\n", &port_0->DIR, &port_0->PIN_CNF[18]);
  // printf("%d", gpio_read(22));
  // printf("port_0_DIR: %p, port_1_DIR: %p\n", &port_0->DIR, &port_1->DIR);
  // printf("port_0_OUT: %p, port_1_OUT: %p\n", &port_0->OUT, &port_1->OUT);
  // printf("port_0_PIN_CNF[21]: %p, port_1_PIN_CNF[5]: %p\n", &port_0->PIN_CNF[21], &port_1->PIN_CNF[5]);
  printf("OUTCLR: %p\n", &port_0->OUTCLR);


}

