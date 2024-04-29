String command;

unsigned long previousMillis = 0;  // Store the last time the LED was updated
const long interval = 100;        // Interval at which to blink (milliseconds)
bool ledState = false;             // Tracks the current state of the LED
int counter = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();  // Get the current time

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the LED was updated
    previousMillis = currentMillis;

    // sends a request for facial recognition every 2 seconds
    counter = counter + 1;
    if (counter == 20) {
      counter = 0;
      Serial.println("f");
    }





    if (Serial.available()) {
      // Trimming out white spaces and \n ------------------------
      command = Serial.readStringUntil('\n');
      command.trim();
      if (command.charAt(command.length() - 1) == '\n') {
        // Remove the last character
        command = command.substring(0, command.length() - 1);
      }
      // ---------------------------------------------------------

      // p = Pin
      if (command.charAt(0) == 'p') {
        String sub_command = command.substring(1);
        if (sub_command.equals(PIN)) {// PIn is the pin to check against
          Serial.println("py");
        } else {
          Serial.println("pn");
        }
      }

      // S = State
      if (command.charAt(0) == 's') {
        if (command.charAt(1) == 'd') {
          state = "dissarm"
        } else if (command.charAt(1) == 'h') {
          state = "home"
        } else if (command.charAt(1) == 'a') {
          state = "away"
          if (door == closed && window == closed) { // to send message to python script if doors are all closed when leaving
            Serial.println("sy"); 
          } else {
            Serial.println("sn"); 
          }

        }
      }

      if (command.charAt(0) == 'd') {
        if alarm == True {
          alarm == False
        }
      }


      if (command.charAt(0) == 'r') {
        runtest();
      }

      if (command.charAt(0) == 'c') {
        String new_pin = command.substring(1);
        pin = new_pin;  
      }

      if (command.charAt(0) == 'f') {
        if (command.charAt(1) == 'y') {
          char face_recognized = 'y';  // open door
        } else if (command.charAt(1) == 'n') { 
          char face_recognized = 'n'; // turn on alarm
        } else if (command.charAt(1) == 'f') { // if no face detected 
          char face_recognized = 'f'; // nothing happens the loop continues, f = failures
        }
      }






   //The main loop runs every 100 ms using millis
    }
  }
}