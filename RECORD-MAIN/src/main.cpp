#include "main.h"
#include "drive.h"

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
	FILE* file = fopen("/usd/1010H.txt", "w"); //open a file named 1010H
		int time = 0; //reset timer

	while (time < 14500) { //if less than 14.5 seconds has elapsed...

		fprintf(file, "%f\n", getVelocity(driveRB)); //record velocity values for drive base motors
		fprintf(file, "%f\n", getVelocity(driveLB)); //record velocity values for drive base motors
		fprintf(file, "%f\n", getVelocity(driveRF)); //record velocity values for drive base motors
		fprintf(file, "%f\n", getVelocity(driveLF)); //record velocity values for drive base motors
		fprintf(file, "%f\n", getVelocity(rClaw)); //record velocity values for intake motors
		fprintf(file, "%f\n", getVelocity(lClaw)); //record velocity values for intake motors
		fprintf(file, "%f\n", getVelocity(roller)); //record velocity values for roller motors
		fprintf(file, "%f\n", getVelocity(futureUse4)); //record velocity values for flywheel motors

		int POS; //setting up holdposition PID for flywheel
		base.opControl(); //run drive base function
		movingParts.Rollers(); //run rolling parts function (flywheel, intakes, rollers)
		if(master.get_digital(DIGITAL_L1)){ //flywheel funciton: if L1 pressed...
      futureUse4.move(127); //move flywheel 100% forwards
    }
    else if(master.get_digital(DIGITAL_L2)){ //if L2 pressed...
      futureUse4.move(-127); //move flywheel backwards 100%
    }
    else{futureUse4.move_absolute(0, POS);} //otherwise, hold flywheel position
		pros::delay(10); //delay for rerun
		time +=10; //timer for rerun
	}
	if (time > 14500) { //if more than 14.5 seconds has elapsed
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
