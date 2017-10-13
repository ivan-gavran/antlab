from xudd.actor import Actor
import logging
import pdb
import communication
from config import settings
logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger(__name__)   

# currently scheduler only forwards the messages without actually scheduling anything
class Scheduler(Actor):
    def __init__(self, hive, id):
        super(Scheduler, self).__init__(hive, id)
        
        self.message_routing.update(
            {"start": self.startServing,\
             "request":self.scheduleTheRequest})

        
    def startServing(self, message):
        _log.info(self.id+' started serving')
        
    def scheduleTheRequest(self, message):
        _log.info('SCHEDULER:request arrived')
        self.send_message(to=settings.SWARM_KEEPER, directive='organize_task', body=message.body)