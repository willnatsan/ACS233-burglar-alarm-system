#ifndef ACS233_CONSTANTS
#define ACS233_CONSTANTS

// Enumerations for the system to help make the main code more readable

// System Modes
enum SYSTEM_MODE {
    DISARMED = 0,
    HOME = 1,
    AWAY = 2
};

// Types of possible unauthorised entries (Handled slighlty differently in the system)
enum UNAUTHORISED_ENTRY_TYPE {
    MAGNETIC_SENSOR_TRIGGERED = 0,
    PIR_SENSOR_TRIGGERED = 1,
};

// Actuator States
enum SOLENOID_STATE {
    LOCKED = 0,
    UNLOCKED = 1
};

enum ALARM_STATE {
    ON = 1,
    OFF = 0
};

// Sensor States
enum BUTTON_STATE {
    PRESSED = 0,
    RELEASED = 1
};

enum PIR_SENSOR_STATE {
    MOTION_DETECTED = 0,
    NO_MOTION = 1
};

enum MAGNETIC_SENSOR_STATE {
    OPEN = 0,
    CLOSED = 1
};

#endif