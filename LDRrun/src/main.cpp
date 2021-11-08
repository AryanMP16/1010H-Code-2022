#include "main.h"
#include "display.h"
#include <iostream>
#include <string>
#include <cstring>

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

void opcontrol() {
	//timer
	int time;
	time = 0;

	ADIUltrasonic sensor ('A'/*ping*/, 'B'/*echo*/); //ultrasonic sensor initialization

	while (true) { //main loop
		/*if (master.get_digital(DIGITAL_A) && backR.get() >= 20){ //if button A is pressed...
			roller.move_velocity(200); //move robot roller 100%
		}
		else{
			roller.move(0); //DO NOT move robot roller
		}*/

		cout << "Distance ultrasonic: " << sensor.get_value() << " || Line sensor value:" << (outer_limitR.get_value()-33) << "\n";  // display ultrasonic value

		base.opControl(); //using function for drive base
		movingParts.Rollers(); //using function for rollers, conveyor, and intakes
	}
}
