#include <Arduino.h>
#include <ArduinoSTL.h>

int red_led = 4;
int yellow_led = 3;
int green_led = 2;
int solenoid = 11;
int buzzer = 12;

void setup() {
  // put your setup code here, to run once

  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(solenoid, OUTPUT);
  pinMode(buzzer, OUTPUT);

  tone(buzzer, 500);
  delay(1000);
  noTone(buzzer);
}

void loop() {
  digitalWrite(red_led, HIGH);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  delay(1000);

  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, HIGH);
  digitalWrite(green_led, LOW);
  delay(1000);

  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, HIGH);
  delay(1000);

  digitalWrite(solenoid, HIGH);
  delay(100);
  digitalWrite(solenoid, LOW);
  delay(100);
  digitalWrite(solenoid, HIGH);
  delay(100);
  digitalWrite(solenoid, LOW);
  delay(100);
}
