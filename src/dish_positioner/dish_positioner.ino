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

/*
    Name:       dish_positioner.ino

    // ln -s /mnt/sda1/arduino/www/ /www/sd
  // Listen on default port 5555, the web server on the Yún
  // will forward there all the HTTP requests for us.
*/

#include "positioner.h"
#include "constants.h"

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;
YunClient client;

void setup() {

	Serial.begin(9600); 
	Serial.println("[*] SAT-POS Started");
  
	Bridge.begin();

	server.listenOnLocalhost();
	server.begin();
  
	pinMode(PIN_ACTION_LED_1, OUTPUT);

	positioner_init();
}

void loop() { 

  client = server.accept();
  client.setTimeout(5);
  
  if (client) {
  	
    digitalWrite(PIN_ACTION_LED_1, HIGH);
  	
    String command = client.readStringUntil('/');
    command.trim();
  	
    if (command == "satellitepositioner") {
    	
      const int url_choice = client.parseInt();
      switch(url_choice) {
        
        case ANGLE : {
          client.print(positioner_get_angle());
          break;
        }
        case ANGLE_EXTEND : {
           client.print(positioner_extend());
           break;
        }
        case ANGLE_RETRACT : {
          client.print(positioner_retract());
          break;
        }
        case TRAIN : {
          client.print(positioner_train());
          break;
        }
      	case TRAIN_COMPLETE : {
          client.print(positioner_is_limits_set());
          break;
        }
        case SCAN_RANGE : {
          client.print(positioner_scan_range());
          break;
        }
        default:{
        	client.print(positioner_dynamic_command(url_choice));	
            break;
        }
      }
    }

    client.stop();
    client.flush();
    digitalWrite(PIN_ACTION_LED_1, LOW);
  }   
}
