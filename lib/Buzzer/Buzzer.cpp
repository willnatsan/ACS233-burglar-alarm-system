#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin) {
  this->buzzer_pin = pin;
  this->last_buzzed_at = -1;
  this->buzzer_state = BUZZER_STATE::OFF;
  pinMode(this->buzzer_pin, OUTPUT);
}

void Buzzer::on() {
  tone(this->buzzer_pin, BUZZER_ALARM_FREQUENCY);
  this->buzzer_state = BUZZER_STATE::ON;
}

void Buzzer::off() {
  noTone(this->buzzer_pin);
  this->buzzer_state = BUZZER_STATE::OFF;
}

void Buzzer::beep() {
  this->on();
  delay(BUZZER_DELAY);
  this->off();
  delay(BUZZER_DELAY);
}