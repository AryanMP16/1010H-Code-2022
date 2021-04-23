#include "main.h" //include the main.h file to access all of the namespaces and includes
#include "run.h" //include the run.h file to access all of the functions and the main.h file

void Run() { //the main run loop

  int time;
  time = 0;

  FILE *fp = fopen("/usd/1010H.txt", "r");

  static float m1, m2, m3, m4, m5, m6, m7, m8; //these are placeholders for motor velocities

    while (true) { //main while loop
      time+=10;
      delay(10);

      if (time<=17500 && time>=16000){
        roller.move_velocity(0);
        futureUse4.move_velocity(0);
        rClaw.move_velocity(0);
        lClaw.move_velocity(0);
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int difLIDAR = (rightLIDAR-leftLIDAR);
        	if(difLIDAR>1){
        		int error, sumError, diffError, errorLast, output;

        		float kP = 2;
        		float kI = 0;
        		float kD = 0.7;

        			error = difLIDAR; //error value equals arm target minus the arm's current position
        			sumError += error; //sum error is defined as the error plus the sum of the error
        			diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
        			driveRB.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveRF.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
              driveLB.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveLF.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              errorLast = error; //error last is defined as error
        	}

        	else if(difLIDAR<1){
        		int error, sumError, diffError, errorLast, output;

            float kP = 2;
        		float kI = 0;
        		float kD = 0.7;

        			error = difLIDAR; //error value equals arm target minus the arm's current position
        			sumError += error; //sum error is defined as the error plus the sum of the error
        			diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
        			driveLB.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveLF.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
              driveRB.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              driveRF.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              errorLast = error; //error last is defined as error
        	}

        	else{}
      }
/*
      else if (time<=11000 && time>=9500){
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int wallDif = leftLIDAR-455;
        cout << wallDif << "\n";

        if ((wallDif)>10){
          int error, sumError, diffError, errorLast, output;

          float kP = 1.0;
          float kI = 0;
          float kD = 1.8;

            error = wallDif; //error value equals arm target minus the arm's current position
            sumError += error; //sum error is defined as the error plus the sum of the error
            diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
            driveLB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveLF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveRB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            driveRF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            errorLast = error; //error last is defined as error
        }
        else if (wallDif < 10){
          int error, sumError, diffError, errorLast, output;

          float kP = 1.0;
          float kI = 0;
          float kD = 1.8;

            error = wallDif; //error value equals arm target minus the arm's current position
            sumError += error; //sum error is defined as the error plus the sum of the error
            diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
            driveLB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveLF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveRB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            driveRF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            errorLast = error; //error last is defined as error
        }
      }

      else if (feof(fp)) { //if the end of the recording file is reached, do not move the motors anymroe
        /////////stop all of the motors
          driveRB.move_velocity(0); //do not move the right back drive motor as the end of the file has been reached
          driveRF.move_velocity(0); //do not move the right front drive motor as the end of the file has been reached
          driveLB.move_velocity(0); //do not move the left back drive motor as the end of the file has been reached
          driveLF.move_velocity(0); //do not move the left back drive motor as the end of the file has been reached
          //roller motor
          roller.move_velocity(0); //do not move the angler motor as the end of the file has been reached
          //intakes
          lClaw.move_velocity(0); //do not move the left intake motor as the end of the file has been reached
          rClaw.move_velocity(0); //do not move the right intake motor as the end of the file has been reached
          //arm motor
          futureUse4.move_velocity(0); //do not move the arm motor as the end of the file has been reached
        ///////close the file
          fclose(fp); //do not move the right back drive motor as the end of the file has been reached
          delay(100); //do not move the right back drive motor as the end of the file has been reached
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////
      else if (time<=29500 && time>=28500){
        roller.move_velocity(0);
        futureUse4.move_velocity(0);
        rClaw.move_velocity(0);
        lClaw.move_velocity(0);
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int difLIDAR = (rightLIDAR-leftLIDAR);
        	if(difLIDAR>1){
        		int error, sumError, diffError, errorLast, output;

        		float kP = 2;
        		float kI = 0;
        		float kD = 0.7;

        			error = difLIDAR; //error value equals arm target minus the arm's current position
        			sumError += error; //sum error is defined as the error plus the sum of the error
        			diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
        			driveRB.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveRF.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
              driveLB.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveLF.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              errorLast = error; //error last is defined as error
        	}

        	else if(difLIDAR<1){
        		int error, sumError, diffError, errorLast, output;

            float kP = 2;
        		float kI = 0;
        		float kD = 0.7;

        			error = difLIDAR; //error value equals arm target minus the arm's current position
        			sumError += error; //sum error is defined as the error plus the sum of the error
        			diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
        			driveLB.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveLF.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
              driveRB.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              driveRF.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              errorLast = error; //error last is defined as error
        	}

        	else{}
      }

      else if (time<=31000 && time>=29500){
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int wallDif = leftLIDAR-540;
        cout << wallDif << "\n";

        if ((wallDif)>10){
          int error, sumError, diffError, errorLast, output;

          float kP = 1.0;
          float kI = 0;
          float kD = 1.8;

            error = wallDif; //error value equals arm target minus the arm's current position
            sumError += error; //sum error is defined as the error plus the sum of the error
            diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
            driveLB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveLF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveRB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            driveRF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            errorLast = error; //error last is defined as error
        }
        else if (wallDif < 10){
          int error, sumError, diffError, errorLast, output;

          float kP = 1.0;
          float kI = 0;
          float kD = 1.8;

            error = wallDif; //error value equals arm target minus the arm's current position
            sumError += error; //sum error is defined as the error plus the sum of the error
            diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
            driveLB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveLF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
            driveRB.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            driveRF.move(0.5*((error * kP) + (sumError * kI) + (diffError * kD)));
            errorLast = error; //error last is defined as error
        }
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////
    
      /////////////////////////////////////////////////??////////////////////////////////////////////////////
*/
      else {
        //reading from the array
        fscanf(fp, "%f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m8, &m6, &m7); //read a stream and format the file
        //drive
        driveLB.move_velocity(m2); //plays values from listed above recorded values
        driveRB.move_velocity(m1);
        driveLF.move_velocity(m4);
        driveRF.move_velocity(m3);
        //roller intakes
        ////////////////////////////////
        lClaw.move_velocity(m8);
        rClaw.move_velocity(m5);
        ////////////////////////////////
        //flywheel and roller
        roller.move_velocity(m6);
        futureUse4.move_velocity(m7);
      }
  }
}
