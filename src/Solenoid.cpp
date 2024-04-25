#include "Solenoid.h"

Solenoid::Solenoid(uint8_t pin) {
  this->solenoid_pin = pin;
  this->lock_state = false;
  this->unlocked_duration = 0;
  pinMode(this->solenoid_pin, OUTPUT);
}

void Solenoid::lock() {
  digitalWrite(this->solenoid_pin, HIGH);
  this->lock_state = true;
}

void Solenoid::unlock() {
  digitalWrite(this->solenoid_pin, LOW);
  this->lock_state = false;
}
