#ifndef ACS233_SOLENOID
#define ACS233_SOLENOID

#include "Arduino.h"

class Solenoid {
private:
  int solenoid_pin;

public:
  bool lock_state;
  float unlocked_duration;

  Solenoid(int pin);
  void lock();
  void unlock();
};

#endif