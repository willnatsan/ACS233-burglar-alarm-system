#ifndef ACS233_SENSOR
#define ACS233_SENSOR

#include "Arduino.h"
#include "ENUMS.h"

class Sensor {
protected:
  uint8_t sensor_pin;
  void (*ISRFunction)();
  
public:
  explicit Sensor(uint8_t pin, void (*isr)());
  void setup();
  bool read() const;
};

// Magnetic Sensor for the door and window
class MagneticSensor : public Sensor {
public:
  MAGNETIC_SENSOR_STATE mag_state;
  float last_opened_at;

  explicit MagneticSensor(uint8_t pin, void (*isr)());
  void setup();
};

// PIR Motion Sensor for detecting motion
class PIRSensor : public Sensor {
public:
  PIR_SENSOR_STATE pir_state;

  explicit PIRSensor(uint8_t pin, void (*isr)());
};

// Button Sensor for detecting button press
class ButtonSensor : public Sensor {
public:
  BUTTON_STATE button_state;

  explicit ButtonSensor(uint8_t pin, void (*isr)());
  void setup();
};

#endif