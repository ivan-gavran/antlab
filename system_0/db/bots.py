from system_0 import db_connection_pool
import psycopg2.extras, psycopg2
import logging

logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger()   

class Bots(object):
    @staticmethod
    def get(bot_id=None, available=[True, False]):
        available=list(available)
        con = db_connection_pool.getconn()
        cur = con.cursor()
        if bot_id==None:
            cur.execute('select * from turtlebot_agents where available in %s',(tuple(available),))
        else:
            cur.execute('select * from turtlebot_agents where available in %s and id=%s',(tuple(available), bot_id))
        
        result = cur.fetchall()
        db_connection_pool.putconn(con)
        return result
        
        
    @staticmethod        
    def insert(turtlebot_name, initial_location):
        con = db_connection_pool.getconn()
        cur = con.cursor()
        try:
            cur.execute('insert into turtlebot_agents (location, name) values (%s, %s) returning id',[initial_location, turtlebot_name])
            
        except Exception as e:
            _log.error(e)
            con.rollback()
            raise
        else:
            con.commit()
            entry_id = cur.fetchone()[0]
            return entry_id 
        finally:
            print('finally block')
            db_connection_pool.putconn(con)
    