#include <ITG3200.h>
#include <ros.h>
#include <geometry_msgs/Vector3.h>

float x, y, z;
ros::NodeHandle nh;
geometry_msgs::Vector3 gyro_data;
ros::Publisher gyro_pub("gyro_data", &gyro_data);
ITG3200 gyro;

void setup()
{
  gyro.begin();
  gyro.init(ITG3200_ADDR_AD0_LOW);
  //Serial.print("zeroCalibrating...");
  gyro.zeroCalibrate(2500, 2);
  delay(1000);
  //Serial.println("done.");
  nh.initNode();
  nh.advertise(gyro_pub);
  //imu_data.orientation_covariance = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  //imu_data.angular_velocity_covariance = {999, 0, 0, 0, 999, 0, 0, 0, 0.05};
  //imu_data.linear_acceleration_covariance = {0, 0, 0, 0, 0, 0, 0, 0, 0};
}

void loop()
{
  gyro.readGyro(&x, &y, &z);
  gyro_data.x = x;
  gyro_data.y = y;
  gyro_data.z = z;

  gyro_pub.publish(&gyro_data);
  nh.spinOnce();
  delay(100);
}
