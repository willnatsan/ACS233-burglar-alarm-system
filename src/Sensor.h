#ifndef ACS233_SENSOR
#define ACS233_SENSOR

#include "Arduino.h"

class Sensor {
private:
  uint8_t sensor_pin;

public:
  explicit Sensor(uint8_t pin);
  bool read();
};

// Magnetic Sensor for the door and window
class MagneticSensor : public Sensor {
public:
  bool mag_state;

  explicit MagneticSensor(uint8_t pin);
};

// PIR Motion Sensor for detecting motion
class PIRSensor : public Sensor {
public:
  bool pir_state;

  explicit PIRSensor(uint8_t pin);
};

// Button Sensor for detecting button press
class ButtonSensor : public Sensor {
public:
  bool button_state;

  explicit ButtonSensor(uint8_t pin);
};

#endif