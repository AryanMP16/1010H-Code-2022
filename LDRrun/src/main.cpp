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

void opcontrol() {
	//timer
	int time;
	time = 0;


	while (False) { //main loop
		screen.refresh();
		/*if(master.get_digital(DIGITAL_RIGHT)){
			chassis.swervePID(1, 1, 1, 1, 1000, 0.012, 0.012);
		}
		else{
			driveRF.move_velocity(0);
		  driveRB.move_velocity(0);
		  driveLF.move_velocity(0);
		  driveLB.move_velocity(0);
		}*/
		base.opControl(); //using function for drive base
		movingParts.Rollers(); //using function for rollers, conveyor, and intakes
		delay(20);
	}
}
