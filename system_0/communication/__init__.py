import pdb
import sys
from xudd.hive import Hive
from xudd.actor import Actor
from config import settings
from actorClasses.request_handler import RequestHandler
from actorClasses.scheduler import Scheduler
from actorClasses.swarm_keeper import SwarmKeeper
from actorClasses.task_generator import TaskGenerator
from actorClasses.tests_generator import TestsGenerator

 

print('communication') 


def startingActors(use_task_generator=False, performanceTesting=False):
    central_hive = Hive(hive_id = settings.HIVE_ID )
    request_handler = central_hive.create_actor(RequestHandler, id=settings.REQUEST_HANDLER)
    scheduler = central_hive.create_actor(Scheduler, id=settings.SCHEDULER)
    swarm_keeper = central_hive.create_actor(SwarmKeeper, id=settings.SWARM_KEEPER)
    if use_task_generator == True:
        task_generator = central_hive.create_actor(TaskGenerator, id='generator')
     
    
     
     
    central_hive.send_message(to=request_handler, directive="start")
    central_hive.send_message(to=scheduler, directive="start")
    central_hive.send_message(to=swarm_keeper, directive="start")
    
    if use_task_generator == True:
        central_hive.send_message(to=task_generator, directive="start")
    
    if performanceTesting == True:
        testingActor = central_hive.create_actor(TestsGenerator, id=settings.TESTS_GENERATOR)
        
        if settings.IMPLAN_ASSIGNMENT == True:
            testDescription = 'implanAssignment'
        elif settings.IMPLAN == True:
            testDescription = 'implan'
        else:
            testDescription = 'basePlan'
        testDescription = testDescription + settings.MULTI_PLANNER
        
        central_hive.send_message(to=testingActor, directive="start", body = {"world":settings.WORLD_FILE_NAME,\
                                                                               "test_description":testDescription, "test_name":settings.TEST_NAME,\
                                                                               "arena_name":settings.ARENA_NAME})
    
    central_hive.run()
    