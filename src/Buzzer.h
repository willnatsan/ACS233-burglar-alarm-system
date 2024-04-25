#ifndef ACS233_BUZZER
#define ACS233_BUZZER

#include "Arduino.h"

class Buzzer {
private:
  int buzzer_pin;
  int alarm_frequency;   // Maybe can move to Constants.h
  int warning_frequency; // Maybe can move to Constants.h

  void beep(int frequency, int on_delay, int off_delay);

public:
  bool buzzer_state;
  float buzzer_duration;

  Buzzer(int pin);
  void on();
  void off();
};

#endif