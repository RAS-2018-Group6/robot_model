#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Pose.h>




// Should subscribe to dead reckoning node


void odomCallback(const geometry_msgs::Pose::ConstPtr& msg){

    x = msg->position.x;
    y = msg->position.y;
    phi = msg->orientation.z;

}

int main(int argc, char** argv){

  ros::init(argc, argv, "position_broadcaster");

  ros::NodeHandle node;
  ros::Rate loop_rate(10);

  static tf::TransformBroadcaster br;
  tf::Transform transform;

  sub_odom = n.subscribe<geometry_msgs::Pose>("/odom",10,odomCallback);



  float x = 0;
  float y = 0;

  while(ros::ok()){
      ROS_INFO("I heard : x:[%f]  y:[%f]", x,y);

      transform.setOrigin(tf::Vector3( x, y, 0.0));
      tf::Quaternion q;
      q.setRPY(0, 0, 3);
      transform.setRotation(q);

      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));

      // change position just to show in rviz. Should be changed acording to /odom topic
      x = x+0.2;
      y = y+0.2;
      loop_rate.sleep();

  }

  return 0;
};
