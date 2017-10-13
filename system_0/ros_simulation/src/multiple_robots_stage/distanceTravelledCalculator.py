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






class DistanceTravelledCalc(object):
    def __init__(self, client_topic='move_base'):
        
        self.totalDistanceTravelled = 0
        self.pose_ground_truth_subscriber = rospy.Subscriber('base_pose_ground_truth', Odometry, self.ground_truth_cb)
        self.end_of_actions_subsriber = rospy.Subscriber('/action_done', Int32, self.forwardTheDistances)
        self.final_distance_publisher = rospy.Publisher('/all_distances', Float32, queue_size=10 )
        rospy.logdebug('initialized distance travelled calculator')
        self.lastPose = None
    
    def distance(self, currentPose, lastPose):
        if lastPose == None:
            return 0
        return math.sqrt( (currentPose.position.x - lastPose.position.x)**2 + (currentPose.position.y - lastPose.position.y)**2 )
        
        
    def forwardTheDistances(self, msg):
        
        self.final_distance_publisher.publish(Float32(self.totalDistanceTravelled))
        self.totalDistanceTravelled = 0
        
        
    def ground_truth_cb(self, msg):
        if self.lastPose == None:
            self.lastPose = msg.pose.pose
            return
        if msg.header.seq % 5 == 0:
            currPose = msg.pose.pose
            self.totalDistanceTravelled += self.distance(currPose, self.lastPose)
            self.lastPose = currPose
            return
def main():
    parser = argparse.ArgumentParser()
    
    
    rospy.init_node('distance_calculator', anonymous=True)
    node_name = rospy.get_name()
    distanceCalculator = DistanceTravelledCalc()
    
    
    rospy.spin()
    
if __name__ == '__main__':
    main()
    
