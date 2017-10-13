import rospy
import logging
from std_msgs.msg import String
import random
from utils.pg_point_type import Point
from geometry_msgs.msg import Pose2D
from xudd.actor import Actor
from config import settings
import pdb, re
from multiple_robots_stage.msg import PatrolStatus, RobotStatus
from multiple_robots_stage.srv import RobotPose
_log = logging.getLogger(__name__)

class PatrollingTaskOrganizer(Actor):
    def __init__(self, hive, id):
        super(PatrollingTaskOrganizer, self).__init__(hive, id)
        _log.info('initializing task_organizer')
        
        
        self.message_routing.update(
            {"start_task_execution": self.startTheTask,
             "stop_task_execution":self.stopTheTask})
        
    def startTheTask(self, message):
        self.retired = False
        rospy.logerr("start of task organizer")
        self.taskActive = False
        _log.info('task started')
        self.taskActive = True
        self.robotAssignments = message.body['robotAssignments']
        self.testName = message.body['test_name']
        _log.info(self.robotAssignments)
        self.directionsTopics = {}
        self.task_id = message.body['task_id']
        self.nextPositionIndex = {}
        self.status_subscribers = {}
        self.directionsPublishers = {}
        self.locations = {}
        self.positionsReached = {}
        
        self.numberOfRobots = len(self.robotAssignments)
        self.numberOfRobotsFinished = 0
        self.status = 'success'
        self.robotsPositions = {}
        self.stopPatrollingRobot = {}
        self.crash_reports = rospy.Subscriber('/robot_status', RobotStatus, self.handleCrashInfo)
        #pdb.set_trace()
        for robotName in self.robotAssignments:
            self.directionsTopics[robotName] = robotName+'/coordinator_directions'
            self.nextPositionIndex[robotName] = 0
            # dict position:boolean (true if reached, false if failed to reach)
            self.positionsReached[robotName] = {(location.x, location.y):False for location in self.robotAssignments[robotName]}
            self.status_subscribers[robotName] = rospy.Subscriber(robotName+'/patrol_status', PatrolStatus, self.nextStep)
            self.directionsPublishers[robotName] = rospy.Publisher(self.directionsTopics[robotName], Pose2D, queue_size=10, latch=True)
            self.locations[robotName] = self.robotAssignments[robotName]
            self.stopPatrollingRobot[robotName] = rospy.ServiceProxy(robotName+'/cancel_patrol_task', RobotPose)
        self.robots = self.robotAssignments.keys()
        rospy.init_node('coordinator', anonymous=True)
        for robotName in self.robotAssignments:
            _log.info(robotName+' chosen')
            self.sendDirection(robotName)
        #self.pose_subscriber = rospy.Subscriber(self.robot_name+'/base_pose_ground_truth', Pose2D, self.getPosition, queue_size=1, )
    
    def stopTheTask(self, message, robots=None):
        
        if robots == None:
            robots = self.robots
        for robot in robots:
            pos = self.stopPatrollingRobot[robot]()
            
    def handleCrashInfo(self, msg):
        if self.retired == False:
            self.hive.send_message(to=settings.SWARM_KEEPER, directive="crash_report", body={'crashed_robot':msg.robotName})    
    
    def getPackages(self, msg):
        pass
        
        
    def nextStep(self, msg=String("")):
        if self.retired == False:
       
            robotName = msg.robot_name
            robotPosition  = msg.position
            trackedGoal = msg.trackedGoal
            _log.debug("**trackedGoal**")
            _log.debug(trackedGoal)
            _log.debug("nextStep**")
            _log.debug(msg)
            _log.debug("nextStep**")
    #         if robotName == "robot_0":
    #             pdb.set_trace()
            
            if msg.status == "failure":
#                 rospy.logerr("failure and next step --------")
#                 rospy.logerr(trackedGoal)
#                 rospy.logerr(self.locations[robotName][-1])
                if Point(trackedGoal)== self.locations[robotName][-1]:
                    self.endOfExecution(status="bla", robotName=robotName, position=robotPosition)
                else:
                    rospy.loginfo('intermediate position could not be reached '+robotName)
                    self.sendDirection(robotName)
                
            elif msg.status == "cancel":
                self.endOfExecution(robotName=robotName, status='cancel', position=robotPosition)
            elif msg.status == "crash":
                self.endOfExecution(status='crash', robotName=robotName, position = robotPosition)
            else:
                self.positionsReached[robotName][(trackedGoal.x, trackedGoal.y)] = True
                if self.nextPositionIndex[robotName] == len(self.locations[robotName]):
                    rospy.loginfo('final position reached '+robotName)
                    self.endOfExecution(status='success', robotName = robotName, position = robotPosition)
                else:
                    rospy.loginfo('intermediate position reached '+robotName)
                    self.sendDirection(robotName)
                    
        else:
            pass
                
    def sendDirection(self, robotName='robot_0'):
        pub = self.directionsPublishers[robotName]
        positionIndex = self.nextPositionIndex[robotName]
#         if robotName=='robot_0' and positionIndex == 1:
#             pdb.set_trace()
        rospy.logerr(self.nextPositionIndex[robotName])
        try:
            position = self.locations[robotName][positionIndex]
        except:
            pdb.set_trace()
        self.nextPositionIndex[robotName] = self.nextPositionIndex[robotName] + 1
        direction = Pose2D(position.x, position.y, 0)
#         rospy.logerr('----------------')
#         rospy.logerr(positionIndex)
#         rospy.logerr(position)
#         rospy.logerr(robotName)
#         rospy.logerr('---------------')
        #rospy.sleep(2.0)
        pub.publish(direction)
    
    def getRobotPosition(self, robotName):
        #TODO: implement actual function
        return self.robotAssignments[robotName][-1]
    
    def endOfExecution(self, robotName="", status='success', position=Pose2D()):
        self.numberOfRobotsFinished = self.numberOfRobotsFinished + 1
        self.robotsPositions[robotName] = position
        rospy.loginfo("finished by now: "+str(self.numberOfRobotsFinished))
        rospy.loginfo("all robots "+str(self.numberOfRobots))
        if status != 'success':
            self.status = status
        
            
        
        if self.numberOfRobotsFinished == self.numberOfRobots:
            self.retired = True
           
            self.send_message(to=settings.SWARM_KEEPER, directive="task_report", body={'robot_positions':self.robotsPositions,\
                                                                                        'task_id':self.task_id,\
                                                                                         'status':status,\
                                                                                         'test_name':self.testName,\
                                                                                         'positions_reached':self.positionsReached})
        