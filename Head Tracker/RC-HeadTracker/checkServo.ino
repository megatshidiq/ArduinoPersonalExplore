/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low gyro data registers.
They can be converted to units of dps (degrees per second) using the
conversion factors specified in the datasheet for your particular
device and full scale setting (gain).

Example: An L3GD20H gives a gyro X axis reading of 345 with its
default full scale setting of +/- 245 dps. The So specification
in the L3GD20H datasheet (page 10) states a conversion factor of 8.75
mdps/LSB (least significant bit) at this FS setting, so the raw
reading of 345 corresponds to 345 * 8.75 = 3020 mdps = 3.02 dps.
*/

#include <Wire.h>
#include <L3G.h>
#include <Servo.h>
//I2C pin arudino uno is A4(SDA) and A5(SCL)
// myservo is the servo object
Servo myservo;
// gyro is the gyro object
L3G gyro;

void setup() {
  Serial.begin(9600);
  // Wire.begin();

  // if (!gyro.init())
  // {
  //   Serial.println("Failed to autodetect gyro type!");
  //   while (1);
  // }

  // gyro.enableDefault();

  myservo.attach(2);
  myservo.write(90);
delay(5000);
}

  void loop() {

  myservo.write(0); //set servo to mid-point
  delay(1000);
  myservo.write(90); //set servo to mid-point
  delay(1000);
  myservo.write(180); //set servo to mid-point
  delay(1000);
  myservo.write(0); //set servo to mid-point
  delay(1000);
  myservo.write(90); //set servo to mid-point
  delay(1000);
  myservo.write(180); //set servo to mid-point
  delay(1000);
  myservo.write(0); //set servo to mid-point
  delay(1000);
  myservo.write(90); //set servo to mid-point
  delay(1000);
  myservo.write(180); //set servo to mid-point
  delay(1000);
//   gyro.read();

//   Serial.print("G ");
//   Serial.print("X: ");

//     int ax = gyro.g.x;
//     int ay = gyro.g.y;
//   Serial.print(ax);
//   Serial.print(" Y: ");
//   Serial.print(ay);
//   Serial.print(" Z: ");
//   Serial.println((int)gyro.g.z);

//   int servoX = map(ax, 0, 1023, 0, 180) ;
//   int servoY = map(ay, 0, 1023, 0, 180) ;
 
//     Serial.print(" Servo X: ");
//     Serial.print(servoX);
//     myservo.write(servoX);
//     Serial.print(" Servo Y: ");
//     Serial.println(servoY);

//   delay(100);
 }