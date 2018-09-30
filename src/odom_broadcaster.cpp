#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Pose.h>



class OdomBroadcaster
{
public:
	ros::NodeHandle node;
	ros::Subscriber sub_odom;
	tf::TransformBroadcaster br;
	tf::Transform transform;


	OdomBroadcaster(){
	  ros::init(argc, argv, "position_broadcaster");
	  ros::Rate loop_rate(10);

	  sub_odom = n.subscribe<geometry_msgs::Pose>("/odom",10,&OdomBroadcaster::odomCallback,this);

}



	void odomCallback(const geometry_msgs::Pose::ConstPtr& msg){
		ROS_INFO("I heard : x:[%f],y:[%f],phi:[%f]", x,y,phi);
		x = msg->position.x;
		y = msg->position.y;
		phi = msg->orientation.z;

		transform.setOrigin(tf::Vector3( x, y, 0.0));
	        tf::Quaternion q;
	        q.setRPY(0, 0, phi);
	        transform.setRotation(q);

	        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));

	}


private:
	float x;
	float y;
	float phi;


	int main(int argc, char** argv){

		ros::Rate loop_rate(20);

	  while(ros::ok()){
	      
		ros::spinOnce();
	        loop_rate.sleep();

	  }

	  return 0;
	}

}
