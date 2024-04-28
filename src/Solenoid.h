#ifndef ACS233_SOLENOID
#define ACS233_SOLENOID

#include "Arduino.h"
#include "ENUMS.h"

class Solenoid {
private:
  uint8_t solenoid_pin;

public:
  SOLENOID_STATE solenoid_state;
  float last_unlocked_at;

  explicit Solenoid(uint8_t pin);
  void lock();
  void unlock();
};

#endif