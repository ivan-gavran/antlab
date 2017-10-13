#ifndef MULTI_ROBOT_MOVE__ORDERED_POSE_STAMPED_H_
#define MULTI_ROBOT_MOVE__ORDERED_POSE_STAMPED_H_

#include <geometry_msgs/PoseStamped.h>
namespace ordered_pose_stamped {
class OrderedPoseStamped : public geometry_msgs::PoseStamped
{
public:
	OrderedPoseStamped(geometry_msgs::PoseStamped g) : geometry_msgs::PoseStamped(){
		this->header = g.header;
		this->pose = g.pose;
	}
	OrderedPoseStamped() : geometry_msgs::PoseStamped(){}
};
bool operator<(const OrderedPoseStamped a, const OrderedPoseStamped b)
	{
		if (a.pose.position.x < b.pose.position.x)
			return true;
		else if ( a.pose.position.x > b.pose.position.x )
			return false;
		else
			return a.pose.position.y < b.pose.position.y;

	}


};
#endif
