#include <Wire.h>
#include <Servo.h>
#include <MPU9250.h>

MPU9250 mpu;

Servo myservoX;  // Menghubungkan servo X ke pin digital 9
Servo myservoY;  // Menghubungkan servo Y ke pin digital 10

void setup() {
  Serial.begin(115200);

  if (!mpu.begin()) {
    Serial.println("Gagal menginisialisasi MPU-9250. Periksa koneksi!");
    while (1);
  }

  myservoX.attach(9);
  myservoY.attach(10);
}

void loop() {
  // Membaca nilai sensor MPU-9250
  mpu.readSensor();

  // Menghitung sudut berdasarkan nilai akselerometer
  float roll = atan2(mpu.getAccelY_mss(), mpu.getAccelZ_mss()) * 180.0 / PI;
  float pitch = atan(-mpu.getAccelX_mss() / sqrt(pow(mpu.getAccelY_mss(), 2) + pow(mpu.getAccelZ_mss(), 2))) * 180.0 / PI;

  // Mengontrol servo berdasarkan sudut roll dan pitch
  int servoXPos = map(roll, -90, 90, 0, 180);
  int servoYPos = map(pitch, -90, 90, 0, 180);

  myservoX.write(servoXPos);
  myservoY.write(servoYPos);

  // Tampilkan nilai sudut pada Serial Monitor
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("   Pitch: ");
  Serial.println(pitch);

  delay(20);  // Tunggu sejenak
}
