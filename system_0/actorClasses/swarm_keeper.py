from xudd.actor import Actor
import logging
import pdb
import datetime
from queue import Queue
from db import Task, TurtlebotAgent, Session
from .task_organizer import PatrollingTaskOrganizer
from config import settings
from utils.implanFormatConverter import metersToGridUnits, gridUnitsToMeters
from utils.pg_point_type import Point
logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger(__name__)  
import subprocess 
import json
from geometry_msgs.msg import PoseStamped
from multi_global_planner.srv import planMultiRobotPath
from multi_global_planner.msg import robotInSpace
from multiple_robots_stage.msg import RobotStatus

import rospy



class SwarmKeeper(Actor):
    def __init__(self, hive, id):
        super(SwarmKeeper, self).__init__(hive, id)
        self.taskQueue = Queue()
        self.activeTaskOrganizers = set()
        self.make_plan = rospy.ServiceProxy("/multi_global_planner/make_plan", planMultiRobotPath)
       
        self.message_routing.update(
            {"start": self.startServing,\
             "organize_task":self.organizeTask,\
             "bot_added":self.addedNewRobot,\
             "task_report":self.finalizeTask,\
             "new_turtlebot":self.newTurtlebot,\
             "cancel_tasks":self.cancelTasks,\
             "crash_report":self.receiveCrashReport})

    #once the task is finished, updates info in db, end removes dynamically created actor that
    #was executing the task. 
    # TODO: add another call assigning robots to tasks in the queue
    def finalizeTask(self, message):
        repeatTask = False
        id = message.body['task_id']
        robotStatus = message.body['status']
        robot_positions = message.body['robot_positions']
        positions_reached = message.body['positions_reached']
        
        positions_not_reached = []
        for robotName in positions_reached:
            for position in positions_reached[robotName]:
                if positions_reached[robotName][position] == False:
                    positions_not_reached.append(Point(position))
                
        if len(positions_not_reached) == 0:
            taskStatus = 'success'
            try:
                self.repeatedTasks.remove(id)
            except:
                pass
        ## invoke again all that are not finished, and add task id to list of repeated task (in order not to repeat forever)
        
        else:
            taskStatus = 'partially finished'
            if id not in self.repeatedTasks:
                self.repeatedTasks.add(id)
                repeatTask= True
                
            else:
                taskStatus = 'unable_to_finish'
            
                 
        session = Session()
        #pdb.set_trace()
        try:
            session.query(Task).filter(Task.id==id).update({Task.status:taskStatus, Task.end_of_processing:datetime.datetime.now()}, synchronize_session=False)
            for robotName in robot_positions:
                session.query(TurtlebotAgent).filter(TurtlebotAgent.name==robotName)\
                .update({TurtlebotAgent.location:Point(robot_positions[robotName]), TurtlebotAgent.available:True})
            session.commit()
            
        except Exception as e:
            pdb.set_trace()
            _log.error('problem updating task and workers in the database: '+repr(e))
        else:
            rospy.loginfo("removing task organizer")
            self.hive.remove_actor(message.from_id)
            self.activeTaskOrganizers.remove(message.from_id)
        finally:
            session.close()
        if repeatTask == True and len(positions_not_reached) > 0:
            self.hive.send_message(to = settings.SCHEDULER, directive='request', body = {'locations':positions_not_reached,\
                                                                                         'request_id':id} )
        else:
            if settings.PERFORMANCE_TESTING == True:
                _log.error("sending message to tests_generator to send another task")
                rospy.loginfo("sending message to tests_generator")
                self.hive.send_message(to = settings.TESTS_GENERATOR, directive="task_finished", body={'task_id':id, 'outcome':'success', 'test_name':message.body['test_name']})
                #self.hive.send_message(to = settings.TESTS_GENERATOR, directive='send_request')
            
    def cancelTasks(self, message):
        for taskOrganizer in self.activeTaskOrganizers:
            self.hive.send_message(to=taskOrganizer, directive="stop_task_execution")   
        

    
    def newTurtlebot(self, message):
        message.reply("halllooooo, ovdje sam")
        
    def startServing(self, message):
        _log.info(self.id+' started serving')
        self.repeatedTasks = set()
        
        #self.hive.send_message(to='generator', directive="start")
    
    def receiveCrashReport(self, msg):
        session = Session()
        try:
            session.query(TurtlebotAgent).filter(TurtlebotAgent.name==msg.body['crashed_robot'])\
                   .update({TurtlebotAgent.alive:False})
            session.commit()
        except Exception as e:
            _log.error('problem updating task and workers in the database: '+repr(e))
        finally:
            session.close()
                       
            
            
    
    def organizeTask(self, message):
        _log.debug('have to organize task :) ')
        _log.debug(repr(message.body))
        task_id = message.body['request_id']
        
        #TODO: decide which robots to send, update the info in the db
        robotsForTheTask = self.assignRobots(locations = message.body['locations'])
        _log.error(robotsForTheTask)
        session = Session()
        if len(robotsForTheTask) == 0:
            _log.error("no robots!!!")
            
            #rospy.loginfo("removing task organizer: can't be run")
            #self.hive.remove_actor(message.from_id)
            #self.activeTaskOrganizers.remove(message.from_id)
            try:
                session.query(Task).filter(Task.id==task_id).update({Task.status:'unable_to_run'}, synchronize_session=False)
                session.commit()
            except Exception as e:
                _log.error('problem updating task and workers in the database: '+repr(e))
            
                
            finally:
                session.close()
            if settings.PERFORMANCE_TESTING:
                    #pdb.set_trace()
                    self.send_message(to=settings.TESTS_GENERATOR, directive="task_finished", body={'outcome':'fail', 'test_name':message.body['test_name']})
        else:
            rospy.loginfo("creating task organizer")
            taskOrganizer = self.hive.create_actor(PatrollingTaskOrganizer)
            self.activeTaskOrganizers.add(taskOrganizer)
            try:
                testName = message.body['test_name']
            except:
                testName = 'default'
                
            try:    
                session.query(TurtlebotAgent).filter(TurtlebotAgent.name.in_(robotsForTheTask))\
                .update({TurtlebotAgent.available:False}, synchronize_session=False)
                session.query(Task).filter(Task.id==task_id).update({Task.status:'in_progress'}, synchronize_session=False)
                session.commit()
                if settings.PERFORMANCE_TESTING:
                    self.send_message(to=settings.TESTS_GENERATOR, directive="task_sent_to_execution", body={'task_id':task_id})
                self.send_message(to=taskOrganizer, directive='start_task_execution', \
                              body={ 'robotAssignments':robotsForTheTask,\
                                    'task_id':task_id, 'test_name':testName})
            except Exception as e:
                _log.error('problem updating task and workers in the database: '+repr(e))
            
                
            finally:
                session.close()
        
    def addedNewRobot(self, message):
        robotId = message.body['id']
        _log.debug('added new robot with id '+repr(robotId))
    
    def assignRobots(self, locations):
        try:
            session = Session()
            availableRobots = session.query(TurtlebotAgent).filter(TurtlebotAgent.available==True)\
                                                        .filter(TurtlebotAgent.alive==True).all()
            #availableRobots = [robot[0] for robot in availableRobots]
        except:
            raise 
        assignments = {  }
        arg_goals = []
        arg_robots = []
        
        setOfGoals = set()
        setOfRobotLocations = set()
        #for bot_name in availableRobots:
        numRobots = len(availableRobots)
        if numRobots == 0:
            return assignments
        # generate optimal assignment using implan
        if settings.IMPLAN_ASSIGNMENT == True:
            for robot_desc in availableRobots:
                robotName = robot_desc.name  
                robot = robotInSpace()
                robotLocation = PoseStamped()
                robotLocation.pose.position.x = robot_desc.location.x
                robotLocation.pose.position.y = robot_desc.location.y
                setOfRobotLocations.add((robot_desc.location.x, robot_desc.location.y))
                robot.robot_pose = robotLocation
                robot.robot_name = robotName
                arg_robots.append(robot)
            for goal_desc in locations:
               goal = PoseStamped()
               goal.pose.position.x = goal_desc.x
               goal.pose.position.y = goal_desc.y
               setOfGoals.add((goal_desc.x, goal_desc.y))
               arg_goals.append(goal)
            if setOfGoals <= setOfRobotLocations:
                allRobotsAssignments = { r.name:[ l for l in locations if (r.location.x == l.x and r.location.y == l.y) ] for r in availableRobots }
                return { r : allRobotsAssignments[r] for r in allRobotsAssignments if allRobotsAssignments[r] != [] }
            
            res = self.make_plan(arg_goals, arg_robots)
            for ass in res.assignment:
                if ass.locations_to_visit == []:
                    continue
                robot_name = ass.robot_name
                assignments[robot_name] = []
                for location in ass.locations_to_visit:
                    assignments[robot_name].append(location.pose.position)
                
   
           
        # greedy algorithm: to each location assign the nearest agent (also taken into account their 'future' positions. nearest = air distance        
        else:
            
            
            loggingFile = open('ros_simulation/src/multiple_robots_stage/static_files_folder/costs/vanilla.txt', 'a')
            robotLocations = {robot.name:robot.location for robot in availableRobots}
            while len(locations) > 0:
                (minDistance, robotToPerform, assignedLocation) = min([ (Point.distance(robotLocations[agentName], goalLoc), agentName, goalLoc ) for agentName in robotLocations for goalLoc in locations  ])
                if robotToPerform in assignments:
                    assignments[robotToPerform].append(assignedLocation)
                else:
                    assignments[robotToPerform]= [assignedLocation]
                loggingFile.write("%s %s\n" % (repr(robotLocations[robotToPerform]), repr(assignedLocation)))
                
                    
                locations.remove(assignedLocation)
                robotLocations[robotToPerform] = assignedLocation
            # here implement the nearest neighbor algorithm
            #assignments = { r.name:[] for r in availableRobots }
            loggingFile.write("-----\n")
            for rob in assignments:
                print("robot "+rob+" is assigned:")
                for loc in assignments[rob]:
                    print("("+repr(loc.x)+", "+repr(loc.y)+")")
            
            
#             assignments = {}
#             for i in range(len(locations)):
#                 candidateRobot = availableRobots[ i % numRobots ].name
#                 if candidateRobot not in assignments: 
#                     assignments[candidateRobot] = []
#                 assignments[ candidateRobot ].append(locations[i])
#             _log.error(assignments)
        return assignments
