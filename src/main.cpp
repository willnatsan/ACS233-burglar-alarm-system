#include "Controller.h"
#include <Arduino.h>
#include <ArduinoSTL.h>

uint8_t SOLENOID_PIN = 11;
uint8_t BUZZER_PIN = 12;

uint8_t SOLENOID_LED_PIN = 6;
uint8_t BUZZER_LED_PIN = 5;
uint8_t AWAY_LED_PIN = 4;
uint8_t DISARMED_LED_PIN = 3;
uint8_t HOME_LED_PIN = 2;

uint8_t WINDOW_MAG_PIN = 18;
uint8_t DOOR_MAG_PIN = 19;
uint8_t PIR_SENSOR_PIN = 20;
uint8_t BUTTON_PIN = 21;

Controller controller(DOOR_MAG_PIN, WINDOW_MAG_PIN, PIR_SENSOR_PIN, BUTTON_PIN,
                      DISARMED_LED_PIN, HOME_LED_PIN, AWAY_LED_PIN,
                      SOLENOID_LED_PIN, BUZZER_LED_PIN, SOLENOID_PIN,
                      BUZZER_PIN);

String command;
uint64_t timestamp = millis();

void setup() {
  Serial.begin(115200);
  controller.setup();
}

void loop() {
  // Receive command from GUI over serial to determine next action
  if (Serial.available()) {
    // Trimming out white spaces and \n ------------------------
    command = Serial.readStringUntil('\n');
    command.trim();
  } else {
    command = "";
  }

  switch (controller.current_mode) {
  case SYSTEM_MODE::DISARMED:
    controller.disarmed_mode(command);
    break;
  case SYSTEM_MODE::HOME:
    controller.home_mode(command);
    break;
  case SYSTEM_MODE::AWAY:
    controller.away_mode(command);
    break;
  }

  if (millis() - timestamp > 5000) {
    controller.check_status();
    timestamp = millis();
  }
}
