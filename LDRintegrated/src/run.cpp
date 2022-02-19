#include "main.h" //include the main.h file to access all of the namespaces and includes
#include "run.h" //include the run.h file to access all of the functions and the main.h file
void Run() { //the main run loop

  int time;
  time = 0;
  FILE *fp;

if (AUTOState == 1){
  fp = fopen("/usd/1010H-SKILLS.txt", "r"); //roll-out
}
else if (AUTOState == 2){
  fp = fopen("/usd/1010H-RIGHT.txt", "r"); //roll-in
}
else if (AUTOState == 3){
  fp = fopen("/usd/1010H-LEFT.txt", "r"); //lift
}

  static float m1, m2, m3, m4, m5, m6, m7, m8, m9; //these are placeholders for motor velocities

    while (true) { //main while loop
      time+=10;
      delay(10);
/*
      if (time<=16000 && time>=15000){
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int difLIDAR = (rightLIDAR-leftLIDAR);
        	if(difLIDAR>20){
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

        	else if(difLIDAR<20){
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

      else if (time<=17000 && time>=16000){
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int wallDif = leftLIDAR-1310;
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
///TURNED AND ALIGNED NOW.
      else if (time<=33000 && time>=32000){
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int wallDif = leftLIDAR-1010;
        if ((wallDif)>10){
          int error, sumError, diffError, errorLast, output;
          float kP = 1.0;
          float kI = 0;
          float kD = 1.0;
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
          float kD = 1.0;
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

      else if (time<=36000 && time>=33000){
        int rightLIDAR = (backR.get());
        int leftLIDAR = (backL.get());
        int difLIDAR = (rightLIDAR-leftLIDAR);
        	if(difLIDAR>10){
        		int error, sumError, diffError, errorLast, output;

        		float kP = 0.55;
        		float kI = 0;
        		float kD = 0.3;

        			error = difLIDAR; //error value equals arm target minus the arm's current position
        			sumError += error; //sum error is defined as the error plus the sum of the error
        			diffError = error - errorLast; //difference in error is equal to error minus the last error, which is also defined as error
        			driveRB.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveRF.move(-0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
              driveLB.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD))); //arm will move according to kp, ki, and kd values
        			driveLF.move(0.5*(-(error * kP) + (sumError * kI) + (diffError * kD)));
              errorLast = error; //error last is defined as error
        	}

        	else if(difLIDAR<10){
        		int error, sumError, diffError, errorLast, output;

            float kP = 0.55;
        		float kI = 0;
        		float kD = 0.3;

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

//////TURNED AND ALIGNED NOW

      else {*/
        //reading from the array
        fscanf(fp, "%f %f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &m9); //read a stream and format the file
        //drive
        driveLB.move(m2); //plays values from listed above recorded values
        driveRB.move(m1);
        driveLF.move(m4);
        driveRF.move(m3);
        //roller intakes
        ////////////////////////////////
        lClaw.move_velocity(m6);
        pistonStateP = (m5); 
        ////////////////////////////////
        //flywheel and roller
        roller.move_velocity(m7);
        clawTargetR = (m8); //FORMERLY: futureUse4.move_velocity(m8);
        pistonState = m9;
      //}
  }
}
