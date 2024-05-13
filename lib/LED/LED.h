#ifndef ACS233_LED
#define ACS233_LED

#include "Arduino.h"

#define BLINK_DELAY 100

class LED {
private:
  uint8_t led_pin;

public:
  uint64_t last_blink;

  explicit LED(uint8_t pin);
  void on();
  void off();
  void blink();
};

#endif