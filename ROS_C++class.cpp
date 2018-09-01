#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "geometry_msgs/PointStamped.h"
class SubPub{
	public:
		SubPub{
			pub = n.advertise<geometry_msgs::PointStamped>("/output", 1000);
			sub = n.subscribe("/input", 1000, &SubPub::conv, this);
		}
		void conv(const geometry_msgs::PointStamped &point_in){
			geometry_msgs::PointStamped point_out;
			listener.transformPoint("core_frame", point_in, point_out);
			pub.publish(point_out);
			ros::spinOnce();
		}
	private:
		 ros::NodeHandle n;
		 ros::Subscriber sub;
		 ros::Publisher pub;
		 tf::TransformListener listener;
}
int main(int argc, char **argv){
	ros::init(argc, argv, "tfconv");
	SubPub StNode;
	ros::spin();
	return 0;
}
