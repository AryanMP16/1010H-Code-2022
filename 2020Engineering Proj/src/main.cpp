#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
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

//motors
	Motor driveLF(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor driveRF(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveRB(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveLB(4, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
//tasks
pros::Task acc_task(
	AccTask_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "TEST_TASK"
);
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

//motors
	driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
//Vision Sensor
	Vision cam1 (20, E_VISION_ZERO_CENTER);
	cam1.clear_led();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//example of drive and turn PIDs:
	chassis.movePID(FORWARD, 123, 1234, 123);
	chassis.turnPID(LEFT, NINETY_DEG, 1234);
	chassis.strafePID(LEFT_STRAFE, 123, 1234, 123);
	chassis.stop();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {
		int count; //counter/timer (used to measure time for controller shake)
		//example of controller shake code:
		if (count >= 95000) {master.rumble("___ .___");} //when 1:35 in operator control, shake controller
		else {}
		//example of expo drive:
		base.opControl();
		//example of temperature control
		base.temperatureControl();

		pros::delay(10);
		count +=10;
	}
}
