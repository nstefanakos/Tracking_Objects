# include "ros/ros.h"
# include "sensor_msgs/LaserScan.h"
# include "nav_msgs/OccupancyGrid.h"
# include <visualization_msgs/MarkerArray.h>
# include <marker/cus_mark.h>
# include <message_filters/subscriber.h>
# include <message_filters/time_synchronizer.h>
# include <message_filters/sync_policies/approximate_time.h>
# include <cmath>
# include <vector>

ros::Publisher pub_1;
ros::Publisher pub_2;
nav_msgs::OccupancyGrid grid;

int count = 0;

void callback(const sensor_msgs::LaserScan::ConstPtr& msg, const marker::cus_mark::ConstPtr& msg_2)
{
	sensor_msgs::LaserScan new_msg(*msg);
	marker::cus_mark new_msg_2(*msg_2);

	grid.header.frame_id = "/hokuyo_base_laser_link";
	grid.header.stamp = ros::Time::now();

	if ( count == 0 )
	{
		grid.info.map_load_time = ros::Time::now();
		grid.info.resolution = 0.2;
		grid.info.width = 80;
		grid.info.height = 80;
		grid.info.origin.position.x = 8;
		grid.info.origin.position.y = 8;
		grid.info.origin.position.z = 0;
		grid.info.origin.orientation.x = 0.7071066;
		grid.info.origin.orientation.y = -0.7071066;
		grid.info.origin.orientation.z = 0;
		grid.info.origin.orientation.w = 0;
		count++ ;
	}

	for (int i = 0 ; i < (grid.info.width*grid.info.height); i++)
	{
		grid.data.push_back(0);
	}
	
	for (int j = 0 ; j < new_msg.ranges.size() ; j++)
	{
		float th = new_msg.angle_min + j * new_msg.angle_increment;
		float x0 = new_msg.ranges[j] * cos(th);
		float y0 = new_msg.ranges[j] * sin(th);
		int x;
		int y;

		x = grid.info.width*grid.info.height/2 - int(x0/grid.info.resolution)*grid.info.height - (grid.info.width);
		y = grid.info.width/2 - y0/grid.info.resolution;

		int k = floor(x+y);

		if (k >= 0 && k < grid.data.size())
		{
			grid.data[k] = 100;
		}
	}

	for (int i = 0 ; i < new_msg_2.array.markers.size() ; i++)
	{
		int x = grid.info.width*grid.info.height/2 - int(new_msg_2.array.markers[i].pose.position.x/grid.info.resolution)*grid.info.height - (grid.info.width);
		int y = grid.info.width/2 - new_msg_2.array.markers[i].pose.position.y/grid.info.resolution;

		int k = floor(x+y);

		
		grid.data[k] = 100;
		
	}

	pub_1.publish(grid);

	grid.data.erase(grid.data.begin(), grid.data.end());

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "Mapping");

	ros::NodeHandle n;

	message_filters::Subscriber<sensor_msgs::LaserScan> laser_sub(n, "/scan", 100);
	message_filters::Subscriber<marker::cus_mark> marker_sub(n, "/visualization_marker_array_2", 100);
	typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::LaserScan, marker::cus_mark> MySyncPolicy;
	message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), laser_sub, marker_sub);
	sync.registerCallback(boost::bind(&callback, _1, _2));

	pub_1 = n.advertise<nav_msgs::OccupancyGrid>("Map_grid", 1000);

	ros::spin();

	return 0;
}