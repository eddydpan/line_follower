#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor * leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor * rightMotor = AFMS.getMotor(4);

int leftIR;
int rightIR;

int leftIRThresh = 795; // Initialize threshold for left IR
int rightIRThresh = 805; // Initialize threshold for right IR

int leftMotorVel;
int rightMotorVel;

void setup() {
  long baudRate = 9600;
  AFMS.begin();
  Serial.begin(baudRate);
 
}

void loop() {
  // Run the motor backwards because of our mechanical orientation of the DC motors
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
  // Get the IR sensors' analog voltage
  rightIR = analogRead(3);
  leftIR = analogRead(2);

  if(rightIR > rightIRThresh) { // Right IR sensor sees the tape
    // Turn right
    rightMotorVel = 0;
    leftMotorVel = 40;
  }

  else if (leftIR > leftIRThresh) { // Left IR sensor sees the tape
    // Turn left
    leftMotorVel = 0;
    rightMotorVel = 40;
  }

  else { // Neither of the sensors see the tape
    // Go straight
    rightMotorVel = 20;
    leftMotorVel = 20;
  }

  // Update motor speeds based on IR sensor values
  leftMotor->setSpeed(leftMotorVel);
  rightMotor->setSpeed(rightMotorVel);

  // Print out all of our outputs to receive on Python file in csv format
  Serial.print(leftIR);
  Serial.print(",");
  Serial.print(rightIR);
  Serial.print(",");
  Serial.print(leftMotorVel);
  Serial.print(",");
  Serial.println(rightMotorVel);
}
