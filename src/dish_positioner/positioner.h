//    __ _/| _/. _  ._/__ /
// _\/_// /_///_// / /_|/
//            _/
// sof digital 2021
// written by michael rinderle <michael@sofdigital.net>

// mit license
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _POSITIONER_h
#define _POSITIONER_h

#include "actuator.h"
#include "constants.h"

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


