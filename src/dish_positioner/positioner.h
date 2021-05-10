#ifndef _POSITIONER_h
#define _POSITIONER_h

#include "actuator.h"
#include "constants.h"0

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void positioner_init()
{
	actuator_init();
}

int positioner_get_angle()
{
	return position;
} 

int positioner_is_limits_set()
{
	return position_trained;
}

long positioner_extend()
{
	return actuator_extend(INCH_OF_TRAVEL_PER_SECOND);
}

long positioner_retract()
{
	return actuator_retract(INCH_OF_TRAVEL_PER_SECOND);
}

char* positioner_train()
{
	actuator_train();
	return "Position trained successfully";
}

char* positioner_scan_range(){

	if(position_trained == FALSE) return "Positioner not trained.";

	const int current_position = position;
	
	// scan to fully retracted
	while(position > 0)
	{
		positioner_retract();
		position--;
	}

	delay(1000);

	// scan to fully extended
	while(position < position_end)
	{
		positioner_extend();
		position++;
	}

	delay(1000);
	
	// scan back to original location
	while(position > current_position)
	{
		positioner_retract();
		position--;
	}

	return "Scan Complete";
}

char* positioner_dynamic_command(int command){
	return "command";
}

#endif


