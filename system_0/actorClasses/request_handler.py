from xudd.actor import Actor
import logging
import pdb
from tornado import autoreload

logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger(__name__)   
from tornado.platform.asyncio import AsyncIOMainLoop
import asyncio 
import tornado.ioloop
from actorClasses.includes import tornado_handlers
import tornado.web
from config import settings
   


class RequestHandler(Actor):
    
    def __init__(self, hive, id):
        super(RequestHandler, self).__init__(hive, id)
        
        
        
        self.message_routing.update(
                {"start": self.startServing,
                 "request":self.request_received})
        
    
    
    def request_received(self):
        print('hi, request')
    
    def make_app(self):
        return tornado.web.Application(request_handler_actor=self, handlers=[
            (r"/", tornado_handlers.Main),
            (r"/api/tasks", tornado_handlers.Tasks),
            (r"/admin/bots", tornado_handlers.Admin),
            (r"/api/ltl_tasks", tornado_handlers.LTL_Tasks),
            
        ], autoreload=True, login_url="/auth/login")
        
    def startServing(self, message):
        _log.info(self.id+' started serving! :)')
        AsyncIOMainLoop().install()
        app = self.make_app()
        app.listen(8888)


    
        
    