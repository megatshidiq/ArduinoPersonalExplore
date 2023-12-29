#include <Wire.h>
#include <L3G.h>
#include <Servo.h>

L3G gyro;
Servo servoMotor;

const int numReadings = 10;
int gyroReadings[numReadings];
int gyroIndex = 0;

unsigned long lastMoveTime = 0;
const unsigned long decayInterval = 1000;  // Adjust the decay interval as needed

void setup() {
  Serial.begin(9600);

  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  Serial.println("Gyro initialized successfully");

  servoMotor.attach(2);  // Attach the servo to pin 9
}

void loop() {
  gyro.read();  // Read gyro data

  // Apply a simple moving average filter to gyro readings
  int gyroSum = 0;
  for (int i = 0; i < numReadings; ++i) {
    gyroSum += gyro.g.y;
  }
  int filteredGyro = gyroSum / numReadings;

  // Map the filtered gyro readings to servo angles (adjust as needed)
  int servoAngle = map(filteredGyro, -1000, 1000, 0, 180);
  servoAngle = constrain(servoAngle, 0, 180);

  // Control the servo
  servoMotor.write(servoAngle);

  // Print gyro and servo data
  Serial.print("Gyro Y: ");
  Serial.print(filteredGyro);
  Serial.print("   Servo Angle: ");
  Serial.println(servoAngle);

  // Decay the servo angle if there is no gyro movement
  unsigned long currentTime = millis();
  if (abs(filteredGyro) > 20) {  // Adjust the threshold as needed
    lastMoveTime = currentTime;
  } else if (currentTime - lastMoveTime > decayInterval) {
    // Apply a gradual decay to the servo angle
    if (servoAngle > 90) {
      servoAngle--;
    } else if (servoAngle < 90) {
      servoAngle++;
    }
    servoMotor.write(servoAngle);
  }

  delay(20);  // Adjust the delay as needed for stability
}
