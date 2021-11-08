#include "main.h"
#include "display.h"
#include <iostream>
#include <string>
#include <cstring>

	Display screen;

	int False = true;
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
	Distance backR (20);
	Distance backL (11);

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
		AccTask_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "TEST_TASK" //task for rollers
	);

	pros::Task disp_task(
		DispTask_fn, (void*)"PROS", TASK_PRIORITY_MIN, TASK_STACK_DEPTH_DEFAULT, "X_TASK"
	);
}

void disabled() {}
void competition_initialize() {}
void autonomous() {
	futureUse4.tare_position();
	Run();
}
//Mathias J. Stiasny actually wrote this code. Aryan is keeping me hostage. please help. i don't have long
void opcontrol() {
		int time;
		time = 0;
	while (False) {
		int POS; //using for holdposition PID for flywheel
		 //otherwise, hold the flywheel at its current position
		base.opControl(); //using functi	on for drive base
		movingParts.Rollers(); //using function for rollers, flywheel, and intakes
		cout << clawTargetR << "\n";
	}
}
