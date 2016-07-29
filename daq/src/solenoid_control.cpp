#include "../include/gpio.h"
#include <stdlib.h>
#include <iostream>

int main()
{

  unsigned int pin = 88;
  gpio_export(pin);
  gpio_set_dir(pin, OUTPUT_PIN);
  gpio_set_value(pin, HIGH);
  std::cout << "Press any key to stop" << std::endl;
  std::cin.get();
  std::cout << "Stopped. Press any key to exit" << std::endl;
  gpio_set_value(pin, LOW);
  std::cin.get();
 
 }
