#!/usr/bin/env python
import rospy
import pdb
from geometry_msgs.msg import PoseStamped
from multi_global_planner.srv import planMultiRobotPath, SingleRobotWaypoints
from multi_global_planner.msg import robotInSpace

goals = [{"x":3, "y":9}, {"x":4, "y":11},{"x":3, "y":11}]
robots = [{"name":"robot_0", "x":2,"y":9},{"name":"robot_1", "x":3, "y":10}]

make_plan = rospy.ServiceProxy("/multi_global_planner/make_plan", planMultiRobotPath)
get_waypoints = rospy.ServiceProxy("/multi_global_planner/get_waypoints", SingleRobotWaypoints)

# arg_goals = []
# arg_robots = []
# for goal_desc in goals:
#    goal = PoseStamped()
#    goal.pose.position.x = goal_desc["x"]
#    goal.pose.position.y = goal_desc["y"]
#    arg_goals.append(goal)
# 
# for robot_desc in robots:
#     robotName = robot_desc["name"]
#     robot = robotInSpace()
#     robotLocation = PoseStamped()
#     robotLocation.pose.position.x = robot_desc["x"]
#     robotLocation.pose.position.y = robot_desc["y"]
# 
#     robot.robot_pose = robotLocation
#     robot.robot_name = robotName
#     arg_robots.append(robot)
# 
#     
#  
#     
# 
# res = make_plan(arg_goals, arg_robots)
goal = PoseStamped
goal.pose.position.x = 3
goal.pose.position.y = 9
goal.pose.orientation.w = 1
res = get_waypoints('robot_0', goal)
pdb.set_trace()
a = 8