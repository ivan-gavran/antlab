import re
import pdb
import sqlalchemy
import psycopg2
from psycopg2.extensions import adapt, register_adapter, AsIs
import math


class Point():
    def __init__(self, point):
        try:
            self.x = point.x
            self.y = point.y
        except:
            self.x = point[0]
            self.y = point[1]
    
    def __hash__(self):
        return hash((self.x, self.y))
    
    def __eq__(self, other):
        try:
            return self.x == other.x and self.y == other.y
        except:
            return self.x == other[0] and self.y == other[1]
    def __repr__(self):
        return "%s %s" % (self.x, self.y)
    @classmethod    
    def from_coordinates(cls,x,y):
        return cls([x,y])
    
    @classmethod
    def distance(cls, a, b):
        return math.sqrt((a.x-b.x)**2 + (a.y-b.y)**2)
    


def adapt_point(point): 
    return AsIs("'(%s, %s)'::point" % (adapt(point.x), adapt(point.y)))


def cast_point(value, cur):
    if value is None:
        return None

    # Convert from (f1, f2) syntax using a regular expression.
    m = re.match(r"\(([^)]+),([^)]+)\)", value)
    if m:
        return Point.from_coordinates(float(m.group(1)), float(m.group(2)))
    else:
        raise psycopg2.InterfaceError("bad point representation: %r" % value)


def register_point_type(engine):
    register_adapter(Point, adapt_point)
    rs = engine.execute("SELECT NULL::point")
    point_oid = rs.cursor.description[0][1]
    POINT = psycopg2.extensions.new_type((point_oid,), "POINT", cast_point)
    psycopg2.extensions.register_type(POINT)
    point_array_rs =  engine.execute("SELECT NULL::point[]")
    point_array_oid = point_array_rs.cursor.description[0][1]
    POINT_ARRAY=psycopg2.extensions.new_array_type( (point_array_oid,), "point[]", POINT )
    psycopg2.extensions.register_type(POINT_ARRAY)


