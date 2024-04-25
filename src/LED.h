#ifndef ACS233_LED
#define ACS233_LED

#include "Arduino.h"

class LED {
private:
  int led_pin;
  bool led_state;

public:
  LED(int pin);
  void on();
  void off();
  void blink(int on_delay, int off_delay);
};

#endif