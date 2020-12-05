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
Motor driveLF(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRF(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveRB(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveLB(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor futureUse1(5, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor futureUse2(6, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor futureUse3(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor futureUse4(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
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
	/*chassis.movePID(FORWARD, 123, 1234, 123);
	chassis.turnPID(LEFT, NINETY_DEG, 1234);
	chassis.strafePID(LEFT_STRAFE, 123, 1234, 123);
	chassis.stop();*/
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

	//Vision cams(10);
		int time;
		time = 0;

		FILE* file = fopen("/usd/example.txt", "w"); //opening the file to record to

	while (time<14500) {

		//recording from drive Motors
 				fprintf(file, "%f\n", getVelocity(driveRB)); //recording from the right back drive motor
 				fprintf(file, "%f\n", getVelocity(driveRF)); //recording from the right front drive motor
 				fprintf(file, "%f\n", getVelocity(driveLB)); //recording from the left back drive motor
 				fprintf(file, "%f\n", getVelocity(driveLF)); //recording from the left back drive motor
				fprintf(file, "%f\n", getVelocity(futureUse1)); //recording from the right back drive motor
				fprintf(file, "%f\n", getVelocity(futureUse2)); //recording from the right front drive motor
				fprintf(file, "%f\n", getVelocity(futureUse3)); //recording from the left back drive motor
				fprintf(file, "%f\n", getVelocity(futureUse4)); //recording from the left back drive motor

		base.opControl();

		if(master.get_digital(DIGITAL_A)){
			driveLB.move(127);
		}
		else if(master.get_digital(DIGITAL_B)){
			driveRB.move(127);
		}
		else if(master.get_digital(DIGITAL_Y)){
			driveLF.move(127);
		}
		else if(master.get_digital(DIGITAL_X)){
			driveRF.move(127);
		}
		else{}

		pros::delay(10);
		time +=10;

		if (time > 14500) { //if the program surpasses 14500 milliseconds, it will not continue recording
 			driveLB.move(0); //the left back drive motor will stop moving, and thus, stop recording
 			driveLF.move(0); //the left front drive motor will stop moving, and thus, stop recording
 			driveRB.move(0); //the right back drive motor will stop moving, and thus, stop recording
 			driveRF.move(0); //the right front drive motor will stop moving, and thus, stop recording
 		}
	}
	fclose(file); //close the file to stop recording
}

//vision_color_code_t codeBLUE = cams.create_color_code(1, 2);
//vision_object_s_t rtn = cams.get_by_sig(0, codeBLUE);

//std::cout << "sig:" << rtn.signature << " Time:" << (time+=10) << " milliseconds" << "\n";