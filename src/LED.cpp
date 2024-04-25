#include "LED.h"

LED::LED(uint8_t pin) {
  this->led_pin = pin;
  this->led_state = false;
  pinMode(this->led_pin, OUTPUT);
}

void LED::on() {
  digitalWrite(this->led_pin, HIGH);
  this->led_state = true;
}

void LED::off() {
  digitalWrite(this->led_pin, LOW);
  this->led_state = false;
}

void LED::blink(int time_delay) {
  if (this->led_state) {
    off();
    delay(time_delay);
  } else {
    on();
    delay(time_delay);
  }
}