#include "main.h" //include the main.h file to access all of the namespaces and includes
#include "run.h" //include the run.h file to access all of the functions and the main.h file

void Run() { //the main run loop

  int time;
  time = 0;

  FILE *fp = fopen("/usd/1010H-SKLZ.txt", "r");

  static float m1, m2, m3, m4, m5, m6, m7, m8; //these are placeholders for motor velocities

    while (true) { //main while loop
      time+=10;
      delay(10);

        //reading from the array
        fscanf(fp, "%f %f %f %f %f %f %f %f", &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8); //read a stream and format the file
        //drive
        driveLB.move(m2); //plays values from listed above recorded values
        driveRB.move(m1);
        driveLF.move(m4);
        driveRF.move(m3);
        //roller intakes
        ////////////////////////////////
        lClaw.move_velocity(m6);
        rClaw.move_velocity(m5);
        ////////////////////////////////
        //flywheel and roller
        roller.move_velocity(m7);
        clawTargetR = (m8); //FORMERLY: futureUse4.move_velocity(m8);
  }
}