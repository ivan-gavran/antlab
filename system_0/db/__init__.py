from config import settings
from sqlalchemy import create_engine
from sqlalchemy.ext.automap import automap_base
from sqlalchemy.orm import sessionmaker
#from utils.pg_point_type import Point, register_point_type, register_point_array_type
from utils.pg_point_type import Point, register_point_type

engine=create_engine('postgresql+psycopg2://'+settings.POSTGRE_USERNAME+':'\
                     +settings.POSTGRE_TOY_PASSWORD+'@'\
                     +settings.POSTGRE_HOST+':'\
                     +settings.POSTGRE_PORT+'/'\
                     +settings.POSTGRE_DB_NAME)
register_point_type(engine)

Base = automap_base()
Base.prepare(engine, reflect=True)

Task = Base.classes.tasks
TurtlebotAgent = Base.classes.turtlebot_agents
Session = sessionmaker(bind=engine)
print('db connection pool established!')