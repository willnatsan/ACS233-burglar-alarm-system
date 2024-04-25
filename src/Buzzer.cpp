#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin) {
  this->buzzer_pin = pin;
  this->buzzer_state = false;
  pinMode(this->buzzer_pin, OUTPUT);
}

void Buzzer::on() {
  tone(this->buzzer_pin, BUZZER_ALARM_FREQUENCY);
  this->buzzer_state = true;
}

void Buzzer::off() {
  noTone(this->buzzer_pin);
  this->buzzer_state = false;
}

void Buzzer::beep(int time_delay) {
  if (this->buzzer_state) {
    off();
    delay(time_delay);
  } else {
    on();
    delay(time_delay);
  }
}