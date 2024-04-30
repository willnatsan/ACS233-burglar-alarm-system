#ifndef ACS233_CONTROLLER
#define ACS233_CONTROLLER

#include "Arduino.h"
#include "Buzzer.h"
#include "DisplayInterface.h"
#include "ENUMS.h"
#include "LED.h"
#include "Sensor.h"
#include "Solenoid.h"

#define DOOR_UNLOCK_TIMEOUT 10000 // random value for now
#define ALARM_TIMEOUT 10000       // random value for now
#define PIN_ENTRY_TIMEOUT 10000   // random value for now

// From testing the motion sensor seems to hold a HIGH value for 10-20s after
// motion is detected A timeout of 25s seems to work well to prevent false
// alarms
#define MOTION_SENSOR_TIMEOUT 25000

// From testing a duration of 50ms seems to work well to prevent switch bounce
#define DEBOUNCE_DURATION 50

class Controller {
private:
  // Sensors
  MagneticSensor *door;
  MagneticSensor *window;
  PIRSensor *pir;
  ButtonSensor *button;

  // Actuators
  Buzzer *buzzer;
  Solenoid *solenoid;

  LED *solenoid_led;
  LED *buzzer_led;
  LED *system_mode_leds[3];

  // Time at which the system was last armed
  int64_t last_armed_at;

  bool authorisation_status;
  String correct_pin;

  // static Controller *controller_handler; // Static pointer to the controller
  // object (For ISRs)

  // ISR functions must be static so that they can be attached to the interrupt
  static void magnetic_sensor_isr();
  static void pir_sensor_isr();
  static void button_isr();

  String change_mode(SYSTEM_MODE mode);
  void authorise_user();

  void alarm_on();
  void alarm_off();

  void handle_unauthorised_entry(UNAUTHORISED_ENTRY_TYPE type);
  void handle_authorised_entry();

  void check_status();
  void change_settings();

  bool input_test();
  bool output_test();

public:
  SYSTEM_MODE current_mode;

  explicit Controller(uint8_t door_mag_pin, uint8_t window_mag_pin,
                      uint8_t pir_pin, uint8_t button_pin,
                      uint8_t disarmed_led_pin, uint8_t home_led_pin,
                      uint8_t away_led_pin, uint8_t solenoid_led_pin,
                      uint8_t buzzer_led_pin, uint8_t solenoid_pin,
                      uint8_t buzzer_pin);
  void setup();
  void disarmed_mode(String command);
  void home_mode(String command);
  void away_mode(String command);

  // static void handle_magnetic_sensor_isr();
  // static void handle_pir_sensor_isr();
  // static void handle_button_isr();
};

#endif