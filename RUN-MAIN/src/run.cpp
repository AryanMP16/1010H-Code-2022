#include "main.h" //include the main.h file to access all of the namespaces and includes
#include "run.h" //include the run.h file to access all of the functions and the main.h file

void Run() { //the main run loop

  int time;
  time = 0;

  std::string readfile = "\"/usd/1010H.txt\"";
  char readfilechar[readfile.size() + 1];
  strcpy(readfilechar, readfile.c_str());

  FILE *fp = fopen("/usd/1010H.txt", "r");

  static float m1, m2, m3, m4, m5, m6, m7, m8; //these are placeholders for motor velocities

    while (true) { //main while loop
      time+=10;
      delay(10);

      if (time<=9900 && time>=5000){
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