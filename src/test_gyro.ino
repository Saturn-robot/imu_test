#include <ITG3200.h>

float x, y, z;
ITG3200 gyro;

void setup()
{
  Serial.begin(9600)
  gyro.begin();
  gyro.init(ITG3200_ADDR_AD0_LOW);
  //Serial.print("zeroCalibrating...");
  gyro.zeroCalibrate(2500, 2);
  delay(1000);
  //Serial.println("done.");
}

void loop()
{
  gyro.readGyro(&x, &y, &z);
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println();
}
