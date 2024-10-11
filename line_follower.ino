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
  
  leftMotor->setSpeed(30);
  rightMotor->setSpeed(30);

  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);

  leftIR = analogRead(1);
  wideLeftIR = analogRead(3);
  rightIR = analogRead(2);
  wideRightIR = analogRead(4);
  
  Serial.print(wideLeftIR);
  Serial.print(",");
  Serial.print(leftIR);
  Serial.print(",");
  Serial.print(rightIR);
  Serial.print(",");
  Serial.print(wideRightIR);
  Serial.println(",");

  if (leftIR < 680) { // If true, left sensor no longer sees black tape
    rightMotor->setSpeed(22); // make the right motor slower to make a slight right
    if (wideLeftIR < 680) { // if both left and wide left are off black tape
      leftMotor->setSpeed(35); // make left side faster for a sharper right turn 
    }
  }

  if (rightIR < 600) { // If true, right sensor no longer sees black tape
    leftMotor->setSpeed(22); // make the left motor slower to make a slight left
    if (wideRightIR < 680) { // if both right and wide right are off black tape
      rightMotor->setSpeed(35); // make  right side faster for a sharper left turn
    }
  }

}
