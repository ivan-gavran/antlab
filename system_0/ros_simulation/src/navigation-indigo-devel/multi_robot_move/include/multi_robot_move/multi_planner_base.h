
#ifndef MULTI_ROBOT_MOVE__MULTI_PLANNER_BASE_H_
#define MULTI_ROBOT_MOVE__MULTI_PLANNER_BASE_H_

#include <geometry_msgs/PoseStamped.h>
#include <costmap_2d/costmap_2d_ros.h>
#include "ordered_pose_stamped.h"

namespace multi_planner_base {
  /**
   * @class MultiPlannerBase
   * @brief Provides an interface for global planners used in navigation of multiple robots. All global planners written as plugins for the navigation stack must adhere to this interface.
   */
  class MultiPlanner{
    public:
      /**
       * @brief Given a vector of goal poses in the world, compute a plan to visit them all from given starting positions (all the goal positions have to be visited, but not all of the start positions should be used for that)
       * @param start_poses The vector start poses 
       * @param goal_poses The vector of goal poses 
       * @param plan The plan... filled by the planner
       * @return True if a valid plan was found, false otherwise
       */
      virtual bool makePlan(std::vector<ordered_pose_stamped::OrderedPoseStamped>& start_poses,
		          std::vector<ordered_pose_stamped::OrderedPoseStamped>& goal_poses,
				  std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> >& assignments,
				  std::map<ordered_pose_stamped::OrderedPoseStamped, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > >& plans) = 0;


      /**
       
       */
      virtual void initialize() = 0;

      /**
       * @brief  Virtual destructor for the interface
       */
      virtual ~MultiPlanner(){}

      MultiPlanner(){}
  };
};

#endif
