#include "main.h"
#include "drive.h"

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
	Motor driveLF(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor driveRF(6, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor driveRB(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor driveLB(5, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor lClaw(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor rClaw(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor roller(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor futureUse4(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "falsdkfjalsdkjflaskfjaslkdfj");
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
}

void opcontrol() {
	FILE* file = fopen("/usd/1010H.txt", "w");
		int time = 0;
	while (time < 14500) {
		switch(clawStat){
			case IN:
				clawTarget = 0;
				break;

			case MID:
				clawTarget = -500;
				break;

			case OUT:
				clawTarget = -1000;
				break;

			default:
				clawStat = IN;
				break;
		};

		fprintf(file, "%f\n", getVelocity(driveRB));
		fprintf(file, "%f\n", getVelocity(driveLB));
		fprintf(file, "%f\n", getVelocity(driveRF));
		fprintf(file, "%f\n", getVelocity(driveLF));
		fprintf(file, "%i\n", clawStat);
		fprintf(file, "%f\n", getVelocity(roller));
		fprintf(file, "%f\n", getVelocity(futureUse4));

		if(master.get_digital(DIGITAL_L1))
			futureUse4.move(127);
		else if(master.get_digital(DIGITAL_L2))
			futureUse4.move(-127);
		else
			futureUse4.move(0);

		base.opControl();
		movingParts.Rollers();
		printf("%d\n", 1);
		pros::delay(10);
		time +=10;
	}
	if (time > 14500) {
		driveRB.move_velocity(0);
		driveLB.move_velocity(0);
		driveRF.move_velocity(0);
		driveLF.move_velocity(0);
		rClaw.move_velocity(0);
		lClaw.move_velocity(0);
		roller.move_velocity(0);
		futureUse4.move_velocity(0);
	}
	fclose(file);
}
