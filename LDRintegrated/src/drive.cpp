#include "main.h"
#include "drive.h"
int clawTargetR;
int clawTargetL;
int bingBongTarg;
ADIAnalogIn outer_limitL ('E');
ADIAnalogIn outer_limitR ('H');
//____________________________________________________________________________//
/////////////////////////////EXPO DRIVE FUNC////////////////////////////////////
//____________________________________________________________________________//
Controller master (CONTROLLER_MASTER); //
//expo drive
//____________________________________________________________________________//
/////////////////////////////GET VELOCITY FUNC//////////////////////////////////
//____________________________________________________________________________//
    double getVelocity(Motor motor) {
      return motor.get_actual_velocity(); //return velocity of motor
    };

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////ROLLER INTAKE FUNC/////////////////////////////////
//____________________________________________________________________________//
Controller partner (CONTROLLER_PARTNER);
void opClass::Rollers() {
  int BUILT_DIFFERENT = futureUse4.get_position();
  if(master.get_digital(DIGITAL_L1)){clawTargetR = 350;}
  else if(master.get_digital(DIGITAL_L2)){clawTargetR = 980;}
  else{futureUse4.move_absolute(BUILT_DIFFERENT,0);}

  if(master.get_digital(DIGITAL_R2)){roller.move_velocity(-600);} //REMOVE COMMENTS ON THIS//////////////////////////
  else if(master.get_digital(DIGITAL_R1)){roller.move_velocity(600);}
  else if (master.get_digital(DIGITAL_UP)){bingBongTarg = 200;}
  else if (master.get_digital(DIGITAL_DOWN)){bingBongTarg = -200;}
  else{roller.move_velocity(0);}
  };
  //____________________________________________________________________________//
  ///////////////////////////TASK FUNCTION NUMBER ONE/////////////////////////////
  //____________________________________________________________________________//
void AccTask_fn(void*par) {
  futureUse4.tare_position();

  clawTargetR = 0;

  while (true) {
    int error, sumError, diffError, errorLast, output;
    int BUILT_DIFFERENT;

		float kP = 0.9;
		float kI = 0;
		float kD = 1.5;

		error = clawTargetR - rClaw.get_position(); //error value equals arm target minus the arm's current position
		sumError += error; //sum error is defined as the error plus the sum of the error
		diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
		rClaw.move((error * kP) + (sumError * kI) + (diffError * kD)); //arm will move according to kp, ki, and kd values
		lClaw.move((error * kP) + (sumError * kI) + (diffError * kD));
    errorLast = error; //error last is defined as error

    }
};
//____________________________________________________________________________//
/////////////////////////////////SWERVE PID///////////////////////////////////////
//____________________________________________________________________________//
void dpidClass::swervePID(int L_or_R, int angle, int radius, int length, int timeout, float gain, float loss){
  float vR=200;
  float vL;
  float vL_Last;
  float vR_Last;
  int startTime = millis();
  float time=0;
////////////////////////////////////////////
while((millis() - startTime) < (timeout)){
  time+= 0.06192190192;
  if (time < (timeout)){
    if(vL < 200){
      vL+=gain;
    }
    else{
      vL = 200;
    }

    if(vR > 65){
      vR-=loss;
    }
    else{
      vR = 65;
    }
  }
  cout << "VEL: " <<driveLF.get_actual_velocity()<<"  TIME: "<<time<<"\n";
//////////////////////////////
  driveRF.move_velocity(vR);//
  driveRB.move_velocity(vR);//
//~~~~~~~~~~~~~~~~~~~~~~~~~///
  driveLF.move_velocity(vL);//
  driveLB.move_velocity(vL);//
//////////////////////////////
  }
  time = 99999999999;
}



//____________________________________________________________________________//
////////////////////////////Don't crash into others/////////////////////////////
//____________________________________________________________________________//
bool goingToCrash;
void dont() { //meme function
  driveLB.move_absolute(driveLB.get_position(),0);
  driveRF.move_absolute(driveRF.get_position(),0);
  driveLF.move_absolute(driveLF.get_position(),0);
  driveRB.move_absolute(driveRB.get_position(),0);
}
//____________________________________________________________________________//
/////////////////////////////////STOP FUNC//////////////////////////////////////
//____________________________________________________________________________//
void dpidClass::stop (void) { //PID stop fucntion
      driveLB.move(0); //do not move motors
      driveRB.move(0);
      driveLF.move(0);
      driveRF.move(0);
  	};
//____________________________________________________________________________//
/////////////////////////////////MOVE PID///////////////////////////////////////
//____________________________________________________________________________//
void dpidClass::movePID(int direction, int target, int timeout, int cap) {
  //variables
    float kP = 0.7; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    float kI = 0; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    float kD = 1.1; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    int error = 0;
    int diffError = 0;
    int errorLast = 0;
    int sumError = 0;
    int power;
    int cp = 0;
    float p;
    float d;
    float i = 0; //integral
  	int startTime = millis();

    driveLB.tare_position(); //reset motor value

  	while((millis() - startTime) < timeout){ //while the timeout has not expired
  			error = target - driveLB.get_position(); //find error by subracting target from current pos
  			sumError += error;
  			diffError = error - errorLast;
        errorLast = error; //store last error value
        p = kP * error; //proportional
        d = kD * diffError; //derivative

        power = p+i+d;

        driveLB.move(direction * power); //direction as 1 will make it move forwards, -1 backwards
        driveLF.move(direction * power);
        driveRB.move(direction * power);
        driveRF.move(direction * power);

        if(power > cap){power = cap;} //cap motor speed
        if(power < -cap){power = -cap;}

        delay(10);
  	}
};
//____________________________________________________________________________//
/////////////////////////////////TURN PID///////////////////////////////////////
//____________________________________________________________________________//
void dpidClass::turnPID(int direction, int target, int timeout) {
  //variables
    float kP = 0.7; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    float kI = 0; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    float kD = 1.1; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    int error = 0;
    int diffError = 0;
    int errorLast = 0;
    int sumError = 0;
    int power;
    int cp = 0;
    float p;
    float d;
    float i = 0; //integral
  	int startTime = millis();

    driveRB.tare_position();
    driveLB.tare_position();

    while((millis() - startTime) < timeout){ //while the timeout has not expired
        cp = abs(direction == 1 ? driveLB.get_position() : driveRB.get_position()); //if abs() is not there, we can't find proper target in the next line
        error = target - cp; //find error by subracting target from current pos
  			sumError += error;
  			diffError = error - errorLast;
        errorLast = error; //store last error value
        p = kP * error; //proportional
        d = kD * diffError; //derivative

        power = p+i+d;

        driveLB.move(-direction * power); //direction as 1 will make it turn left, -1 right
        driveLF.move(-direction * power);
        driveRB.move(direction * power);
        driveRF.move(direction * power);

        /*if(power > cap){power = cap;} //cap motor speed
        if(power < -cap){power = -cap;}*/

        delay(10);
  	}
};
//____________________________________________________________________________//
/////////////////////////////////STRAFE PID/////////////////////////////////////
//____________________________________________________________________________//
void dpidClass::strafePID(int direction, int target, int timeout, int cap) {
  //variables
    float kP = 0.7; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    float kI = 0; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    float kD = 1.1; //THESE ARE PLACEHOLDERS FOR UNTESTED VALUES
    int error = 0;
    int diffError = 0;
    int errorLast = 0;
    int sumError = 0;
    int power;
    int cp = 0;
    float p;
    float d;
    float i = 0; //integral
  	int startTime = millis();

    driveLB.tare_position(); //reset motor value

  	while((millis() - startTime) < timeout){ //while the timeout has not expired
  			error = target - driveLB.get_position(); //find error by subracting target from current pos
  			sumError += error;
  			diffError = error - errorLast;
        errorLast = error; //store last error value
        p = kP * error; //proportional
        d = kD * diffError; //derivative

        power = p+i+d;

        driveLB.move(-direction * power); //direction as 1 will make it move forwards, -1 backwards
        driveLF.move(direction * power);
        driveRB.move(direction * power);
        driveRF.move(-direction * power);

        if(power > cap){power = cap;} //cap motor speed
        if(power < -cap){power = -cap;}

        delay(10);
  	}
}
    //examples on main.cpp
