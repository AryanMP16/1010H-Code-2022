#include "main.h"
#include "display.h"
#include <iostream>
#include <string>
#include <cstring>
	bool False = true;
	Display screen;

	//drive objects
	dpidClass chassis;
	opClass base;
	opClass movingParts;
	//motors
	Motor futureUse4(17, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //CAP LIFT
	Motor driveRB(15, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor lClaw(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor roller(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor rClaw(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveRF(16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor driveLF(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveLB(19, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	int time=0;
	Distance backR (14);
	Distance backL (9);

void initialize() {
	//motors
	screen.createScreen();
	screen.refresh();
	//motors
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE); //brake hold on drive base motors
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	//tasks
	pros::Task acc_task(
		AccTask_fn, (void*)"PROS", TASK_PRIORITY_MIN, TASK_STACK_DEPTH_MIN, "TEST_TASK" //task for rollers
	);
}

void disabled() {}
void competition_initialize() {}
void autonomous() {
	futureUse4.tare_position();
	Run();
}

  int exponentialD(int joyVal, float driveExpon, int joystkDead, int motorMin){
  int joystkSign;
  int joyMax = 127 - joystkDead;
  int joyLive = abs(joyVal) - joystkDead;
  if (joyVal > 0) joystkSign = 1;
  else if (joyVal < 0) joystkSign = -1;
  else joystkSign = 0;
  int power = joystkSign * (motorMin + (127 - motorMin) * pow(joyLive, driveExpon) / pow(joyMax, driveExpon));
  return power;}

  int DIR = 1;
  int RECState = 0;

void opcontrol() {
	FILE* file = fopen("/usd/1010H.txt", "w"); //open a file named 1010H
		int time;

	while(true){
		screen.refresh();
		switch(RECState) {
			case 1:
				time = 0; //reset timer
				while (time < 15000) {
					lv_led_on(led1);
					int Y = exponentialD(master.get_analog(ANALOG_LEFT_Y), 1.7, 8, 15);
					//int X = exponentialD(master.get_analog(ANALOG_LEFT_X), 1.7, 8, 15);
					int Z = exponentialD(master.get_analog(ANALOG_RIGHT_X), 1.7, 8, 15);
					driveLB.move((DIR * (-Y)) /*- X*/ - Z);
					driveRF.move((DIR * (-Y)) /*- X*/ + Z);
					driveLF.move((DIR * (-Y)) /*+ X*/ - Z);
					driveRB.move((DIR * (-Y)) /*+ X*/ + Z);

					if(master.get_digital(DIGITAL_X)){
						DIR = 1;
					} 
					if (master.get_digital(DIGITAL_B)){
					DIR = -1;
					}
					movingParts.Rollers(); //using function for rollers, conveyor, and intakes
					//main loop					
					fprintf(file, "%d\n", ((DIR * (-Y)) /*+ X*/ + Z)); //record velocity values for drive base motors
					fprintf(file, "%d\n", ((DIR * (-Y)) /*- X*/ - Z)); //record velocity values for drive base motors
					fprintf(file, "%d\n", ((DIR * (-Y)) /*- X*/ + Z)); //record velocity values for drive base motors
					fprintf(file, "%d\n", ((DIR * (-Y)) /*+ X*/ - Z)); //record velocity values for drive base motors
					fprintf(file, "%f\n", getVelocity(rClaw)); //record velocity values for intake motors
					fprintf(file, "%f\n", getVelocity(lClaw)); //record velocity values for intake motors
					fprintf(file, "%f\n", getVelocity(roller)); //record velocity values for roller motors
					fprintf(file, "%d\n", clawTargetR); //FORMERLY: fprintf(file, "%f\n", getVelocity(futureUse4));

					delay(10);
					time += 10;
				}
				if (time > 15000) {
					driveRB.move_velocity(0); //DO NOT MOVE ANY MOTORS
					driveLB.move_velocity(0);
					driveRF.move_velocity(0);
					driveLF.move_velocity(0);
					rClaw.move_velocity(0);
					lClaw.move_velocity(0);
					roller.move_velocity(0);
					futureUse4.move_velocity(0);
				}
				fclose(file); //close file
				break;
			default:
				time = 0; //reset timer
				int Y = exponentialD(master.get_analog(ANALOG_LEFT_Y), 1.7, 8, 15);
				//int X = exponentialD(master.get_analog(ANALOG_LEFT_X), 1.7, 8, 15);
				int Z = exponentialD(master.get_analog(ANALOG_RIGHT_X), 1.7, 8, 15);
				driveLB.move((DIR * (-Y)) /*- X*/ - Z);
				driveRF.move((DIR * (-Y)) /*- X*/ + Z);
				driveLF.move((DIR * (-Y)) /*+ X*/ - Z);
				driveRB.move((DIR * (-Y)) /*+ X*/ + Z);

				if(master.get_digital(DIGITAL_X)){
					DIR = 1;
				} 
				if (master.get_digital(DIGITAL_B)){
				DIR = -1;
				}
				movingParts.Rollers(); //using function for rollers, conveyor, and intakes
				time = 0; //reset timer
				delay(10);
				time+=10;
		}
	}
}
