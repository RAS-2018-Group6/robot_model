#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Pose.h>
#include <math.h>




// Should subscribe to dead reckoning node

int main(int argc, char** argv){

  ros::init(argc, argv, "position_broadcaster");

  ros::NodeHandle node;
  ros::Rate loop_rate(100);

  static tf::TransformBroadcaster br;
  tf::Transform transform;

  float x = 0;
  float y = 0;
  float x_arg = 0;
  float y_arg = 0;

  while(ros::ok()){
      ROS_INFO("I heard : x:[%f]  y:[%f]", x,y);

      transform.setOrigin(tf::Vector3( x, y, 0.0));
      tf::Quaternion q;
      q.setRPY(0, 0, 0);
      transform.setRotation(q);

      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));

      // change position just to show in rviz. Should be changed acording to /odom topic
      x_arg = x_arg+0.01;
      y_arg = y_arg+0.01;
      x = cos(x_arg);
      y = sin(y_arg);
      loop_rate.sleep();

  }

  return 0;
};
