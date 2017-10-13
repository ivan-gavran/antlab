#ifndef MULTI_GLOBAL_PLANNER__H_
#define MULTI_GLOBAL_PLANNER__H_
#include <geometry_msgs/PoseStamped.h>

#include <multi_robot_move/multi_planner_base.h>
#include <multi_robot_move/ordered_pose_stamped.h>
#include <string>
#include <multi_global_planner/planMultiRobotPath.h>
#include <multi_global_planner/SingleRobotWaypoints.h>
#include <pluginlib/class_loader.h>
#include <tf/transform_listener.h>


using namespace std;
namespace multi_global_planner
{
	class MultiGlobalPlanner{
	public:
		std::map<string, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > >plannedWaypoints;
		pluginlib::ClassLoader<multi_planner_base::MultiPlanner> planner_loader;
		MultiGlobalPlanner();
	private:
		boost::shared_ptr<multi_planner_base::MultiPlanner> planner_;
		ros::Publisher initpos_pub_;
		tf::TransformListener tf_listener_;
		ros::ServiceServer make_plan_srv_;
		ros::ServiceServer get_waypoints_srv_;
		bool planService(multi_global_planner::planMultiRobotPath::Request &req, multi_global_planner::planMultiRobotPath::Response &resp);
		bool getWaypoints(multi_global_planner::SingleRobotWaypoints::Request &req, multi_global_planner::SingleRobotWaypoints::Response &resp);

	};
};

#endif
