#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor * leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor * rightMotor = AFMS.getMotor(4);

int wideLeftIR = 0;
int wideRightIR = 0;

int wideLeftThresh = 690;//550 //745
int wideRightThresh = 780;//765 //835

int leftMotorVel;
int rightMotorVel;
void setup() {
  // put your setup code here, to run once:
  long baudRate = 9600;
  AFMS.begin();
  Serial.begin(baudRate);
  

}

void loop() {
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);

//  leftIR = analogRead(1);
  wideRightIR = analogRead(3);
//  rightIR = analogRead(2);
  wideLeftIR = analogRead(2);
  /*
  Serial.print(wideLeftIR);
  Serial.print(",");
  Serial.print(wideRightIR);
  Serial.println("");
  */
  leftMotor->setSpeed(leftMotorVel);
  rightMotor->setSpeed(rightMotorVel);

  

  if(wideRightIR > wideRightThresh) {
    rightMotorVel = 0;
    leftMotorVel = 40;
  }

  else if (wideLeftIR > wideLeftThresh) {
    leftMotorVel = 0;
    rightMotorVel = 40;
  }

  else {
    rightMotorVel = 20;
    leftMotorVel = 20;
  }
  leftMotor->setSpeed(leftMotorVel);
  rightMotor->setSpeed(rightMotorVel);
  
//  Serial.print("Right_Motor_Vel:");
//  Serial.print("Left_Sensor:");
  Serial.print(wideLeftIR);
  Serial.print(",");
//  Serial.print("Right_Sensor:");
  Serial.print(wideRightIR);
  
  Serial.print(",");
//  Serial.print("Left_Motor_Vel:");
  Serial.print(leftMotorVel);
  Serial.print(",");
  Serial.println(rightMotorVel);
  /*
  if (leftIR < leftThresh) { // If true, left sensor no longer sees black tape = TURN RIGHT

    rightMotor->setSpeed(22); // make the right motor slower to make a slight right
    Serial.println("");
    if (wideRightIR > wideRightThresh) { // if both left is off tape and wide right is on tape
      leftMotor->setSpeed(35); // make left side faster for a sharper right turn 
      if (rightIR < rightThresh) {
        rightMotor->run(BACKWARD);
        rightMotor->setSpeed(25); // make left side faster for a sharper right turn 
        leftMotor->setSpeed(25); // make left side faster for a sharper right turn 

      }
    }
    
  }

  else if (rightIR < rightThresh) { // If true, right sensor no longer sees black tape = TURN LEFT
    leftMotor->setSpeed(22); // make the left motor slower to make a slight left
    if (wideRightIR < wideRightThresh) { // if both right and wide right are off black tape
      rightMotor->setSpeed(35); // make  right side faster for a sharper left turn
      if (leftIR < leftThresh) {
        leftMotor->run(BACKWARD);
        leftMotor->setSpeed(25); // make left side faster for a sharper right turn 
        rightMotor->setSpeed(25); // make left side faster for a sharper right turn 

      }
    }
  }
  */
}
