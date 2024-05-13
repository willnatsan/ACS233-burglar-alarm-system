#include "LED.h"

LED::LED(uint8_t pin) {
  this->led_pin = pin;
  pinMode(this->led_pin, OUTPUT);
}

void LED::on() { digitalWrite(this->led_pin, HIGH); }

void LED::off() { digitalWrite(this->led_pin, LOW); }

void LED::blink() {
  this->on();
  delay(BLINK_DELAY);
  this->off();
  delay(BLINK_DELAY);
}