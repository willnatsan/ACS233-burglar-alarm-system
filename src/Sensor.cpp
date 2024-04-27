#include "Sensor.h"

Sensor::Sensor(uint8_t pin, void (*isr)()) {
  this->sensor_pin = pin;
  this->ISRFunction = isr;
}

void Sensor::setup() {
  pinMode(this->sensor_pin, INPUT);
  if (this->ISRFunction != nullptr) {
    attachInterrupt(digitalPinToInterrupt(this->sensor_pin), this->ISRFunction, CHANGE);
  }
}

bool Sensor::read() const { return digitalRead(this->sensor_pin); }

// Magnetic Sensor for the door and window
MagneticSensor::MagneticSensor(uint8_t pin, void (*isr)()) : Sensor(pin, isr) {
  this->mag_state = this->read();
}

void MagneticSensor::setup() {
  pinMode(this->sensor_pin, INPUT_PULLUP);
  if (this->ISRFunction != nullptr) {
    attachInterrupt(digitalPinToInterrupt(this->sensor_pin), this->ISRFunction, CHANGE);
  }
}

// PIR Motion Sensor for detecting motion
PIRSensor::PIRSensor(uint8_t pin, void (*isr)()) : Sensor(pin, isr) {
  this->pir_state = this->read();
}

// Button Sensor for detecting button press
ButtonSensor::ButtonSensor(uint8_t pin, void(*isr)()) : Sensor(pin, isr) {
  this->button_state = this->read();
}

void ButtonSensor::setup() {
  pinMode(this->sensor_pin, INPUT_PULLUP);
  if (this->ISRFunction != nullptr) {
    attachInterrupt(digitalPinToInterrupt(this->sensor_pin), this->ISRFunction, FALLING);
  }
}