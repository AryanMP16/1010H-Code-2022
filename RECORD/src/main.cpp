#include "main.h"
#include "drive.h"

	//drive objects
	dpidClass chassis;
	opClass base;
	opClass movingParts;
//motors
Motor futureUse4(17, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //CAP LIFT
	Motor driveRB(15, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor lClaw(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor roller(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //NOW INTAKE
	Motor rClaw(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveRF(16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor driveLF(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveLB(19, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

void initialize() { 
	pros::lcd::initialize();
//motors
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	//tasks
	pros::Task acc_task(
		AccTask_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "TEST_TASK"
	);
}
void disabled() {}
void competition_initialize() {}
void autonomous() {
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

void opcontrol() {
	FILE* file = fopen("/usd/1010H.txt", "w"); //open a file named 1010H
		int time = 0; //reset timer

	while (time < 15000) {
		if(master.get_digital(DIGITAL_R1)){futureUse4.move_velocity(-200);}
		else if(master.get_digital(DIGITAL_R2)){futureUse4.move_velocity(200);}
		else{futureUse4.move_velocity(0);}

		 //if less than 14.5 seconds has elapsed...
		//testing upload to github
		int Y = exponentialD(master.get_analog(ANALOG_LEFT_Y), 1.7, 8, 15);
		int Z = exponentialD(master.get_analog(ANALOG_RIGHT_X), 1.7, 8, 15);
		driveLB.move((DIR * (-Y)) /*- X*/ - Z);
		driveRF.move((DIR * (-Y)) /*- X*/ + Z);
		driveLF.move((DIR * (-Y)) /*+ X*/ - Z);
		driveRB.move((DIR * (-Y)) /*+ X*/ + Z);

		if(master.get_digital(DIGITAL_X)){
			DIR = -1;
			}
		if (master.get_digital(DIGITAL_B)){
				DIR = 1;
			}

		fprintf(file, "%d\n", ((DIR * (-Y)) /*+ X*/ + Z)); //record velocity values for drive base motors
		fprintf(file, "%d\n", ((DIR * (-Y)) /*- X*/ - Z)); //record velocity values for drive base motors
		fprintf(file, "%d\n", ((DIR * (-Y)) /*- X*/ + Z)); //record velocity values for drive base motors
		fprintf(file, "%d\n", ((DIR * (-Y)) /*+ X*/ - Z)); //record velocity values for drive base motors
		fprintf(file, "%f\n", getVelocity(rClaw)); //record velocity values for intake motors
		fprintf(file, "%f\n", getVelocity(lClaw)); //record velocity values for intake motors
		fprintf(file, "%f\n", getVelocity(roller)); //record velocity values for roller motors
		fprintf(file, "%d\n", clawTargetR); //FORMERLY: fprintf(file, "%f\n", getVelocity(futureUse4));

		movingParts.Rollers();

		pros::delay(10); //delay for rerun
		time +=10; //timer for rerun
	}
	if (time > 15000) { //if more than 14.5 seconds has elapsed
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
}
