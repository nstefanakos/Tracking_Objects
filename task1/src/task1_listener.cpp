#include "ros/ros.h"
#include "std_msgs/String.h"

void callback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO(" You gave me: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");

	ros::NodeHandle n;

	ros::Subscriber Sub1 = n.subscribe("chatter", 1000, callback);

	ros::spin();

	return 0;
}