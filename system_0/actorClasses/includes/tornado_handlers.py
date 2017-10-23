import tornado.web
import tornado
from tornado import gen
from config import settings
import pdb
import json
import psycopg2.extras
import asyncio
#from system_0.db.bots import Bots as bots_db
#from system_0.db.tasks import Tasks as tasks_db
import logging
from utils.tbot_json_encoder import TurtlesEncoder
from utils.pg_point_type import Point
from db import Task, TurtlebotAgent, Session
from tornado.web import asynchronous
print('importao')


logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger()   

# currently just a testing class, without usage
class Main(tornado.web.RequestHandler):
    
        
            
    
    def get(self):
        """
        request_handler_actor = self.application.settings['request_handler_actor']
        request_handler_actor.send_message(to=settings.SCHEDULER, directive="request")
        dict = {'cat':12}
        k = self.get_argument(name='offset', default=10)
        dict['offset'] = k
        self.write(dict)
        """
        self.write('<html><body>'
                   '<p>Reachability: </p>'
                   '<form id="task_form" action="/api/tasks" method="POST">'
                   '<input type="text" name="locations", placeholder=[[3,9]]>'
                   '<input type="text" name="user", value=turtle>'
                   '<input type="text" name="action", value=reach>'
                   '<input type="submit" value="Submit">'
                   '</form>'
                   '<p>LTL request: </p>'
                   '<form id="task_form" action="/api/ltl_tasks" method="POST">'
                    '<input type="text" name="formula", value=&lt&gt(loc1/\&lt&gt(loc2\/loc3))>'
                   '<input type="text" name="user", value=turtle>'
                   '<input type="text" name="locationValues", value=loc1:1,3;loc2:1,2;loc3:2,4>'
                   '<input type="text" name="sameRobotLocations", value=loc1,loc2>'
                   '<input type="submit" value="Submit">'
                   '</form>'
                   '</body></html>')
        
    def prepare(self):
        pass
    
    def on_finish(self):
        pass


class LTL_Tasks(tornado.web.RequestHandler):
    def __init__(self, application, request, **kwargs):
        _log.debug('ltl task init')
        super(LTL_Tasks, self).__init__(application, request, **kwargs)
        self.session = Session()
        self.request_handler_actor = self.application.settings['request_handler_actor']
        self.ltl_static_files_folder = settings.ROS_STATIC_FILES_FOLDER
    
    def __del__(self):
        self.session.close()
    # list all existing tasks
    

    # a method to cancel all currently active tasks
    def delete(self):
        _log.info("in delete method")
        self.request_handler_actor.send_message(to=settings.SWARM_KEEPER, directive="cancel_tasks")
    
    #post a new task - it will update a file containing ltl formula
    @asynchronous
    def post(self):
        
        formula = self.get_body_argument(name = "formula")
        with open(self.ltl_static_files_folder+"ltl_input", "w") as ltlInputFile:
            ltlInputFile.write(formula)
        
        user = self.get_body_argument(name='user')
        
        locationValues = self.get_body_argument(name="locationValues")
        listOfLocations = locationValues.split(";")
        listOfLocations = [s.replace(":"," ") for s in listOfLocations]
        listOfLocations = [s.replace(","," ") for s in listOfLocations]
        stringOfLocations = "\n".join(listOfLocations)
        with open(self.ltl_static_files_folder+"original_ltl_propositions", "w") as originalPropositionsFile:
            originalPropositionsFile.write(stringOfLocations)
            
        locationValues = self.get_body_argument(name="sameRobotLocations")
        listOfLocations = locationValues.split(";")
        listOfLocations = [s.replace(":"," ") for s in listOfLocations]
        listOfLocations = [s.replace(","," ") for s in listOfLocations]
        stringOfLocations = "\n".join(listOfLocations)
        with open(self.ltl_static_files_folder+"related_propositions_ltl_planner", "w") as originalPropositionsFile:
            originalPropositionsFile.write(stringOfLocations)
        
        
                
        
        #dummy locations: previous reachability architecture had this to track in a database all that was done
        locations = [[-1,-1]]
        locations = [Point(l) for l in locations]
        status = "pending"
        new_task = Task(username=user, locations=locations, status=status)
        try:
            self.session.add(new_task)
            self.session.commit()
            entry_id = new_task.id
            self.request_handler_actor.send_message(to=settings.SCHEDULER, directive="request",\
                                           body = {'locations':locations, 'request_id':entry_id})
            self.set_status(200)
            self.redirect('/')
        except Exception as e:
            self.session.rollback()
            self.set_status(400)
        

class Tasks(tornado.web.RequestHandler):
    def __init__(self, application, request, **kwargs):
        _log.debug('task init')
        super(Tasks, self).__init__(application, request, **kwargs)
        self.session = Session()
        self.request_handler_actor = self.application.settings['request_handler_actor']
    
    def __del__(self):
        self.session.close()
    # list all existing tasks
    def get(self):
        username = self.get_argument(name='username',default=None)
        query = self.session.query(Task)
        if username!=None:
            query = query.filter(Task.username==username)
            
        result = query.all()
        jsonResult = json.dumps(result, cls=TurtlesEncoder )
        self.write(jsonResult)

    # a method to cancel all currently active tasks
    def delete(self):
        _log.info("in delete method")
        self.request_handler_actor.send_message(to=settings.SWARM_KEEPER, directive="cancel_tasks")
    
    #post a new task (it consists of list of locations to visit (locations are lists as well)
    @asynchronous
    def post(self):
        action = self.get_body_argument(name='action')
        if action == 'cancel':
            self.request_handler_actor.send_message(to=settings.SWARM_KEEPER, directive="cancel_tasks")
            self.set_status(200)
            self.redirect('/')
        locations=json.loads(self.get_body_argument(name='locations'))
        if not isinstance(locations, list):
            self.set_status(400, 'list of locations needed')
            self.finish()
            return
        else:
            self.redirect('/')
            correct_location_format = [isinstance(location, list) and len(location)==2 for location in locations]
            if min(correct_location_format) == False:
                self.set_status(400, 'each location has to be a list of length 2')
                
                self.finish()
                return
        
        user = self.get_body_argument(name='user')
        status = 'pending'
        locations = [Point(l) for l in locations]
        new_task = Task(username=user, locations=locations, status=status)
        try:
            self.session.add(new_task)
            self.session.commit()
            entry_id = new_task.id
            self.request_handler_actor.send_message(to=settings.SCHEDULER, directive="request",\
                                           body = {'locations':locations, 'request_id':entry_id})
            self.set_status(200)
            self.redirect('/')
        except Exception as e:
            self.session.rollback()
            self.set_status(400)
        
        
        
class Admin(tornado.web.RequestHandler):
    def __init__(self, application, request, **kwargs):
        super(Admin, self).__init__(application, request, **kwargs)
        _log.debug('admin init')
        self.session = Session()
        self.request_handler_actor = self.application.settings['request_handler_actor']
    def __del__(self):
        self.session.close()
    # list existing bots
    def get(self):
        result = self.session.query(TurtlebotAgent).all()
        jsonResult = json.dumps(result, cls=TurtlesEncoder )
        self.write(jsonResult)
    # add a new bot with name and location
   
    def post(self):
        
        
        if settings.SIMULATION == True:
            initial_location = [settings.NEST_X, settings.NEST_Y]
            robots_in_database = self.session.query(TurtlebotAgent.name).all()
            if len(robots_in_database)==0:
                maximal_index = -1
            else:
                maximal_index = max([int(r[0].split('_')[1]) for r in robots_in_database])
            turtlebot_name = 'robot_'+repr(maximal_index+1)
            if maximal_index == settings.MAXIMAL_NUMBER_OF_BOTS - 1:
                self.set_status(204, "maximal number of bots already reached")
                self.finish()
        else:
            try:
                initial_location=json.loads(self.get_body_argument(name='location'))
            except:
                self.set_status(400)
                self.finish()
            else:
                turtlebot_name=self.get_body_argument(name='name')
                robots_with_same_name = self.session.query(TurtlebotAgent).filter_by(name=turtlebot_name).all()
                if len(robots_with_same_name) > 0:
                    self.set_status(400, "the turtlebot name must be unique")
                elif len(initial_location) != 2:
                    self.set_status(400, "the initial location must be a 2d vector")
                    self.finish()
        
        try:
            new_agent = TurtlebotAgent(name=turtlebot_name, location = Point(initial_location))
            self.session.add(new_agent)
            self.session.commit()
            
        except Exception as e:
            self.session.rollback()
            self.set_status(400, 'error writing in the database')
        
