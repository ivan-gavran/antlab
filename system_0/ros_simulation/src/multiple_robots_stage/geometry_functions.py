from geometry_msgs.msg import Pose2D
import math

def plane_distance(point1, point2):
    return math.sqrt(math.pow(point1.x-point2.x, 2)+math.pow(point1.y-point2.y, 2))