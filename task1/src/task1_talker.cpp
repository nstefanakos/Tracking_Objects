#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/UInt32.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/Header.h"
#include <sstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "talker");

	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

	ros::Rate loop_rate(2);


	std_msgs::Header header;
	std_msgs::String encoding ;
	std_msgs::Float32 angle_max ;
	std_msgs::Float32 angle_min ;
	std_msgs::Float32 angle_increment ;
	std_msgs::Float32 time_increment ;
	std_msgs::Float32 scan_time ;
	std_msgs::Float32 range_max ;
	std_msgs::Float32 range_min ;
	std_msgs::Float32MultiArray ranges ;
	std_msgs::Float32MultiArray intensities ;
	std_msgs::UInt32 height ;
	std_msgs::UInt32 width ;
	std_msgs::UInt8 is_bigendian ;
	std_msgs::UInt32 step ;
	std_msgs::UInt8MultiArray data ;
	
	int count = 0;
	while (ros::ok())
	{
		std_msgs::String msg_head;
		std_msgs::String msg_amax;
		std_msgs::String msg_amin;
		std_msgs::String msg_ainc;
		std_msgs::String msg_tinc;
		std_msgs::String msg_st;
		std_msgs::String msg_rmax;
		std_msgs::String msg_rmin;
		std_msgs::String msg_ran;
		std_msgs::String msg_inten;
		std_msgs::String msg_hei;
		std_msgs::String msg_wid;
		std_msgs::String msg_isb;
		std_msgs::String msg_step;
		std_msgs::String msg_data;
		std_msgs::String msg_enc;



		std::stringstream amin;
		std::stringstream amax;
		std::stringstream head;
		std::stringstream ainc;
		std::stringstream tinc;
		std::stringstream st;
		std::stringstream rmax;
		std::stringstream rmin;
		std::stringstream ran;
		std::stringstream inten;
		std::stringstream hei;
		std::stringstream wid;
		std::stringstream isb;
		std::stringstream step;
		std::stringstream data;
		std::stringstream enc;


		head << "Acquisition time of the first ray: " << header ;
		amin << "Start angle of the scan [rad]:  " << angle_min ;
		amax << "End angle of the scan [rad]:  " << angle_max ;
		ainc << "Angular distance between measurements [rad]:  " << angle_increment ;
		tinc << "Time between measurements [seconds]:  " << time_increment ;
		st << "Time between scans [seconds]:  " << scan_time;
		rmin << "Minimum range [meters]:  " << range_min ;
		rmax << "Maximum range [meters]:  " << range_max ;
		ran << "Range data [meters]:  " << ranges ;
		inten << "Intensity data:  " << intensities ;


		msg_amin.data = amin.str();
		msg_amin.data = amax.str();
		msg_ainc.data = ainc.str();
		msg_tinc.data = tinc.str();
		msg_st.data = st.str();
		msg_rmin.data = rmin.str();
		msg_rmax.data = rmax.str();
		msg_ran.data = ran.str();
		msg_inten.data = inten.str();

		// ROS_INFO("%s", msg1.data.c_str());
		// ROS_INFO("%s", msg2.data.c_str());
		// ROS_INFO("%s", msg3.data.c_str());


		// chatter_pub.publish(msg1);
		// chatter_pub.publish(msg2);
		// chatter_pub.publish(msg3);

		ros::spinOnce();

		loop_rate.sleep();
		++count ;

	}


}