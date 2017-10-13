#import system_0

from config import settings
from utils.pg_point_type import Point
from db import Session, TurtlebotAgent
import logging
import pdb
import re
import argparse
from utils.launchFileGeneration import generateLaunchFile
from utils.mapTransformation import generateMap


logging.basicConfig(level=logging.DEBUG)
_log = logging.getLogger()   
import json
import communication
import yaml
import csv
from PIL import Image


def initialize_system():
    parser = argparse.ArgumentParser()
    parser.add_argument("--arena_name", dest='arenaName', default="twoRoomsCropped", help="name of the arena. there should exist .yaml and .world files of the same name ")
    parser.add_argument("--world_file", dest='worldFile', default="", help="this should be used if the .world file should be different than arena.world")
    parser.add_argument("--yaml_file", dest='yamlFile', default="", help="this should be used if the .yaml file should be different than arena.yaml")
    parser.add_argument("--use_implan", dest='implan', action='store_true')
    parser.add_argument("--use_ltl_implan", dest='ltl_implan', action='store_true')
    parser.add_argument("--use_implan_assignment", dest='implan_assignment', action='store_true', default=False)
    parser.add_argument("--only_file_generation", dest='only_file_generation', action='store_true', default=False)
    parser.add_argument("--use_task_generator", dest='use_task_generator', action='store_true', default=False)
    parser.add_argument("--implan_scale_factor", dest="implan_scale_factor",\
                         help="to what scale implan might reduce the map for performance reasons", default=None)
    parser.add_argument("--run_test", dest="performanceTesting", action="store_true", default=False)
    parser.add_argument("--test_name", dest="testName", default="maze")
    parser.add_argument("--multi_planner", dest='multiPlanner', default="vanilla")
    
    parser.add_argument("--path_cost_tolerance", dest='pathCostTolerance', default=1)
    parser.add_argument("--planning_patience", dest='planningPatienceInSeconds', default=235)
    parser.add_argument("--final_optimization", dest='finalOptimization', action="store_true", default=False)
    parser.add_argument("--primitives_file", dest='primitivesFile', default="primitive_movements_manhattan.txt")
    parser.add_argument("--always_eventually_file", dest='alwaysEventuallyFile', default='original_always_eventually_obstacles.txt')
    parser.set_defaults(implan=False)
    args, unknown = parser.parse_known_args()
    arenaName = args.arenaName
    settings.ARENA_NAME=arenaName
    
    settings.MULTI_PLANNER = args.multiPlanner
    if args.worldFile != "":
        world_file = args.worldFile
    else:
        world_file = arenaName+'.world' 
    settings.WORLD_FILE_NAME = world_file
    print(args.implan, args.implan_assignment)
    performanceTesting = args.performanceTesting
    implan = args.implan
    ltl_implan = args.ltl_implan
    if ltl_implan == True:
        implan = True
    settings.IMPLAN= implan
    settings.LTL_IMPLAN = ltl_implan
    implan_assignment = args.implan_assignment
    if implan == True:
        implan_assignment = True
    only_file_generation = args.only_file_generation
    
        
    maps_directory = settings.MAP_FOLDER
    world_file_path = maps_directory+"/worlds/"+world_file
    f_world = open(world_file_path, 'r')
    world_file_text = f_world.read()
    matches_pose = re.findall('turtlebot\n\(.*?pose \[ (.*?) \].*?\)', world_file_text, re.DOTALL)
    robots_positions = [ [float(c) for c in s.split(' ')] for s in matches_pose]
    settings.NUMBER_OF_ROBOTS = len(robots_positions)
    settings.ROBOTS_LOCATIONS = robots_positions
    matches_map = re.findall('floorplan.*?bitmap \"..\/(.*?).pgm\"', world_file_text, re.DOTALL)
    if len(matches_map) == 1:
        map_image_file = matches_map[0]+'.pgm'
    else:
        raise "map not detected correctly"
    if args.yamlFile != "":
        map_description_file = args.yamlFile
    else:
        map_description_file = arenaName+'.yaml'
    f_world.close()
    
    settings.TEST_NAME = args.testName
        
    
    f_yaml = open(maps_directory+'/'+map_description_file, 'r')
    map_description = yaml.load(f_yaml)
    f_yaml.close()
    #generate launch file

    
    generateLaunchFile(world_file_name=world_file, map_file = map_description_file, robots_positions=robots_positions,\
                        implan=args.implan, implan_assignments = implan_assignment, multiPlanner=settings.MULTI_PLANNER, multiPlannerParams={"ant_multi_planner/path_cost_tolerance":int(args.pathCostTolerance),\
                                                                                                "ant_multi_planner/planning_patience":int(args.planningPatienceInSeconds),\
                                                                                                 "ant_multi_planner/final_optimization":args.finalOptimization,\
                                                                                                 "ant_multi_planner/primitives":args.primitivesFile})
    
    session = Session()
    f_world = open(settings.MAP_FOLDER+'/worlds/'+world_file)
    world_file_text = f_world.read()
    
    matches_pose = re.findall('turtlebot\n\(.*?pose \[ (.*?) \].*?\)', world_file_text, re.DOTALL)
    robots_positions = [ [float(c) for c in s.split(' ')] for s in matches_pose]
    try:
        session.query(TurtlebotAgent).delete()
        for idx, position in enumerate(robots_positions):
            initial_location = [position[0], position[1]]
            new_agent = TurtlebotAgent(name="robot_"+str(idx), location = Point(initial_location)) 
            session.add(new_agent)
        session.commit()
    except Exception as e:
        session.rollback()
        _log.error("problem writing to db")
        _log.error(e)
    session.close() 
    
    
    recommendedImplanScale = round(settings.PREFERRED_UNIT_SIZE / map_description["resolution"])
    if args.implan_scale_factor != None:
        implan_scale_factor = int(args.implan_scale_factor)
    else:
        implan_scale_factor = recommendedImplanScale
    settings.PERFORMANCE_TESTING = performanceTesting
    settings.IMPLAN_ASSIGNMENT = implan_assignment
    settings.IMPLAN_UNIT_SIZE = implan_scale_factor * map_description["resolution"]
    shared_cnf_json_file = open(settings.cnf_json_location, "w")
    cnf_json = {}
    #shared_cnf_json_file.seek(0)
    if implan == True:
        cnf_json["implan"] = 1
    else:
        cnf_json["implan"] = 0
    if implan_assignment == True:
        cnf_json["implan_assignment"] = 1
    else:
        cnf_json["implan_assignment"] = 0
    cnf_json["map_scale"] = implan_scale_factor
    obstacle_file = None
    dimension_file = None
    if ltl_implan == True:
        obstacle_file = "ltl_obstacle.txt"
        dimension_file = "ltl_dimension.txt"
            
        
    if implan_assignment == True or implan == True:
        settings.IMPLAN_UNIT_SIZE = implan_scale_factor * map_description['resolution']
    
        
        (l, w) = generateMap(imageFile=map_image_file, scale=implan_scale_factor, dynamicObstaclesOriginalFile=args.alwaysEventuallyFile, protectionZone=1,\
                             obstacleFile=obstacle_file, dimensionFile = dimension_file)
        
        cnf_json["map_width"] = w
        cnf_json["map_length"] = l
        cnf_json["resolution"] = map_description["resolution"]
        
         
#     if ltl_implan == True:
#         with open(settings.ROS_STATIC_FILES_FOLDER+"ltl_workspace.txt", "w") as workspaceFile:
#             workspaceFile.write("%d\n", cnf_json["map_width"])
#             workspaceFile.write("%d\n", cnf_json["map_height"])
#             workspaceFile.write("%d\n", len(robots_positions))
    json.dump(cnf_json, shared_cnf_json_file)
    shared_cnf_json_file.close()
    
    im = Image.open(settings.MAP_FOLDER+'/'+map_image_file)
    imageWidth, imageHeight = im.size
    
    settings.MAP_WIDTH_METERS = map_description["resolution"] * imageWidth
    settings.MAP_HEIGHT_METERS = map_description["resolution"] * imageHeight
    
    if recommendedImplanScale != implan_scale_factor:
        print("warning: recommended implan scale factor is %f, but factor %f is given "%(recommendedImplanScale, implan_scale_factor)) 
    else:
        print("implan scale as recommended: %f" % implan_scale_factor)
        
    
    
    
    print('finish')
    if only_file_generation == False:
        
        communication.startingActors(use_task_generator = args.use_task_generator, performanceTesting=performanceTesting)
    



    

if __name__ == '__main__':
    initialize_system()
    
