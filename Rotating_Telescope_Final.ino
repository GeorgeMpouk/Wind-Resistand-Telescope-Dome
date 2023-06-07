// Rotating Telescope code by George Boukouvalas and Rosa Hoogenboom
// Created for Robotics Final project
// Leiden, 2023


// Include the Arduino Stepper.h library:
#include <AccelStepper.h>
//Initialisation phase
float North = 0;
int South = 0;
int East = 0;
int West = 0;
volatile byte revolutions;

float rpmilli;
float windSpeed;

unsigned long timeold = 0;
// Motor pin definitions:
#define motorPin1 8   // IN1 on the ULN2003 driver
#define motorPin2 9   // IN2 on the ULN2003 driver
#define motorPin3 10  // IN3 on the ULN2003 driver
#define motorPin4 11  // IN4 on the ULN2003 driver

// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper library with 28BYJ-48 stepper motor:
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);


// Define number of steps per one full rotation for big gear, which is two rotations of the motor:
const int stepsPerRevolution = 2 * 4096;


//setup function
void setup() {
  Serial.begin(9600);
  // Set the maximum steps per second:
  stepper.setMaxSpeed(1000);
  stepper.setCurrentPosition(0);                               //Start the telescope dome facing North
  attachInterrupt(digitalPinToInterrupt(2), rpm_fun, RISING);  // wind speed measurement
  revolutions = 0;
  rpmilli = 0;
  timeold = 0;
}
// main loop
void loop() {
  while (revolutions >= 1) { // make sure wind speed is enough
    //Update RPM every 20 counts, increase this for better RPM resolution,
    //decrease for faster update

    // calculate the revolutions per milli(second)
    rpmilli = ((float)revolutions) / (millis() - timeold);
    timeold = millis();
    revolutions = 0;
    //WHEELCIRC = 2 * PI * radius (in meters)
    // speed = rpmilli * WHEELCIRC * “milliseconds per hour” / “meters per kilometer”

    // simplify the equation to reduce the number of floating point operations
    // speed = rpmilli * WHEELCIRC * 3600000 / 1000
    // speed = rpmilli * WHEELCIRC * 3600

    windSpeed = rpmilli * 2.074 * 3600;
    // test print
    Serial.print(" Speed:");
    Serial.print(windSpeed, DEC);
    Serial.println(" kph");



    North = digitalRead(7);  // magnetic sensor read out from digital pin 7
    South = digitalRead(6);  // magnetic sensor read out from digital pin 6
    East = digitalRead(5);   // magnetic sensor read out from digital pin 5
    West = digitalRead(4);   // magnetic sensor read out from digital pin 4
      Serial.print("North:");

    Serial.println(North);

//    int windlist[4] = { North, South, East, West };  //change to different variable depending on pin readout
// int maxWind = windlist[0];
// int maxWindDirection = 5;
// for (int i = 0; i < 4; i++) {  //find which direction the maximum wind speed is coming from
//   if (windlist[i] > maxWind) {
//     maxWind = windlist[i];
//     maxWindDirection = i;
//   }
// }

    
      if (North ==0) {  //if the maximum speed is coming from the North
        //rotate to  South
        while (stepper.currentPosition() != stepsPerRevolution / 2) {  //move south
          stepper.moveTo(stepsPerRevolution / 2);
          stepper.setSpeed(500);
          stepper.runSpeedToPosition();
        }
      }

      else if (South ==0) {  //if the maximum speed is coming from the South
        //rotate to  North
        if (stepper.currentPosition() == 3 * stepsPerRevolution / 4) {  // move north from west
          while (stepper.currentPosition() != stepsPerRevolution) {     //move north
            stepper.moveTo(stepsPerRevolution);
            stepper.setSpeed(500);
            stepper.runSpeedToPosition();
          }
          stepper.setCurrentPosition(0);  //reset to the correct position on the wheel
        } else {
          while (stepper.currentPosition() != 0) {
            stepper.moveTo(0);
            stepper.setSpeed(500);
            stepper.runSpeedToPosition();
          }
        }
      }

      else if (East ==0) {  //if the maximum speed is coming from the East
        //rotate to  West
        if (stepper.currentPosition() == 0) {                             // move west from north
          while (stepper.currentPosition() != -stepsPerRevolution / 4) {  //move west anti-clockwise
            stepper.moveTo(-stepsPerRevolution / 4);
            stepper.setSpeed(500);
            stepper.runSpeedToPosition();
          }
          stepper.setCurrentPosition(3 * stepsPerRevolution / 4);  //reset to the correct position on the wheel
        } else {
          while (stepper.currentPosition() != 3 * stepsPerRevolution / 4) {  //move west clockwise
            stepper.moveTo(3 * stepsPerRevolution / 4);
            stepper.setSpeed(500);
            stepper.runSpeedToPosition();
          }
        }
      }

      else if (West ==0) {  //if the maximum speed is coming from the West
        //rotate to  East
        while (stepper.currentPosition() != stepsPerRevolution / 4) {  //move east
          stepper.moveTo(stepsPerRevolution / 4);
          stepper.setSpeed(500);
          stepper.runSpeedToPosition();
        }
      }
    
  }
}
void rpm_fun() {
  revolutions++;
}