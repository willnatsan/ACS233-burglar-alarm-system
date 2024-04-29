#include "LED.h"

LED::LED(uint8_t pin) {
  this->led_pin = pin;
  pinMode(this->led_pin, OUTPUT);
}

void LED::on() { digitalWrite(this->led_pin, HIGH); }

void LED::off() { digitalWrite(this->led_pin, LOW); }

void LED::blink(int time_delay) {
  this->on();
  delay(time_delay);
  this->off();
  delay(time_delay);
}