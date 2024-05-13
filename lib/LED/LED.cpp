#include "LED.h"

LED::LED(uint8_t pin) {
  this->led_pin = pin;
  this->last_blink = -1;
  pinMode(this->led_pin, OUTPUT);
}

void LED::on() { digitalWrite(this->led_pin, HIGH); }

void LED::off() { digitalWrite(this->led_pin, LOW); }

void LED::blink() {

  if (millis() - this->last_blink >= BLINK_DELAY) {
    digitalWrite(this->led_pin, !digitalRead(this->led_pin));
    this->last_blink = millis();
  }
}