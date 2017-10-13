import json
from datetime import datetime, date
from db import TurtlebotAgent, Task
class TurtlesEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, datetime):
            return str(obj)
        elif isinstance(obj, TurtlebotAgent):
            return {'name':obj.name, 'location':obj.location, 'available':obj.available }
        elif isinstance(obj, Task):
            return {'username':obj.username, 'status':obj.status, 'locations':obj.locations}
        return json.JSONEncoder.default(self, obj)
    
