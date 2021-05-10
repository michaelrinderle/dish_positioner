#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#define TRUE 0
#define FALSE 1

// ACTION NOTIFICATION LED
const byte PIN_ACTION_LED_1 = 13;

// RELAY PINS TO SWITCH DC MOTOR POLARITY
const byte PIN_RELAY_INPUT_1 = 7;
const byte PIN_RELAY_INPUT_2 = 8;

// HALL EFFECT MODULE FOR ACTUATOR 
const byte PIN_SENSOR_INTERRUPT_1 = 3;

volatile byte PULSE_SENSOR_1; // Pulse 


// 1" OF TRAVEL IN .6 SECONDS @ 1:28 RATIO
const int INCH_OF_TRAVEL_PER_SECOND = 700;

enum static_rest_types
{
  ANGLE = 0,
  ANGLE_EXTEND = 1,
  ANGLE_RETRACT = 2,
  TRAIN = 3,
  TRAIN_COMPLETE = 4,
  SCAN_RANGE = 5,
};

enum actuator_direction
{
	EXTEND,
	RETRACT,
	STATIONARY
};

enum relay_setting {
  ACTIVATED = 0,  // LOW
  DEACTIVATED =1  // HIGH
};

#endif