int64_t debounceDuration = 50;

int button = 21;
int buttonState;
int lastButtonState;
int64_t lastButtonChange = millis();

int magneticSensor = 19;
int magneticSensorState;
int lastMagneticSensorState;
int64_t lastMagneticSensorChange = millis();

int pirSensor = 20;
int pirSensorState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(magneticSensor, INPUT_PULLUP);
  pinMode(pirSensor, INPUT);
}

void loop() {
  if (millis()-lastButtonChange >= debounceDuration){
    buttonState = digitalRead(button);
    if (buttonState != lastButtonState){
      lastButtonChange = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW){
        Serial.println("Button Pressed!");
      }
    }
  }

  if (millis()-lastMagneticSensorChange >= debounceDuration){
    magneticSensorState = digitalRead(magneticSensor);
    if (magneticSensorState != lastMagneticSensorState){
      lastMagneticSensorState = magneticSensorState;
      lastMagneticSensorChange = millis();
      if (magneticSensorState == HIGH){
        Serial.println("Door/Window Opened!");
      }
    }
  }

  pirSensorState = digitalRead(pirSensor);

  if (pirSensorState == HIGH){
    Serial.println("Motion Detected!");
  }
  else{
    Serial.println("No Motion");
  }
}
