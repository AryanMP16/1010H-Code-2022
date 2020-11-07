#include "main.h" //include the main.h file to access all of the namespaces and includes
#include "run.h" //include the run.h file to access all of the functions and the main.h file

void Run() { //the main run loop
  //
  FILE *fp; //create a file called fp

  fp = fopen("/usd/example.txt", "r"); //open an fp file called "/usd/example.txt", and read from it
  static float m1, m2, m3, m4/*, m5, m6, m7, m8*/; //these are placeholders for motor velocities

  while (true) { //main while loop

//closes file after all the motors have stopped (AFTER AUTO)
      if (feof(fp)) { //if the end of the recording file is reached, do not move the motors anymroe
        /////////stop all of the motors
          //drive motors
            driveRB.move_velocity(0); //do not move the right back drive motor as the end of the file has been reached
            driveRF.move_velocity(0); //do not move the right front drive motor as the end of the file has been reached
            driveLB.move_velocity(0); //do not move the left back drive motor as the end of the file has been reached
            driveLF.move_velocity(0); //do not move the left back drive motor as the end of the file has been reached

        ///////close the file
            fclose(fp);
            delay(100); //do not move the right back drive motor as the end of the file has been reached
      }

//reading from the array
    fscanf(fp, "%f %f %f %f", &m1, &m2, &m3, &m4/*, &m5, &m6, &m7, &m8*/); //read a stream and format the file
/*IMPORTANT: WHEN ADDING MORE MOTORS, MAKE SURE TO ADD MORE %F'S AND M5-8*/

//moving motors using array values
//printf("%f\n", m1); //print the values of the right back motor to the serial terminal for testing purposes
//drive motors
  driveLB.move_velocity(m1); //read the motor velocities from the left back motor and play them back
  driveRB.move_velocity(m2); //read the motor velocities from the right back motor and play them back
  driveLF.move_velocity(m3); //read the motor velocities from the left front motor and play them back
  driveRF.move_velocity(m4); //read the motor velocities from the right front motor and play them back

  delay(20); //delay 10 milliseconds so as to balance the 10 millisecond delay in the record files
}
}
