#ifndef ACS233_SOLENOID
#define ACS233_SOLENOID

#include "Arduino.h"

class Solenoid {
private:
  uint8_t solenoid_pin;

public:
  bool lock_state;
  float unlocked_duration;

  explicit Solenoid(uint8_t pin);
  void lock();
  void unlock();
};

#endif