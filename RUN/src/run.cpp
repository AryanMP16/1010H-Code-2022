#include "main.h" //include the main.h file to access all of the namespaces and includes
#include "run.h" //include the run.h file to access all of the functions and the main.h file

void Run() { //the main run loop
  FILE *fp = fopen("/usd/1010H.txt", "r"); //open an fp file called "/usd/1010H.txt", and read from it
  static float m1, m2, m3, m4, m7, m8; //these are placeholders for motor velocities
  static int p5, p6;
  while (true) { //main while loop
//closes file after all the motors have stopped (AFTER AUTO)
      if (feof(fp)) { //if the end of the recording file is reached, do not move the motors anymroe
        /////////stop all of the motors
          //drive motors
          int a = driveRB.get_position();
          int b = driveRF.get_position();
          int c = driveLB.get_position();
          int d = driveLF.get_position();
          int e = roller.get_position();
          int f = lClaw.get_position();
          int g = rClaw.get_position();
          int h = futureUse4.get_position();
            driveRB.move_absolute(a,0); //do not move the right back drive motor as the end of the file has been reached
            driveRF.move_absolute(b,0); //do not move the right front drive motor as the end of the file has been reached
            driveLB.move_absolute(c,0); //do not move the left back drive motor as the end of the file has been reached
            driveLF.move_absolute(d,0); //do not move the left back drive motor as the end of the file has been reached
            //roller motor
            roller.move_absolute(e,0); //do not move the angler motor as the end of the file has been reached
            //intakes
            lClaw.move_absolute(f,0); //do not move the left intake motor as the end of the file has been reached
            rClaw.move_absolute(g,0); //do not move the right intake motor as the end of the file has been reached
          //arm motor
            futureUse4.move_absolute(h,0); //do not move the arm motor as the end of the file has been reached
        ///////close the file
            fclose(fp); //do not move the right back drive motor as the end of the file has been reached
            delay(100); //do not move the right back drive motor as the end of the file has been reached
      }
int clawTarget;
int clawTargetL;
int error, sumError, diffError, errorLast, output;
int BUILT_DIFFERENT;
float kP = 0.9;
float kI = 0;
float kD = 0;
int errorL, sumErrorL, diffErrorL, errorLastL;
float kPL = 0.9;
float kIL = 0.0;
float kDL = 0.0;
//reading from the array
    fscanf(fp, "%f %f %f %f %i %i %f %f", &m1, &m2, &m3, &m4, &p5, &p6, &m7, &m8); //read a stream and format the file
    driveLB.move_velocity(m2);
    driveRB.move_velocity(m1);
    driveLF.move_velocity(m4);
    driveRF.move_velocity(m3);
    ////////////////////////////////
        error = p6 - rClaw.get_position(); //error value equals arm target minus the arm's current position
        sumError += error; //sum error is defined as the error plus the sum of the error
        diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
        rClaw.move((error * kP) + (sumError * kI) + (diffError * kD)); //arm will move according to kp, ki, and kd values
        errorLast = error; //error last is defined as error
        //
        errorL = p5 - lClaw.get_position(); //error value equals arm target minus the arm's current position
        sumErrorL += errorL; //sum error is defined as the error plus the sum of the error
        diffErrorL = errorL - errorLastL; //difference in error is equal to error minus the last error, which is also defined as error
        lClaw.move((errorL * kPL) + (sumErrorL * kIL) + (diffErrorL * kDL));
        errorLastL = errorL; //error last is defined as error
    ////////////////////////////////
    roller.move_velocity(m7);
    futureUse4.move_velocity(m8);
  delay(10); //delay 10 milliseconds so as to balance the 10 millisecond delay in the record files
}
}
