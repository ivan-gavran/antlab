#!/usr/bin/env python
import os
import rospy
import actionlib
import pdb
import argparse
import pyglet
import geometry_functions
import tf

from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from geometry_msgs.msg import Pose2D, Point, PoseStamped
from std_msgs.msg import String, Bool
from multiple_robots_stage.msg import PriorityPosition, NavigationActivityStatus, PriorityPositionSimple, PatrolStatus, RobotStatus
from multiple_robots_stage.srv import RobotPose, CrashRobot, CrashRobotResponse
from nav_msgs.msg import Odometry
import std_msgs






class ActionExec(object):
    def __init__(self, client_topic='move_base'):
        
        self.name = rospy.get_param('~robot_name')
        self.priority = self.name
        self.client_topic = client_topic
        self.epsilon = 0.5
        
        # dictionary of active robots. it would be used to avoid collisions (if another active robot is approaching, check priority.
        # if the robot stopped its activity, treat it as a static obstacle)
        self.otherActiveRobots = {}
        
        self.active = False
        self.crashed = False
        
        #hardcoded at the moment
        self.position = Pose2D(10,10, 0)
        self.goalPaused = False
        self.blockingRobots = set()
        self.tf_listener = tf.TransformListener()
        
        self.robotPositionService = rospy.Service('robot_position', RobotPose, self.getRobotPosition)
        self.crashingService = rospy.Service('crash', CrashRobot, self.crash)
        self.cancellingRequestService = rospy.Service('cancel_patrol_task', RobotPose, self.stopTheExecution)
        
        self.status_publisher = rospy.Publisher('patrol_status', PatrolStatus, queue_size=10)
        self.robot_status_publisher = rospy.Publisher('/robot_status', RobotStatus, queue_size=10)
        self.directions_subscriber = rospy.Subscriber('coordinator_directions', Pose2D, self.sendARobot)
        self.positions_subscriber = rospy.Subscriber('/collision_positions', PriorityPositionSimple, self.receiveAPosition)
        self.positions_publisher = rospy.Publisher('/collision_positions', PriorityPositionSimple, queue_size=10 )
        self.navigation_status_publisher = rospy.Publisher('/navigation_activity_status', NavigationActivityStatus, queue_size=10, latch=True )
        self.navigation_status_subscriber = rospy.Subscriber('/navigation_activity_status', NavigationActivityStatus, self.receiveNavigationStatus )
        self.pose_ground_truth_subscriber = rospy.Subscriber('base_pose_ground_truth', Odometry, self.ground_truth_cb)
        
        self.client = actionlib.SimpleActionClient(self.client_topic, MoveBaseAction)
        self.client.wait_for_server()
        
        rospy.logdebug('initialized action exec')
    
    def receiveNavigationStatus(self, msg):
        self.otherActiveRobots[msg.name] = msg.activity_status
        rospy.logdebug(msg)
        if msg.activity_status == False and msg.name in self.blockingRobots:
            self.blockingRobots.remove(msg.name)
            self.checkConditionsAndContinue()
        rospy.logdebug(self.otherActiveRobots)
    
    def ground_truth_cb(self, msg):
        rospy.logdebug(self.active)
        if self.active == True:
            rospy.logdebug('assigning new position')
            self.position = msg.pose.pose.position
            rospy.logdebug(self.position)
            message_to_send = PriorityPositionSimple()
            message_to_send.priority = self.priority
            message_to_send.robot_name = self.name
            message_to_send.position = Pose2D(self.position.x, self.position.y, 0)
            self.positions_publisher.publish(message_to_send)
    def checkConditionsAndContinue(self):
        rospy.logdebug(self.blockingRobots)
        if len(self.blockingRobots) == 0:
            rospy.logdebug('noone is blocking continuing')
            rospy.logdebug(self.currentGoal)
            rospy.logdebug("sending goal after continuation")
            rospy.logdebug(self.currentGoal)
            self.client.send_goal(self.currentGoal, done_cb=self.done_cb, active_cb=self.active_cb)
            
    def getRobotPosition(self, request={}):
        try:
            (trans, rot) = self.tf_listener.lookupTransform("/map", self.name+"/base_link", rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
            rospy.logerr(e)
            return
        return Pose2D(trans[0], trans[1], 0)
        
    def crash(self, request={}):
        self.crashed = True
        rospy.loginfo("cancelling all goals++++++++++++++++++++++++++++")
        self.client.cancel_all_goals()
        self.robot_status_publisher.publish(RobotStatus(False, self.name))
        return CrashRobotResponse(0)
    
        
    def stopTheExecution(self, request={}):
        self.client.cancel_all_goals()
        return self.getRobotPosition()
    
        
               
                
    
    def receiveAPosition(self, msg):
        rospy.logdebug(msg.position)
        othersPosition = msg.position
        agentsPosition = Pose2D(self.position.x, self.position.y, 0)
        rospy.logdebug(agentsPosition)
        rospy.logdebug(othersPosition)
        rospy.logdebug('position received')
        d = geometry_functions.plane_distance(othersPosition, agentsPosition)
        
         
        if self.goalPaused == True and msg.robot_name in self.blockingRobots:
            
            if d > self.epsilon:
                self.blockingRobots.remove(msg.robot_name)
                self.checkConditionsAndContinue()
                rospy.logdebug('removing from blocking list')
        elif self.otherActiveRobots.get(msg.robot_name)==True:
            if d < self.epsilon and self.priority < msg.priority:
                if self.active == True: 
                    rospy.logerr('too close, stopping')
                    self.client.cancel_goal()
                    self.goalPaused = True
                self.blockingRobots.add(msg.robot_name)
            
    
    def sendARobot(self, msg):
        rospy.logdebug('send a roboto situation')
        pose = msg
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id='/map' #1 map? or should there be 1 per core?
        
        self.currentPose2DGoal = pose
        
       
            
        # find a better way for this transformation
        goal.target_pose.pose.position.x = pose.x
        goal.target_pose.pose.position.y = pose.y
        goal.target_pose.pose.position.z = 0.0
        goal.target_pose.pose.orientation.x = 0.0   
        goal.target_pose.pose.orientation.y = 0.0
        goal.target_pose.pose.orientation.z = 0.0
        goal.target_pose.pose.orientation.w = 1.0
        self.currentGoal = goal
        rospy.logerr('************************')
        rospy.logerr(self.name)
        rospy.logerr("sending a goal "+str(pose.x)+" "+str(pose.y))
        self.client.send_goal(goal, done_cb=self.done_cb, active_cb=self.active_cb)
        
       
#         self.client.send_goal(goal)
#         finishedOnTime = self.client.wait_for_result(rospy.Duration(60))
#         state = self.client.get_state()
#         #result = self.client.send_goal_and_wait(goal, rospy.Duration(60))
#         # TODO
#         if state == 3:
#             self.status_publisher.publish("success")
#         else:
#             rospy.logerr("navigation failed")
#             self.status_publisher.publish("failure")
#
    def active_cb(self):
        rospy.logdebug('sending activity status')
        self.active = True
        self.navigation_status_publisher.publish(NavigationActivityStatus(self.name, True))        
    def done_cb(self, state, res):
        rospy.logerr(self.name)
        rospy.logerr('done cb')
        rospy.loginfo(state)
        self.active = False
        self.navigation_status_publisher.publish(NavigationActivityStatus(self.name, False))
        rospy.logdebug("state: "+str(state))
        if state==3:
            status_description = "success"
            
        elif state == 4:
            self.active = False
            status_description = "failure"
        else:
            self.active = False
            status_description = "cancel"
        rospy.logdebug("status description: "+status_description)
        self.status_publisher.publish(PatrolStatus(status_description, self.getRobotPosition(), self.name, self.currentPose2DGoal))
    
def main():
    parser = argparse.ArgumentParser()
    
    parser.add_argument("--robot_name", default="robot_0", help="robot's name. should be unique in order to coordinate multiple robots. default: robot_0 ")
    args, unknown = parser.parse_known_args()
    rospy.logwarn('------------------------------')
    rospy.logwarn(args)
    
    
    rospy.init_node('client_patrol', anonymous=True)
    node_name = rospy.get_name()
    actionExecuter = ActionExec()
    
    
    rospy.spin()
    
if __name__ == '__main__':
    main()
    
