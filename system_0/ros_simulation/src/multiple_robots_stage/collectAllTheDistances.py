#!/usr/bin/env python
import os
import rospy
import actionlib
import pdb
import argparse
import pyglet
import geometry_functions
import tf
import math

from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from geometry_msgs.msg import Pose2D, Point, PoseStamped
from std_msgs.msg import String, Bool, Int32, Float32
from multiple_robots_stage.msg import PriorityPosition, NavigationActivityStatus, PriorityPositionSimple, PatrolStatus, RobotStatus
from multiple_robots_stage.srv import RobotPose, CrashRobot, CrashRobotResponse
from nav_msgs.msg import Odometry
import std_msgs
import pdb





class CollectAllDistances(object):
    def __init__(self, client_topic='move_base'):
        
        self.sumOfAllDistances = 0
        self.numberOfDistancesReceived = 0
        
        self.totalNumberOfRobots = int(rospy.get_param("~number_of_robots"))
        self.distances_subscriber = rospy.Subscriber('/all_distances', Float32, self.addDistance )
        
        
    
    def addDistance(self, msg):
        self.sumOfAllDistances += msg.data
        self.numberOfDistancesReceived += 1
        if self.numberOfDistancesReceived == self.totalNumberOfRobots:
            statsFile = "/home/ivan/antlab-repo/system_0/staticFilesTesting/ltlResults"
            with open(statsFile, "a") as stat_f:
                stat_f.write("\t"+repr(self.sumOfAllDistances))
            self.sumOfAllDistances = 0
            self.numberOfDistancesReceived = 0
        
        
def main():
    
    
    rospy.init_node('distance_collector', anonymous=True)
    node_name = rospy.get_name()
    distanceCollector = CollectAllDistances()
    
    
    rospy.spin()
    
if __name__ == '__main__':
    main()
    
