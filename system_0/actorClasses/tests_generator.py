from xudd.actor import Actor
import logging
import pdb
from config import settings
import asyncio
import random
from db import Task, TurtlebotAgent, Session
from utils.pg_point_type import Point
import time
import datetime
import os
import json
logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger(__name__)   
from utils.tbot_json_encoder import TurtlesEncoder
from shutil import copyfile

class TestsGenerator(Actor):
    def __init__(self, hive, id):
        super(TestsGenerator, self).__init__(hive, id)
        self.session = Session()
        self.testingLocations = []
        self.locationsFromFile = False
        self.locationsIndex = 0
        self.testStatistics = {}
        self.requestsToFulfill = []
        self.numberOfTasksFinished = 0
        self.numberOfRepeats = 1
        self.totalNumberOfTasks = 10
        _log.info("init tests generator")
        self.message_routing.update({"start": self.startServing,\
             "send_request":self.sendRequest,\
             "task_sent_to_execution":self.taskSentToExecution,\
             "task_finished":self.taskFinished})
        
    def startServing(self, message=None):
        
        self.firstTime = True
        if settings.TEST_NAME=="":
            testName = message.body['world'].split('.')[0]
        else:
            testName = settings.TEST_NAME
        self.testDescription = message.body['test_description']
        self.testName = message.body['test_name']
        self.arenaName = message.body['arena_name']
        self.testFolder = "ros_simulation/src/multiple_robots_stage/static_files_folder/ltl_test_examples/"+self.testName
        copyfile(self.testFolder+"/ltl_input", "ros_simulation/src/multiple_robots_stage/static_files_folder/ltl_input")
        
        
        self.sendRequest()
                
    def taskSentToExecution(self, message):
        self.testStatistics[self.testName]["sent_to_execution"] = datetime.datetime.now()
    
    def taskFinished(self, message):
        _log.info("task finished "+self.testName)
        print("task finished function!")
        cost = -1
        if message.body['outcome'] == 'success':
        
            srcFile = "ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraintsSaved.smt2"
            destFile = "ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraints"+repr(self.numberOfTasksFinished)+".smt2"
            os.rename(srcFile, destFile)
            
            srcFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_ltl_workspace.txt"
            destFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_ltl_workspace"+repr(self.numberOfTasksFinished)+".txt"
            os.rename(srcFile, destFile)
            
            srcFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_ltl_input"
            destFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_ltl_input"+repr(self.numberOfTasksFinished)
            os.rename(srcFile, destFile)
            
            srcFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_propositions_ltl_planner"
            destFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_propositions_ltl_planner"+repr(self.numberOfTasksFinished)
            os.rename(srcFile, destFile)
            
            srcFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_related_propositions_ltl_planner"
            destFile = "ros_simulation/src/multiple_robots_stage/static_files_folder/saved_related_propositions_ltl_planner"+repr(self.numberOfTasksFinished)
            os.rename(srcFile, destFile)
            
            print("constraint files renamed")
            z3OutputFile = "ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output"
            cost = 0
            
            setOfActiveRobots = set()
            
            with open("ros_simulation/src/multiple_robots_stage/static_files_folder/assignmentFile.txt") as assignment_f:
                for line in assignment_f:
                    setOfActiveRobots.add(int(line.strip()[0]))
            with open(z3OutputFile) as f:
                for line in f:
                    for idx in setOfActiveRobots:
                        keyString = "total_cost_"+str(idx+1) 
                        if keyString in line:
                            line = line.replace(keyString, "")
                            line = line.strip("()\n\t ")
                            totalCostContents = line.split()
                            if "/" in line:
                                cost +=  float(totalCostContents[1]) / float(totalCostContents[-1])
                            else:
                                
                                cost += float(totalCostContents[0])
                    
                    
        
        statsFile = "../staticFilesTesting/ltlResults"
        with open(statsFile, "a") as stat_f:
            stat_f.write("\t"+repr(cost))
        os.system("rostopic pub action_done std_msgs/Int32 1 --once")
        self.numberOfTasksFinished += 1
        if self.numberOfTasksFinished == self.totalNumberOfTasks:
            self.writeTheStats()
        else:
            self.sendRequest()
#        outcome = message.body['outcome']
#         if outcome == 'success':
#             testName = message.body['test_name']
#             self.requestsToFulfill.remove(testName)
#             print(testName+' finished -- removing from set!!!!!!!!!!!!!!----------------------!!!!!!!!!!!!!')
#             self.testStatistics[self.testName]["finished"] = datetime.datetime.now()
#             if len(self.requestsToFulfill) == 0:
#                     #pdb.set_trace()
#                     
#                     self.writeTheStats()
#                     return
#             else:
#                 self.sendRequest()
#         else:
#             
#             print('failure of scheduling, rescheduling in the queue!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
        
    def writeTheStats(self):
        
        #os.system("rostopic pub action_done std_msgs/Int32 1")
        print("the stats written, done with testing")
        
        return
    
    def sendRequest(self, message=None):
        #pdb.set_trace(
        testLocationsFilename = self.testFolder +"/"+self.arenaName+"/original_ltl_propositions" + repr(self.numberOfTasksFinished+1)
        copyfile(testLocationsFilename, "ros_simulation/src/multiple_robots_stage/static_files_folder/original_ltl_propositions")
        
        
        listOfRequests = []
        
            
        locationsToVisit = [Point([1,1])]
            
            
            #self.locationsIndex = self.locationsIndex + 1
        
        user = 'testGenerator'
        status = 'pending'
        new_task = Task(username=user, locations=locationsToVisit, status=status)
        try:
            self.session.add(new_task)
            self.session.commit()
            entry_id = new_task.id
            
            _log.debug("tester: -------------------------sending new request to scheduler")
            
            
            self.send_message(to=settings.SCHEDULER, directive="request",\
                                           body = {'locations':locationsToVisit, 'request_id':entry_id,'test_name':'def'})
            
             
        except Exception as e:
            self.session.rollback()
            _log.error("error saving task to database")
             
        
        
        
