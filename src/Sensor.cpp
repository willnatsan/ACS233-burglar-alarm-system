#include "Sensor.h"

Sensor::Sensor(uint8_t pin) {
  this->sensor_pin = pin;
  pinMode(this->sensor_pin, INPUT);
}

bool Sensor::read() { return digitalRead(this->sensor_pin); }

MagneticSensor::MagneticSensor(uint8_t pin) : Sensor(pin) {
  this->mag_state = this->read();
}

PIRSensor::PIRSensor(uint8_t pin) : Sensor(pin) {
  this->pir_state = this->read();
}

ButtonSensor::ButtonSensor(uint8_t pin) : Sensor(pin) {
  this->button_state = this->read();
}