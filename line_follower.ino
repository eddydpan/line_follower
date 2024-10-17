#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor * leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor * rightMotor = AFMS.getMotor(4);

int blinkTime = millis();
int t;

int wideLeftIR = 0;
int leftIR = 0;
int rightIR = 0;
int wideRightIR = 0;

//int wideLeftThresh = 955;
//int wideRightThresh = 835;

int wideLeftThresh = 970;
int wideRightThresh = 875;

//int leftThresh = 740;
//int rightThresh = 730;


void setup() {
  // put your setup code here, to run once:
  long baudRate = 9600;
  AFMS.begin();
  Serial.begin(baudRate);
  

}

void loop() {

  

//  t = millis()
//  currentTime = (t - blinkTime)
//  Serial.println(current_time);
//  timeSinceBlink = 
  
  

  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);

  leftIR = analogRead(1);
  wideRightIR = analogRead(3);
  rightIR = analogRead(2);
  wideLeftIR = analogRead(5);
  
  Serial.print(wideLeftIR);
  Serial.print(",");
//  Serial.print(leftIR);
//  Serial.print(",");
//  Serial.print(rightIR);
//  Serial.print(",");
  Serial.print(wideRightIR);
  Serial.println("");

  if (wideLeftIR > wideLeftThresh) {
    leftMotor->setSpeed(10);
    Serial.println("LEFT SEES TAPE. GO RIGHT");
  }

  else if(wideRightIR > wideRightThresh) {
    rightMotor->setSpeed(10); 
    Serial.println("RIGHT SEES TAPE. GO LEFT");


  }
  else {
    leftMotor->setSpeed(30);
    rightMotor->setSpeed(30);
  }
  
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
