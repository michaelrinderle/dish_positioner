#ifndef _ACTUATOR_h
#define _ACTUATOR_h

#include "constants.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

long position;
long position_end;
int  position_trained = FALSE;

long pulse_total = 0;

void sensor1_isr();
long get_pulses_to_inches();

void actuator_init()
{
	// setup relay inputs
	pinMode(PIN_RELAY_INPUT_1, OUTPUT);
	pinMode(PIN_RELAY_INPUT_2, OUTPUT);

	// initialize relay pins
	digitalWrite(PIN_RELAY_INPUT_1, DEACTIVATED);
	digitalWrite(PIN_RELAY_INPUT_2, DEACTIVATED);

	// enable internal resister for the inputs pins
	pinMode(PIN_SENSOR_INTERRUPT_1, RISING);
	
	// read the initial state of the inputs
	PULSE_SENSOR_1 = digitalRead(PIN_SENSOR_INTERRUPT_1);

	// will detect a rising or a falling edge
	attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_INTERRUPT_1), sensor1_isr, CHANGE);
}

void actuator_stop()
{
	digitalWrite(PIN_RELAY_INPUT_1, DEACTIVATED);
	digitalWrite(PIN_RELAY_INPUT_2, DEACTIVATED);
}

long actuator_extend(long duration)
{
	if(position_trained == TRUE && 
	   position == position_end) return NULL;

	position++;
	
	digitalWrite(PIN_RELAY_INPUT_1, ACTIVATED);
	digitalWrite(PIN_RELAY_INPUT_2, DEACTIVATED);

	delay(duration);
	actuator_stop();

	return position;
}

long actuator_retract(long duration)
{
	if(position_trained == TRUE && 
	   position == 0) return NULL;

	position--;
	
	digitalWrite(PIN_RELAY_INPUT_1, DEACTIVATED);
	digitalWrite(PIN_RELAY_INPUT_2, ACTIVATED);

	delay(duration);
	actuator_stop();

	return position;
}

void actuator_detect_retract_position()
{
	while(true)
	{
		pulse_total = 0;
		actuator_retract(INCH_OF_TRAVEL_PER_SECOND);
		// absolutely no travel detected
		if(pulse_total == 0)
		{
			position = 0;
			break;
		}
	}
}

void actuator_detect_extend_range()
{
	while(true)
	{
		pulse_total = 0;
		actuator_extend(INCH_OF_TRAVEL_PER_SECOND);
		
		position++;
		
		// confirm pulses
		if(pulse_total > 0)
		{
			position++;
			continue;
		}

		position_end = position;
		position_trained = TRUE;		
		break;
	}
}

void actuator_train()
{
	actuator_detect_retract_position();
	actuator_detect_extend_range();	
}

void sensor1_isr() {
	PULSE_SENSOR_1 = !PULSE_SENSOR_1;
	pulse_total++;
	Serial.println("[*] Sensor 1");
}

long get_pulses_to_inches()
{
	long pulse_start = pulse_total;
	actuator_extend(INCH_OF_TRAVEL_PER_SECOND);
	return pulse_total - pulse_start;
}

#endif

