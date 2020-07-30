/**************************************************************************
	FileName		[ Elevate_Gcode.ino ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Firmware for the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#include "configuration.h"
#include "gcode/gcode_translators.h"
#include "motor/motor_driver.h"

void setup() {
	Serial.begin(Baudrate);

	Pen_init(Servo_Pin);

	X_Stepper.init(X_Stepper_Invert);
	X_Stepper.setEndstop(X_Endstop_Pin, X_Endstop_Invert);
	Y_Stepper.init(Y_Stepper_Invert);
	Y_Stepper.setEndstop(Y_Endstop_Pin, Y_Endstop_Invert);
}

//String cmd = "";
//vector<String> params;

//void loop() {
//	if(Serial.available()){
//		cmd = Serial.readStringUntil('\n'); // read in command
//		if (cmd!=""){
//			params = Gcode_Parser(cmd); // parse and return params
//			Seperator(params); // seperate to G/M translator => motor driving 
//      Serial.write("complete\n");
//		}
//	}
//}

int sofar = 0;
const int MAX_BUF = 100; //need define;
char buf[MAX_BUF];
vector<vector<char>> params;

void loop(){
  
  if( Serial.available()){
  
    char c = Serial.read();
//    Serial.println(c);
    if ( sofar < MAX_BUF ) {
      buf[sofar++]=c;
      if (c == '\n'){
//        Serial.println('S');
        buf[sofar]=0;
        params = Gcode_Parser(buf,sofar);
        Seperator(params);
        Serial.write("complete\n");
        sofar = 0;
//        delay(500);
      }
     }
    
    }
      
  
  }
