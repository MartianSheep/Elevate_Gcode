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

			Serial.println(period_per_step);
		}

		void setEndstop(unsigned int end_pin, bool end_inv = false){
			// this function can only be called in setup() in main.ino
			endstop_pin = end_pin;
			endstop_inverted = end_inv;

			pinMode(endstop_pin, OUTPUT);
		}
	/**************** Settings end ****************/

	/**************** Moving start ****************/
		void step(int steps = 1){ // moving the motor by giving steps
			disable();

			if(steps < 0){
				digitalWrite(direction_pin, HIGH);
				steps = -steps;
			}
			else{
				digitalWrite(direction_pin, LOW);
			}

			for(int i = 0; i < steps; ++i){
				digitalWrite(step_pin, HIGH);
				delay(period_per_step/2);
				digitalWrite(step_pin, LOW);
				delay(period_per_step/2);
			}

		}

		void homing(){
			// keep going on one single direction until hit endstop
			// and set that position as 0
			now_pos = 0;
			int small_step = 1;

			while(get_endstop() == endstop_inverted){
				step(small_step);
			}
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

	// unsigned int	steps_per_round;
	unsigned int	step_pin;
	unsigned int	direction_pin;

	unsigned int	enable_pin;
	unsigned int	endstop_pin;

	int				now_pos;

	float			period_per_step;
	// the unit of now_pos should be steps
};