#include "Controller.h"

Controller::Controller(uint8_t door_mag_pin, uint8_t window_mag_pin,
                       uint8_t pir_pin, uint8_t button_pin,
                       uint8_t disarmed_led_pin, uint8_t home_led_pin,
                       uint8_t away_led_pin, uint8_t solenoid_pin,
                       uint8_t buzzer_pin) {
  // Initialise sensors
  door = new MagneticSensor(door_mag_pin, magnetic_sensor_isr);
  window = new MagneticSensor(window_mag_pin, magnetic_sensor_isr);
  pir = new PIRSensor(pir_pin, pir_sensor_isr);
  button = new ButtonSensor(button_pin, button_isr);

  // Initialise actuators
  buzzer = new Buzzer(buzzer_pin);
  lock = new Solenoid(solenoid_pin);
  diarmed_led = new LED(disarmed_led_pin);
  home_led = new LED(home_led_pin);
  away_led = new LED(away_led_pin);

  // Set the system to disarmed mode by default
  change_mode(DISARMED);

  // Set the system to unauthorised by default
  authorisation_status = false;

  // Set the last armed time to -1
  last_armed_at = -1;
}

void Controller::setup() {
  // Setup sensors
  door->setup();
  window->setup();
  pir->setup();
  button->setup();
}

void Controller::disarmed_mode() {}

void Controller::home_mode() {}

void Controller::away_mode() {}

void Controller::magnetic_sensor_isr() {}

void Controller::pir_sensor_isr() {}

void Controller::button_isr() {}