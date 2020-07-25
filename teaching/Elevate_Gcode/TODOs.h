#include "motor/motor_driver.h"

    /**************** Pen_Degree Start ****************/
    void Pen_Degree(int degree){

		//TODO
        Pen_Servo.write(degree);
        delay(Pen_Delay_Time);

	}

    /**************** Pen_Degree End ****************/

    /**************** Y_next Start ****************/

    char Y_next(float &tx, float &ty, float Y_period ){
        // TODO
        // 
        char flag;

        tx -= ty;
        ty = Y_period;
        if(ty>tx) flag = 'X';
        else if(tx == ty) flag = 'E';

        return flag;
    }

    /**************** Y_next End ****************/

    /**************** Move Start ****************/

    void Move(int step_pin){
        //TODO
        digitalWrite(step_pin, LOW);

		delayMicroseconds(200);

		digitalWrite(step_pin, HIGH);
    }

    /**************** Move Start ****************/
/**************** G-code Translator start ****************/
	void G_Code_Translator(int num, vector<String> v){

		float X = X_coordinate();
		float Y = Y_coordinate();
		for (int i=0; i<v.size();i++){
			String param = v[i];
			char param_type = param.charAt(0);
			switch(param_type){
				case 'X':
					param = param.substring(1,param.length());
					X = param.toFloat();
					break;
				case 'Y':
					param = param.substring(1,param.length());
					Y = param.toFloat();
					break;
				default:
					Serial.println("Gcode Translator: ");
					Serial.println(param_type);
					Serial.println("Error, other params");
					return;
			}
		}

		switch(num){
			case 0:
				// G0: Linear move without extrusion(but we don't have that at first)
				//     so I think it's a seperator between each curve;
				//TODO
                
                Move_to(X,Y);
				break;
			case 1:
				// G1: Linear move with extrusion, which would really draw a line;
				//TODO
                
                Move_Stepper_Linear(X,Y);
				break;
			case 21:
				// G21: set units to milimeters;
				break;
			case 28:
				//TODO
                X_homing();
                Y_homing();
				break;
			case 90:
				// G90: set coordinate to absolute;
				break;
			case 92:
				// G92: set position and return now position;
				if(X != X_coordinate())
					set_X_coordinate(X);
				if(Y != Y_coordinate())
					set_Y_coordinate(Y);
				Serial.print("Now Position: (");
				Serial.print( X_coordinate() );
				Serial.print(',');
				Serial.print( Y_coordinate() );
				Serial.print(')');
				Serial.println();
				break;
			default:
				Serial.println("Error, command not implemented");
				break;
		}
		return;
	}
	/**************** G-code Translator end ****************/
