/**************************************************************************
	FileName		[ cnc_stepper.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Stepper Related Class in CNC Project ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

class CNC_Stepper
{
public:
	CNC_Stepper(float period,
				unsigned int st_pin,
				unsigned int dir_pin,
				unsigned int ena_pin){

		period_per_step = period;
		// unit becomes miliseconds
		step_pin = st_pin;
		direction_pin = dir_pin;
		enable_pin = ena_pin;

		now_pos = 0;
		enabled = false;
		inverted = false;
	}
	~CNC_Stepper() {};

	/**************** Settings start ****************/
		void init(bool invert = false){
			inverted = invert;
			pinMode(step_pin, OUTPUT);
			pinMode(direction_pin, OUTPUT);
			pinMode(enable_pin, OUTPUT);

			enable();
		}

		void setEndstop(unsigned int end_pin, bool end_inv = false){
			// this function can only be called in setup() in main.ino
			endstop_pin = end_pin;
			endstop_inverted = end_inv;

			pinMode(endstop_pin, INPUT_PULLUP);
		}
	/**************** Settings end ****************/

	/**************** Moving start ****************/
		void homing(){
			// keep going on one single direction until hit endstop
			// and set that position as 0
			now_pos = 0;
			int small_step = -1;

			#ifdef DEBUG
				Serial.println("CNC_Stepper: homing called...");
			#endif

			digitalWrite(direction_pin, HIGH);

			while(get_endstop() == endstop_inverted){
				// step(small_step);
				digitalWrite(step_pin, LOW);
				delayMicroseconds(Homing_Delay);
				digitalWrite(step_pin, HIGH);
			}

			#ifdef DEBUG
				Serial.println("CNC_Stepper: homing done !!");
			#endif
		}

		bool get_endstop(){
			return digitalRead(endstop_pin);
		}

		int get_pos() { return now_pos; }

		void set_pos(int new_pos) { // force to set now_pos
			now_pos = new_pos;
		}
	/**************** Moving end ****************/

	/**************** Enable start ****************/
		void enable(bool b = true){ // enable the motor for manual control
			enabled = b;
			if(b){
				digitalWrite(enable_pin, HIGH);
			}
			else{
				digitalWrite(enable_pin, LOW);
			}
		}

		void disable(bool b = true){ // machine overtaking the control
			enabled = !b;
			if(b){
				digitalWrite(enable_pin, LOW);
			}
			else{
				digitalWrite(enable_pin, HIGH);
			}
		}

		bool get_enable() { return enabled; }

		unsigned int get_step_pin(){ return step_pin; }
		unsigned int get_direction_pin(){ return direction_pin; }
		bool inverted_status(){ return inverted; }
		void new_pos(int x){ now_pos += x; }
	/**************** Enable end ****************/

private:
	bool			inverted;
	// inverted means that if the motor is plugged in inverted
	// this means that the motor will turn the opposite direction
	// so we need this bool to distinguish
	bool			enabled;
	// enable means that if human can turn the motor by hand
	// motor should be disabled during machine process
	// and enable by enable()
	// not sure if we can do enable() after a process is done
	// so that the motor won't keep making noise while halt
	bool			endstop_inverted;
	// if the endstop's output is inverted
	// would like to set to 0 if homing is not done
	// and set 1 if the machine hits the endstop
	// if endstop inverted, 1 for not done 0 for hit

	unsigned int	step_pin;
	unsigned int	direction_pin;

	unsigned int	enable_pin;
	unsigned int	endstop_pin;

	int				now_pos;
	// the unit of now_pos should be steps

	float			period_per_step;
	// the unit of period_per_step is microseconds
	// but init puts miliseconds
};
