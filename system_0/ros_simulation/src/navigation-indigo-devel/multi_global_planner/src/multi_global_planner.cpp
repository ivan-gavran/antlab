#include <pluginlib/class_loader.h>
#include <multi_robot_move/multi_planner_base.h>
#include <multi_global_planner/multi_global_planner.h>
#include <multi_global_planner/robotInSpace.h>
#include <multi_global_planner/robotLocationAssignment.h>
#include <multi_robot_move/ordered_pose_stamped.h>
#include <boost/unordered_map.hpp>
#include <ros/ros.h>
#include <csignal>
#include <signal.h>



namespace multi_global_planner
{
	MultiGlobalPlanner::MultiGlobalPlanner() : planner_loader("multi_robot_move", "multi_planner_base::MultiPlanner")
	{
		ROS_WARN("constructor of multi_global_planner");
		ros::NodeHandle nh;
		ros::NodeHandle private_nh("~");
		std::string multi_planner;
		private_nh.param("multi_planner", multi_planner, std::string("ant_multi_planner::AntMultiPlanner"));
		planner_ = planner_loader.createInstance(multi_planner);
		initpos_pub_ = nh.advertise<geometry_msgs::PoseStamped>("initpos",1);
		
		
		
		make_plan_srv_ = private_nh.advertiseService("make_plan", &MultiGlobalPlanner::planService, this);
		get_waypoints_srv_ = private_nh.advertiseService("get_waypoints", &MultiGlobalPlanner::getWaypoints, this);
		
	}
	bool MultiGlobalPlanner::getWaypoints(multi_global_planner::SingleRobotWaypoints::Request &req, multi_global_planner::SingleRobotWaypoints::Response &resp)
	{

		string robot_name = req.robot_name;
		ordered_pose_stamped::OrderedPoseStamped goal_location = req.goal;
		std::map<string, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > >::iterator planned_waypoints_iterator;
		std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> >::iterator helper_iterator;
		std::vector<geometry_msgs::PoseStamped> response_vector;
		planned_waypoints_iterator = plannedWaypoints.find(robot_name);
		if (planned_waypoints_iterator != plannedWaypoints.end()){
			if (planned_waypoints_iterator->second.find(goal_location) != planned_waypoints_iterator->second.end()){
				ROS_DEBUG("found the goal location (%f, %f)", goal_location.pose.position.x, goal_location.pose.position.y);
				for (int plannedWaypointsCounter = 0; plannedWaypointsCounter < plannedWaypoints[robot_name][goal_location].size(); plannedWaypointsCounter++){
					response_vector.push_back(plannedWaypoints[robot_name][goal_location][plannedWaypointsCounter]);
				}
				plannedWaypoints[robot_name].erase(goal_location);
			}
			else {

				for (helper_iterator = plannedWaypoints[robot_name].begin(); helper_iterator != plannedWaypoints[robot_name].end(); helper_iterator++ ){
					ROS_DEBUG("robot name: %s", robot_name.c_str());
					ROS_DEBUG("[[[%f %f]]]",helper_iterator->first.pose.position.x, helper_iterator->first.pose.position.y);
				}
				ROS_DEBUG("goal location not found...where it is? %f %f",goal_location.pose.position.x, goal_location.pose.position.y);
				ROS_DEBUG("(%f, %f)\n", goal_location.pose.position.x, goal_location.pose.position.y);
				//raise(SIGABRT);
				return false;
			}
		}
		else{
			ROS_DEBUG("robot name not found");
			ROS_DEBUG("%s", robot_name.c_str());
			return true;
		}
		resp.waypoints = response_vector;
		
		return true;
	}
	
	bool MultiGlobalPlanner::planService(multi_global_planner::planMultiRobotPath::Request &req, multi_global_planner::planMultiRobotPath::Response &resp)
	{
		std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > assignments;
		std::map<ordered_pose_stamped::OrderedPoseStamped, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > > plans;
		ROS_WARN("inside a service planService");
		std::vector<ordered_pose_stamped::OrderedPoseStamped> startPoses;
		std::map<ordered_pose_stamped::OrderedPoseStamped, string > startPosesRobotMapping;
		
		std::vector<geometry_msgs::PoseStamped> goalPoses = req.locations_to_visit;
		std::vector<ordered_pose_stamped::OrderedPoseStamped> goalPosesConverted;
		
		for(std::vector<geometry_msgs::PoseStamped>::iterator it = goalPoses.begin(); it != goalPoses.end(); it++){
			ordered_pose_stamped::OrderedPoseStamped temp_pose;
			temp_pose = ordered_pose_stamped::OrderedPoseStamped(*it);
			//normalizing the orientation
			temp_pose.pose.orientation.w = 1.0;
			goalPosesConverted.push_back(temp_pose);
		}
		
		std::vector<robotInSpace> initialLocations = req.available_robots;
		for (std::vector<robotInSpace>::iterator vi = initialLocations.begin(); vi != initialLocations.end(); vi++)
		{
			ordered_pose_stamped::OrderedPoseStamped ordered_pose = ordered_pose_stamped::OrderedPoseStamped(vi->robot_pose);  



			startPoses.push_back(ordered_pose);
			startPosesRobotMapping[ordered_pose] = vi->robot_name;
			

		}
		
	
		
		
		
		planner_->makePlan(startPoses, goalPosesConverted, assignments, plans);
		for (int i = 0; i < plans.size(); ++i){
			ROS_ERROR("sth found in plans");
		}
		if (plans.size() == 0){
			ROS_INFO("plans size = 0, returning ...");
			return true;
		}

		for (std::vector<robotInSpace>::iterator vi = initialLocations.begin(); vi != initialLocations.end(); vi++)
		{
			
			ordered_pose_stamped::OrderedPoseStamped current_pose = vi->robot_pose;
			string current_robot = vi->robot_name;
			//ROS_DEBUG("CURRENT_POSE: %f %f", current_pose.pose.position.x, current_pose.pose.position.y);
			//ROS_DEBUG("ROBOT_NAME: %s", current_robot.c_str());
			map<ordered_pose_stamped::OrderedPoseStamped, vector<ordered_pose_stamped::OrderedPoseStamped> >::iterator element_iterator = assignments.find(current_pose);
			if (element_iterator != assignments.end()){
				robotLocationAssignment response_element;
				response_element.robot_name = current_robot;
				plannedWaypoints[current_robot].clear();
				map<ordered_pose_stamped::OrderedPoseStamped, vector<ordered_pose_stamped::OrderedPoseStamped> > current_plans = plans[current_pose];
				

				for(map<ordered_pose_stamped::OrderedPoseStamped, vector<ordered_pose_stamped::OrderedPoseStamped> >::iterator mi =current_plans.begin(); mi != current_plans.end(); ++mi)
				{
					ROS_DEBUG("current plans for point: (%f, %f) and robot %s\n", mi->first.pose.position.x, mi->first.pose.position.y, current_robot.c_str());
					for (int j = 0; j < mi->second.size(); ++j){
						ROS_DEBUG("[[%f, %f]]\n", mi->second[j].pose.position.x, mi->second[j].pose.position.y);
					}
				}


				plannedWaypoints[current_robot] = current_plans;

				/*
				for (int i = 0; i < current_plans.size(); ++i){
					plannedWaypoints[current_robot].push_back(current_plans[i]);
				}
				*/
				//plannedWaypoints[current_robot] = plans[current_pose];
				vector<ordered_pose_stamped::OrderedPoseStamped> listOfLocations = element_iterator->second;
				for (vector<ordered_pose_stamped::OrderedPoseStamped>::iterator opsi = listOfLocations.begin(); opsi != listOfLocations.end(); ++opsi)
				{
					response_element.locations_to_visit.push_back(*opsi);
				}
			
			resp.assignment.push_back(response_element);
			}
		}
		
		
		
		return true;
	}
};


