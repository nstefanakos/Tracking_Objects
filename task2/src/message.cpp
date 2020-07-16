# include "ros/ros.h"
# include <sensor_msgs/LaserScan.h>
# include <sensor_msgs/Image.h>
# include <cmath>
# include <vector>
# include "task2/laserscan.h"
# include "task2/image.h"


ros::Publisher pub_1;
ros::Publisher pub_2;
ros::Publisher pub_3;
ros::Publisher pub_4;

int count = 0;
int count_2 = 0;
bool separated ;

std::vector<float> old_ranges;
std::vector<unsigned char> old_rgb;

void Callback_1(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	ros::NodeHandle nh;

	sensor_msgs::LaserScan new_msg(*msg);
	task2::laserscan cus_msg;

	cus_msg.header = new_msg.header;
	cus_msg.distances = new_msg.ranges;

	int count_1 = 0;

	if (count == 0)
	{
		old_ranges = cus_msg.distances;
	}

	if (separated == true)
	{
		for (int i = 0 ; i < cus_msg.distances.size(); i++)
		{
			if (abs(old_ranges[i] - cus_msg.distances[i]) <= 0.7 || abs(old_ranges[i] - cus_msg.distances[i]) > 7)
			{
				cus_msg.distances[i] = new_msg.range_max + (float) 1 ;  
				// new_msg.ranges[i] = new_msg.range_max + (float) 1 ;  
				new_msg.ranges[i] = 1;  
				count_1 = count_1 + 1;
			}
		}
		if (count_1 != cus_msg.distances.size())
		{
			pub_1.publish(cus_msg);
			pub_2.publish(new_msg);
		}

	}

	else 
	{

		for (int i = 0 ; i < cus_msg.distances.size(); i++)
		{

			cus_msg.angles.push_back (new_msg.angle_min + (i * new_msg.angle_increment)); 
	
			if (abs(old_ranges[i] - 1) <= abs(cus_msg.distances[i]))
			{
				cus_msg.distances[i] = new_msg.range_max + (float) 1 ; 
				new_msg.ranges[i] = new_msg.range_max + (float) 1 ; 
				count_1 = count_1 + 1;
			}
		}

		if (count_1 != cus_msg.distances.size())
		{
			pub_1.publish(cus_msg);
			pub_2.publish(new_msg);
		}
	}
	count = count + 1 ; 
}

void Callback_2(const sensor_msgs::Image::ConstPtr& msg)
{
	ros::NodeHandle nh;

	sensor_msgs::Image new_msg(*msg);
	task2::image cus_msg;

	cus_msg.header = new_msg.header;
	cus_msg.pixel_values = new_msg.data;
	
	int count_3 = 0;

	if (count_2 == 0)
	{
		old_rgb = cus_msg.pixel_values;
	}

	if (separated == true)
	{
		for (int i = 0 ; i < cus_msg.pixel_values.size(); i = i + 3)
		{
			if (abs(old_rgb[i] - cus_msg.pixel_values[i]) < 25 && abs(old_rgb[i+1] - cus_msg.pixel_values[i+1]) < 25 && abs(old_rgb[i+3] - cus_msg.pixel_values[i+3]) < 25)
			{
				cus_msg.pixel_values[i] = sqrt((new_msg.data[i]*new_msg.data[i] + new_msg.data[i+1]*new_msg.data[i+1] + new_msg.data[i+2]*new_msg.data[i+2]) / 3);  
				cus_msg.pixel_values[i+1] = sqrt((new_msg.data[i]*new_msg.data[i] + new_msg.data[i+1]*new_msg.data[i+1] + new_msg.data[i+2]*new_msg.data[i+2]) / 3);  
				cus_msg.pixel_values[i+2] = sqrt((new_msg.data[i]*new_msg.data[i] + new_msg.data[i+1]*new_msg.data[i+1] + new_msg.data[i+2]*new_msg.data[i+2]) / 3);
				new_msg.data[i] = cus_msg.pixel_values[i];
				new_msg.data[i+1] = cus_msg.pixel_values[i+1];
				new_msg.data[i+2] = cus_msg.pixel_values[i+2];
				count_3 = count_3 + 1;
			}
			else 
			{
				old_rgb[i] = cus_msg.pixel_values[i];
				old_rgb[i+1] = cus_msg.pixel_values[i+1];
				old_rgb[i+2] = cus_msg.pixel_values[i+2];
			}
		}

		if (count_3 != (cus_msg.pixel_values.size()/3))
		{
			pub_3.publish(cus_msg);
			pub_4.publish(new_msg);
		}

	}
	else 
	{
		for (int i = 0 ; i < cus_msg.pixel_values.size(); i = i + 3)
		{
			if (abs(old_rgb[i] - cus_msg.pixel_values[i]) <= 10 || abs(old_rgb[i+1] - cus_msg.pixel_values[i+1]) <= 10 || abs(old_rgb[i+3] - cus_msg.pixel_values[i+3]) <= 10)
			{
				cus_msg.pixel_values[i] = sqrt((new_msg.data[i]*new_msg.data[i] + new_msg.data[i+1]*new_msg.data[i+1] + new_msg.data[i+2]*new_msg.data[i+2]) / 3);  
				cus_msg.pixel_values[i+1] = sqrt((new_msg.data[i]*new_msg.data[i] + new_msg.data[i+1]*new_msg.data[i+1] + new_msg.data[i+2]*new_msg.data[i+2]) / 3);  
				cus_msg.pixel_values[i+2] = sqrt((new_msg.data[i]*new_msg.data[i] + new_msg.data[i+1]*new_msg.data[i+1] + new_msg.data[i+2]*new_msg.data[i+2]) / 3);
				new_msg.data[i] = cus_msg.pixel_values[i];
				new_msg.data[i+1] = cus_msg.pixel_values[i+1];
				new_msg.data[i+2] = cus_msg.pixel_values[i+2];
				count_3 = count_3 + 1;
			}
			else 
			{
				old_rgb[i] = cus_msg.pixel_values[i];
				old_rgb[i+1] = cus_msg.pixel_values[i+1];
				old_rgb[i+2] = cus_msg.pixel_values[i+2];
			}
		}

		if (count_3 != (cus_msg.pixel_values.size()/3))
		{
			pub_3.publish(cus_msg);
			pub_4.publish(new_msg);
		}
	}
	count_2 = count_2 + 1 ; 
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "listen");

	ros::NodeHandle n;

	n.getParam("/separated", separated);

	ros::Subscriber sub = n.subscribe("/scan", 10000, Callback_1);

	pub_1 = n.advertise<task2::laserscan>("new_scan", 1000);
	pub_2 = n.advertise<sensor_msgs::LaserScan>("new_scan_2", 1000);

	ros::Subscriber image = n.subscribe("/radio_cam/rgb/image_raw", 1000, Callback_2);

	pub_3 = n.advertise<task2::image>("new_rgb", 1000);
	pub_4 = n.advertise<sensor_msgs::Image>("new_rgb_2", 1000);

	ros::Rate loop_rate(100);

	while (ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}