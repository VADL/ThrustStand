#include "gpio.h"
#include <stdlib.h>
#include <iostream>

int main()
{
  int adcpin = 0;
  unsigned int adcvalue = 0;

  adc_get_value(adcpin, &adcvalue);

  std::cout << adcvalue << std::endl;
}
