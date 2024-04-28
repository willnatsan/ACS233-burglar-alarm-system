#include "Solenoid.h"

Solenoid::Solenoid(uint8_t pin) {
  this->solenoid_pin = pin;
  this->solenoid_state = SOLENOID_STATE::UNLOCKED;
  this->last_unlocked_at = -1;
  pinMode(this->solenoid_pin, OUTPUT);
}

void Solenoid::lock() {
  digitalWrite(this->solenoid_pin, HIGH);
  this->solenoid_state = SOLENOID_STATE::LOCKED;
}

void Solenoid::unlock() {
  digitalWrite(this->solenoid_pin, LOW);
  this->solenoid_state = SOLENOID_STATE::UNLOCKED;
}
