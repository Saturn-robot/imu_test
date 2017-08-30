#include <ITG3200.h>

float x, y, z;
unsigned long time;
unsigned long dt;
ITG3200 gyro;
float roll, pitch, yaw;
void setup()
{
  Serial.begin(9600);
  gyro.begin();
  gyro.init(ITG3200_ADDR_AD0_LOW);
  //Serial.print("zeroCalibrating...");
  gyro.zeroCalibrate(2500, 2);
  gyro.setScaleFactor(1.0, 1.0, 0.1, false);
  delay(1000);
  //Serial.println("done.");
}

void loop()
{
  time = millis();

  gyro.readGyro(&x, &y, &z);

  dt = millis() - time;
  
  roll += x * dt * 0.001;
  pitch += y * dt * 0.001;
  yaw += z * dt * 0.001;

  Serial.print(roll);
  Serial.print(",");
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(yaw);
  Serial.println();
}
