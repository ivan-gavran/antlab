from system_0 import db_connection_pool
import psycopg2.extras, psycopg2
import logging
from system_0.config import settings
logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger()   

class Tasks(object):
    @staticmethod
    def get(id=None, status=settings.TASK_STATUS):
        status=list(status)
        con = db_connection_pool.getconn()
        cur = con.cursor()
        if id==None:
            cur.execute('select * from tasks where status in %s',(tuple(status),))
        else:
            cur.execute('select * from tasks where status in %s and id=%s',(tuple(status), id))
        
        con.commit()
        entry_id = cur.fetchone()[0]
        db_connection_pool.putconn(con)
        
    @staticmethod        
    def insert(locations, username='anonymous', status=settings.TASK_STATUS[0]):
        con = db_connection_pool.getconn()
        cur = con.cursor()
        try:
            cur.execute('insert into tasks (locations, username, status) values (%s, %s, %s) returning id',[locations, username, status])
            
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
    
    @staticmethod
    def update_status(id, status):
        con = db_connection_pool.getconn()
        cur = con.cursor()
        try:
            cur.execute('update tasks set status=%s where id=%s',[status, id])
            
        except Exception as e:
            _log.error(e)
            con.rollback()
            raise
        else:
            con.commit()
             
        finally:
            print('finally block')
            db_connection_pool.putconn(con)