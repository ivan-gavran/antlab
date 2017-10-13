import pdb
from xudd.hive import Hive
from xudd.actor import Actor
from config import settings
#from hi_receiving_actor import HiReceivingActor
#from hi_sending_actor import HiSendingActor
from actorClasses.request_handler import RequestHandler
from actorClasses.scheduler import Scheduler
from actorClasses.swarm_keeper import SwarmKeeper

class CentralHive(object):
    def __init__(self):
        pass
    
    def setCommunicationInfrastructure(self):
        central_hive = Hive(hive_id = settings.HIVE_ID )
        request_handler = central_hive.create_actor(RequestHandler, id=settings.REQUEST_HANDLER)
        scheduler = central_hive.create_actor(Scheduler, id=settings.SCHEDULER)
        swarm_keeper = central_hive.create_actor(SwarmKeeper, id=settings.SWARM_KEEPER)
        

        central_hive.send_message(to=request_handler, directive="start")
        central_hive.send_message(to=scheduler, directive="start")
        central_hive.send_message(to=swarm_keeper, directive="start")

        central_hive.run()

        