#ifndef ACS233_CONTROLLER
#define ACS233_CONTROLLER

#include "Arduino.h"
#include "Buzzer.h"
#include "DisplayInterface.h"
#include "LED.h"
#include "Sensor.h"
#include "Solenoid.h"
#include "ENUMS.h"

class Controller {
    private:
        float UNLOCK_TIMEOUT = 10000; // Random value for now
        float ALARM_TIMEOUT = 10000; // Random value for now
        float PIN_ENTRY_TIMEOUT = 10000; // Random value for now
        float MOTION_SENSOR_TIMEOUT = 10000; // Random value for now

        float last_armed_at;

        MagneticSensor *door;
        MagneticSensor *window;
        PIRSensor *pir; 
        ButtonSensor *button;

        Buzzer *buzzer;
        Solenoid *lock;

        void magnetic_sensor_isr();
        void pir_sensor_isr();
        void button_isr();

    public:
        explicit Controller(int magnetic_sensor_pin, int pir_sensor_pin, int button_pin,
                        int disarmed_mode_led, int home_mode_led, int away_mode_led,
                        int solenoid_pin,int buzzer_pin);
        void setup();
        void verify_user();
        void change_mode(SYSTEM_MODE mode);
        void alarm_on();
        void alarm_off();
        void handle_unauthorised_entry(UNAUTHORISED_ENTRY_TYPE type);
        void handle_authorised_entry();
        void check_status();

};


#endif