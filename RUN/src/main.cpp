#include "main.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
	//drive objects
	dpidClass chassis;
	opClass base;
	opClass movingParts;
	//motors
	Motor futureUse4(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveRB(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor lClaw(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor roller(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor rClaw(5, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveRF(6, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor driveLF(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveLB(9, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "DISCLAIMER: This robot has consumed an phat dose of methinphetamine and is therefore required to go ape shit on you");
	pros::lcd::register_btn1_cb(on_center_button);
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
	Run();
}
ADIAnalogIn crashSensor ('A');
void opcontrol() {
		int time;
		time = 0;
	while (true) {
		base.opControl();
		movingParts.Rollers();
		pros::delay(10);
		time +=10;
	}
}
