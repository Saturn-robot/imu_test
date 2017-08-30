#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Imu, MagneticField
from geometry_msgs.msg import *
from math import radians

class Gyro:
    def __init__(self, frame_id = 'base_link'):
        self.frame_id = frame_id
        rospy.init_node('gyro_publisher', log_level=rospy.INFO)
        # Create imu message and magnetic message
        self.imu_msg = Imu()
        self.mag_msg = MagneticField()

        # Initialize imu message
        self.imu_msg.header.frame_id = self.frame_id
        self.imu_msg.orientation_covariance = [sys.float_info.max, 0, 0, 0, sys.float_info.max, 0, 0, 0, 0.05]
        self.imu_msg.angular_velocity_covariance = [sys.float_info.max, 0, 0, 0, sys.float_info.max, 0, 0, 0, 0.05]
        self.imu_msg.linear_acceleration_covariance = [0, 0, 0, 0, 0, 0, 0, 0, 0]

        # Initialize magnetic message
        self.mag_msg.header.frame_id = self.frame_id

        # Create publishers: imu_pub & mag_pub
        self.imu_pub = rospy.Publisher('imu/data_raw', Imu, queue_size=10)
        self.mag_pub = rospy.Publisher('imu/mag', MagneticField, queue_size=10)
        # Create subscribers to acquire sensors' data
        rospy.Subscriber('gyro_data', Vector3, self.gyro_callback)
        rospy.Subscriber('accel_data', Vector3, self.accel_callback)
        rospy.Subscriber('mag_data', Vector3, self.mag_callback)

    def gyro_callback(self, gyro_data):
        self.imu_msg.angular_velocity.x = radians(gyro_data.x)
        self.imu_msg.angular_velocity.y = radians(gyro_data.y)
        self.imu_msg.angular_velocity.z = radians(gyro_data.z)

    def accel_callback(self, accel_data):
        self.imu_msg.linear_acceleration.x = accel_data.x
        self.imu_msg.linear_acceleration.y = accel_data.y
        self.imu_msg.linear_acceleration.z = accel_data.z

    def mag_callback(self, mag_data):
        self.mag_msg.magnetic_field.x = mag_data.x
        self.mag_msg.magnetic_field.y = mag_data.y
        self.mag_msg.magnetic_field.z = mag_data.z

    def publish_imu(self):
        rate = rospy.Rate(10)
        while not rospy.is_shutdown():
            # Publish two messages
            self.imu_msg.header.stamp = rospy.Time.now()
            self.imu_msg.header.stamp = rospy.Time.now()
            self.imu_pub.publish(self.imu_msg)
            self.mag_pub.publish(self.mag_msg)
            rate.sleep()

if __name__ == "__main__":
    try:
        gyro_pub = Gyro()
        gyro_pub.publish_imu()
    except rospy.ROSInterruptException as e:
        rospy.loginfo(e)
        rospy.loginfo("Gyro publisher is being closed...")
