#include "Controller.h"

Controller::Controller(uint8_t door_mag_pin, uint8_t window_mag_pin,
                       uint8_t pir_pin, uint8_t button_pin,
                       uint8_t disarmed_led_pin, uint8_t home_led_pin,
                       uint8_t away_led_pin, uint8_t solenoid_led_pin,
                       uint8_t buzzer_led_pin, uint8_t solenoid_pin,
                       uint8_t buzzer_pin) {
  // Initialise sensors
  door = new MagneticSensor(door_mag_pin, handle_magnetic_sensor_isr);
  window = new MagneticSensor(window_mag_pin, handle_magnetic_sensor_isr);
  pir = new PIRSensor(pir_pin, handle_pir_sensor_isr);
  button = new ButtonSensor(button_pin, handle_button_isr);

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
  last_triggered_at = -1;

  // Set the number of facial recognition attempts to 0
  facial_recognition_attempts = 0;
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
      Serial.write("py");
    } else {
      Serial.write("pn");
    }
    break;

  // If the command is 's'. the user is trying to change the system mode
  case 's':
    switch (command.charAt(1)) {
    case 'd':
      this->change_mode(SYSTEM_MODE::DISARMED);
      break;
    case 'h':
      this->change_mode(SYSTEM_MODE::HOME);
      break;
    case 'a':
      this->change_mode(SYSTEM_MODE::AWAY);
      break;
    }
    break;

  // If the command is 'r', the user is trying to run a test of the system
  case 'r':
    if (this->input_test() && this->output_test()) {
      Serial.write("ry");
    } else {
      Serial.write("rn");
    }
    break;

  // If the command is 'c', the user is trying to change the PIN
  case 'c':
    if (command.substring(1).length() != 4 || !command.substring(1).toInt()) {
      Serial.write("cn");
    } else {
      this->correct_pin = command.substring(1);
      Serial.write("cy");
    }
    break;
  }
}

void Controller::home_mode(String command) {
  system_mode_leds[1]->on();
  system_mode_leds[0]->off();
  system_mode_leds[2]->off();

  switch (command.charAt(0)) {
  // If the command is 'f', the user is undergoing facial recognition
  case 'f':
    facial_recognition_attempts++;
    switch (command.charAt(1)) {
    case 'y':
      solenoid->unlock();
      solenoid_led->blink();
      Serial.write("fy");
      break;
    case 'n':
      if (facial_recognition_attempts >= 3) {
        Serial.write("fn");
        facial_recognition_attempts = 0; // Reset the number of attempts
      }
      break;
    }

  // If the command is 'p', the user has entered a PIN to enter the settings OR
  // disarm the system
  case 'p':
    if (command.substring(1).equals(this->correct_pin)) {
      this->authorisation_status = true;
      Serial.write("py");
    } else {
      Serial.write("pn");
    }
    break;

  // if the command is 'd', the user is trying to disarm the system
  case 'd':
    if (this->authorisation_status) {
      this->change_mode(SYSTEM_MODE::DISARMED);
      this->authorisation_status = false;
      this->last_triggered_at = -1;
      Serial.write("dy");
    } else {
      Serial.write("dn");
    }
    break;

  // If the command is 's'. the user is trying to change the system mode
  case 's':
    switch (command.charAt(1)) {
    case 'd':
      this->change_mode(SYSTEM_MODE::DISARMED);
      break;
    case 'h':
      this->change_mode(SYSTEM_MODE::HOME);
      break;
    case 'a':
      this->change_mode(SYSTEM_MODE::AWAY);
      break;
    }
    break;

  // If the command is 'r', the user is trying to run a test of the system
  case 'r':
    if (this->input_test() && this->output_test()) {
      Serial.write("ry");
    } else {
      Serial.write("rn");
    }
    break;

  // If the command is 'c', the user is trying to change the PIN
  case 'c':
    if (command.substring(1).length() != 4 || !command.substring(1).toInt()) {
      Serial.write("cn");
    } else {
      this->correct_pin = command.substring(1);
      Serial.write("cy");
    }
    break;
  }

  this->check_timeouts();
}

void Controller::away_mode(String command) {
  system_mode_leds[2]->on();
  system_mode_leds[0]->off();
  system_mode_leds[1]->off();

  switch (command.charAt(0)) {
  // If the command is 'f', the user is undergoing facial recognition
  case 'f':
    facial_recognition_attempts++;
    switch (command.charAt(1)) {
    case 'y':
      solenoid->unlock();
      solenoid_led->blink();
      Serial.write("fy");
      break;
    case 'n':
      if (facial_recognition_attempts >= 3) {
        Serial.write("fn");
        facial_recognition_attempts = 0; // Reset the number of attempts
      }
      break;
    }

  // If the command is 'p', the user has entered a PIN to disarm the system
  case 'p':
    if (command.substring(1).equals(this->correct_pin)) {
      this->authorisation_status = true;
      Serial.write("py");
    } else {
      Serial.write("pn");
    }
    break;

  // if the command is 'd', the user is trying to disarm the system
  case 'd':
    if (this->authorisation_status) {
      this->change_mode(SYSTEM_MODE::DISARMED);
      this->authorisation_status = false;
      this->last_triggered_at = -1;
      Serial.write("dy");
    } else {
      Serial.write("dn");
    }
    break;
  }

  this->check_timeouts();
}

void Controller::magnetic_sensor_isr() {
  if (millis() - door->last_triggered_at >= DEBOUNCE_DURATION) {
    door->last_triggered_at = millis();
    door->mag_state = (MAGNETIC_SENSOR_STATE)door->read();

    if (door->mag_state == MAGNETIC_SENSOR_STATE::CLOSED &&
        solenoid->solenoid_state == SOLENOID_STATE::UNLOCKED) {
      solenoid->lock();
      solenoid_led->off();
    } else if (door->mag_state == MAGNETIC_SENSOR_STATE::OPEN) {
      switch (current_mode) {
      case SYSTEM_MODE::AWAY:
      case SYSTEM_MODE::HOME:
        this->last_triggered_at = millis();
        break;
      case SYSTEM_MODE::DISARMED:
      default:
        break;
      }
    }
  }
}

void Controller::pir_sensor_isr() {
  pir->last_triggered_at = millis();
  pir->pir_state = (PIR_SENSOR_STATE)pir->read();

  if (pir->pir_state == PIR_SENSOR_STATE::MOTION_DETECTED &&
      millis() - pir->last_triggered_at >= MOTION_SENSOR_TIMEOUT) {
    switch (current_mode) {
    case SYSTEM_MODE::AWAY:
      this->last_triggered_at = millis();
      break;
    case SYSTEM_MODE::HOME:
    case SYSTEM_MODE::DISARMED:
    default:
      break;
    }
  }
}

void Controller::button_isr() {
  if (millis() - button->last_triggered_at >= DEBOUNCE_DURATION) {
    button->last_triggered_at = millis();
    button->button_state = (BUTTON_STATE)button->read();

    solenoid->unlock();
    solenoid_led->blink();
    solenoid->last_unlocked_at = millis();
  }
}

void Controller::change_mode(SYSTEM_MODE mode) { this->current_mode = mode; }

bool Controller::check_status() {
  String message = "st";
  message += door->mag_state;
  message += window->mag_state;
  message += solenoid->solenoid_state;
  Serial.write(message.c_str());

  if (door->mag_state == MAGNETIC_SENSOR_STATE::CLOSED ||
      window->mag_state == MAGNETIC_SENSOR_STATE::CLOSED ||
      solenoid->solenoid_state == SOLENOID_STATE::LOCKED) {
    return true;
  }
  return false;
}

void Controller::check_timeouts() {
  // Check if the user has been authorised within the allocated time
  if (!this->authorisation_status &&
      millis() - last_triggered_at >= PIN_ENTRY_TIMEOUT) {
    buzzer->on();
    buzzer_led->blink();
    buzzer->last_buzzed_at = millis();
  }

  // Check if the alarm has been activated for more than the allocated time
  if (buzzer->buzzer_state == BUZZER_STATE::ON &&
      millis() - buzzer->last_buzzed_at >= ALARM_TIMEOUT) {
    buzzer->off();
    buzzer_led->off();
    buzzer->last_buzzed_at = -1;
  }
}

bool Controller::input_test() {
  String message = "it";
  message += door->read();
  message += window->read();
  message += pir->read();
  message += button->read();
  Serial.write(message.c_str());

  return true;
}

bool Controller::output_test() {
  solenoid->unlock();
  solenoid_led->blink();
  solenoid->lock();

  buzzer->beep();
  buzzer_led->blink();

  for (int i = 0; i < 3; i++) {
    system_mode_leds[i]->blink();
  }

  return true;
}