#include <multi_global_planner/multi_global_planner.h>
#include <ros/ros.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "multi_global_planner");
  ROS_WARN("in main");
  multi_global_planner::MultiGlobalPlanner multi_global_planner;

  //ros::MultiThreadedSpinner s;
  ros::spin();

  return(0);
}
