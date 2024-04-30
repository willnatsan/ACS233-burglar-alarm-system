#include "Controller.h"

Controller::Controller(uint8_t door_mag_pin, uint8_t window_mag_pin,
                       uint8_t pir_pin, uint8_t button_pin,
                       uint8_t disarmed_led_pin, uint8_t home_led_pin,
                       uint8_t away_led_pin, uint8_t solenoid_led_pin,
                       uint8_t buzzer_led_pin, uint8_t solenoid_pin,
                       uint8_t buzzer_pin) {
  // Initialise sensors
  door = new MagneticSensor(door_mag_pin, magnetic_sensor_isr);
  window = new MagneticSensor(window_mag_pin, magnetic_sensor_isr);
  pir = new PIRSensor(pir_pin, pir_sensor_isr);
  button = new ButtonSensor(button_pin, button_isr);

  // Initialise actuators
  buzzer = new Buzzer(buzzer_pin);
  solenoid = new Solenoid(solenoid_pin);

  solenoid_led = new LED(solenoid_led_pin);
  buzzer_led = new LED(buzzer_led_pin);
  system_mode_leds[0] = new LED(disarmed_led_pin);
  system_mode_leds[1] = new LED(home_led_pin);
  system_mode_leds[2] = new LED(away_led_pin);

  // Set the system to disarmed mode by default
  change_mode(DISARMED);

  // Set the system to unauthorised by default
  authorisation_status = false;

  // Set the correct PIN to "1234" by default
  correct_pin = "1234";

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

void Controller::disarmed_mode(String command) {
  system_mode_leds[0]->on();
  system_mode_leds[1]->off();
  system_mode_leds[2]->off();

  // Read the command received from the GUI and act accordingly
  switch (command.charAt(0)) {

  // If the command is 'p', the user has enetered a PIN to enter the settings
  case 'p':;
    if (command.substring(1).equals(this->correct_pin)) {
      this->authorisation_status = true;
      Serial.write("py"); // "py" means the PIN is correct
    } else {
      Serial.write("pn"); // "pn" means the PIN is incorrect
    }
    break;

  // If the command is 's'. the user is trying to change the system mode
  case 's':
    switch (command.charAt(1)) {
    case 'd':
      change_mode(SYSTEM_MODE::DISARMED);
      break;
    case 'h':
      change_mode(SYSTEM_MODE::HOME);
      break;
    case 'a':
      change_mode(SYSTEM_MODE::AWAY);
      break;
    }
    break;

  // If the command is 'r', the user is trying to run a test of the system
  case 'r':
    if (input_test() && output_test()) {
      Serial.write("ry"); // "ry" means the test was successful
    } else {
      Serial.write("rn"); // "rn" means the test was unsuccessful
    }
    break;

  // If the command is 'c', the user is trying to change the PIN
  case 'c':
    if (command.substring(1).length() != 4 || !command.substring(1).toInt()) {
      Serial.write("cn"); // "cn" means the new PIN is invalid
    } else {
      this->correct_pin = command.substring(1);
      Serial.write("cy"); // "cy" means the new PIN is valid
    }
    break;
  }
}

void Controller::home_mode(String command) {
  system_mode_leds[1]->on();
  system_mode_leds[0]->off();
  system_mode_leds[2]->off();

  switch (command.charAt(0)) {
  // If the command is 'p', the user has enetered a PIN
  case 'p':;
    if (command.substring(1).equals(this->correct_pin)) {
      this->authorisation_status = true;
      Serial.write("py"); // "py" means the PIN is correct
    } else {
      Serial.write("pn"); // "pn" means the PIN is incorrect
    }
    break;

  // if the command is 'd', the user is trying to disarm the system
  case 'd':
    if (this->authorisation_status) {
      change_mode(SYSTEM_MODE::DISARMED);
      alarm_off();
      Serial.write("dy"); // "dy" means the disarming was successful
    } else {
      Serial.write("dn"); // "dn" means the disarming was unsuccessful
    }
    break;
  }
}

void Controller::away_mode(String command) {}

void Controller::magnetic_sensor_isr() {}

void Controller::pir_sensor_isr() {}

void Controller::button_isr() {}