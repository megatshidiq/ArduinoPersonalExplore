#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050_9Axis_MotionApps41.h>

MPU6050 mpu;

#define INTERRUPT_PIN 2 // use pin 2 on Arduino Pro for interrupt

volatile bool mpuInterrupt = false;

void dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {
  Wire.begin();
  Serial.begin(115200);

  mpu.initialize();

  pinMode(INTERRUPT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);

  Serial.println(F("Initializing DMP..."));
  uint8_t devStatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788);

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuInterrupt = false;
    Serial.println(F("DMP Initialization complete. Waiting for data..."));
  } else {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}

void loop() {
  if (!mpuInterrupt && fifoCount < packetSize) {
    return;
  }

  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
  } else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    // Get magnetometer data
    int16_t mx, my, mz;
    mpu.getMag(&mx, &my, &mz);

    // Calculate heading angle
    float heading = atan2(my, mx) * 180.0 / M_PI;
    if (heading < 0) {
      heading += 360.0;
    }

    // Now you can use heading along with yaw, pitch, and roll for head tracking

    Serial.print("Yaw, Pitch, Roll, Heading: ");
    Serial.print(ypr[0] * 180/M_PI);
    Serial.print(", ");
    Serial.print(ypr[1] * 180/M_PI);
    Serial.print(", ");
    Serial.print(ypr[2] * 180/M_PI);
    Serial.print(", ");
    Serial.println(heading);
  }
}
