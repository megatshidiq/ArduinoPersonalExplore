#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define motors
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// Define IR sensor pins
const int sensorPin1 = A0;
const int sensorPin2 = A1;
const int sensorPin3 = A2;
const int sensorPin4 = A3;
const int sensorPin5 = A4;

// Threshold values for each sensor
const int threshold = 500;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - Line Follower test!");

  AFMS.begin();  // create with the default frequency 1.6KHz

  // Set the speed for the motors
  leftMotor->setSpeed(150);
  rightMotor->setSpeed(150);
}

void loop() {
  int sensorValues[5];

  // Read sensor values
  sensorValues[0] = analogRead(sensorPin1);
  sensorValues[1] = analogRead(sensorPin2);
  sensorValues[2] = analogRead(sensorPin3);
  sensorValues[3] = analogRead(sensorPin4);
  sensorValues[4] = analogRead(sensorPin5);

  // Adjust motor speeds based on sensor values
  int leftSpeed = 150;
  int rightSpeed = 150;

  // Adjust the speed based on sensor inputs
  leftSpeed += sensorValues[0] > threshold ? -30 : 0;
  leftSpeed += sensorValues[1] > threshold ? -15 : 0;
  rightSpeed += sensorValues[3] > threshold ? -15 : 0;
  rightSpeed += sensorValues[4] > threshold ? -30 : 0;

  // Set motor speeds
  leftMotor->setSpeed(leftSpeed);
  rightMotor->setSpeed(rightSpeed);

  // Run motors
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);

  // Print sensor values for debugging
  Serial.print("Sensor Values: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();

  delay(10); // adjust as needed
}
