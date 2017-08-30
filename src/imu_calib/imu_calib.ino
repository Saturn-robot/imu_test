#include <GY85.h>
#include <ros.h>
#include <geometry_msgs/Vector3.h>

float x, y, z;
ros::NodeHandle nh;
geometry_msgs::Vector3 accel_data;
geometry_msgs::Vector3 gyro_data;
geometry_msgs::Vector3 mag_data;
ros::Publisher gyro_pub("gyro_data", &gyro_data);
ros::Publisher accel_pub("accel_data", &accel_data);
ros::Publisher mag_pub("mag_data", &mag_data);
GY85 gy85(1234, 1235, 1236);

void setup()
{
  gy85.init();
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.advertise(gyro_pub);
  nh.advertise(accel_pub);
  nh.advertise(mag_pub);
  while (!nh.connected())
  {
    nh.spinOnce();
  }
  nh.loginfo("Imu publisher connected!");
  delay(1);
  //imu_data.orientation_covariance = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  //imu_data.angular_velocity_covariance = {999, 0, 0, 0, 999, 0, 0, 0, 0.05};
  //imu_data.linear_acceleration_covariance = {0, 0, 0, 0, 0, 0, 0, 0, 0};
}

void loop()
{
  float accels[3];
  float gyros[3];
  float mags[3];

  gy85.readAccel(accels);
  accel_data.x = accels[0];
  accel_data.y = accels[1];
  accel_data.z = accels[2];
  accel_pub.publish(&accel_data);

  gy85.readGyro(gyros);
  gyro_data.x = gyros[0];
  gyro_data.y = gyros[1];
  gyro_data.z = gyros[2];
  gyro_pub.publish(&gyro_data);

  gy85.readMag(mags);
  mag_data.x = mags[0];
  mag_data.y = mags[1];
  mag_data.z = mags[2];
  mag_pub.publish(&mag_data);

  nh.spinOnce();
  delay(100);
}
