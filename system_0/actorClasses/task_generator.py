from xudd.actor import Actor
import logging
import pdb
from config import settings
import asyncio
from random import randint
from db import Task, TurtlebotAgent, Session
from utils.pg_point_type import Point
import time
logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger(__name__)   

class TaskGenerator(Actor):
    def __init__(self, hive, id):
        super(TaskGenerator, self).__init__(hive, id)
        self.session = Session()
        
        self.message_routing.update(
            {"start": self.startGeneratingTasks})

    def startGeneratingTasks(self, message):
        _log.debug("sleeping some time")
        some_locations = [[2,9], [3,10],[3,9],[3,11],[4,4], [4,1.5], [2.5,9], [4,10], [4,11]]
        number_of_locations = randint(1, 4)
        locations_to_visit = []
        for _ in range(number_of_locations):
            loc = randint(0,len(some_locations)-1)
            locations_to_visit.append(some_locations[loc])
        locations = locations_to_visit
            
        
        user = "generator"
        status = 'pending'
        locations = [Point(l) for l in locations]
        new_task = Task(username=user, locations=locations, status=status)
        try:
            self.session.add(new_task)
            self.session.commit()
            entry_id = new_task.id
            _log.debug("-------------------------sending new request")
            self.send_message(to=settings.SCHEDULER, directive="request",\
                                           body = {'locations':locations, 'request_id':entry_id})
            yield from asyncio.sleep(30)
            self.send_message(to="generator", directive="start")
            
        except Exception as e:
            self.session.rollback()
            self.set_status(400)
        
        
        