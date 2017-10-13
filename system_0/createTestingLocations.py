from config import settings
import argparse
import re
from PIL import Image
import pdb
import json
import yaml
import os
import random
from utils.implanFormatConverter import pixelUnitsToMeters, metersToPixelUnits  

def assure_path_exists(path):
        dir = os.path.dirname(path)
        if not os.path.exists(dir):
                os.makedirs(dir)

def isPlaceOnMapFree(x, y, pixels, resolution, imageLength, imageWidth, safetyWindow = 1.0):
    (x_p, y_p) = metersToPixelUnits(x, y, resolution, imageWidth)
    safetyBelt = int(round(safetyWindow / resolution))
    print(x,y)
    for i in range(-safetyBelt, safetyBelt):
        for j in range(-safetyBelt, safetyBelt):
            x_coord = x_p + i 
            y_coord = y_p + j
            try:
                if x_coord < 0 or x_coord > imageLength or y_coord < 0 or y_coord > imageWidth or pixels[x_coord,y_coord] < 150:
                    try:
                        print(x_coord, y_coord, pixels[x_coord, y_coord])
                    except:
                        print(x_coord, y_coord)
                    return False
            except:
                print('index out!----------------------------------')
                print(x_coord, imageLength, y_coord, imageLength)
    return True

def createLocations():
        parser = argparse.ArgumentParser()
        parser.add_argument("--world_file", default="artificialFloorSmallestSize.world")
        parser.add_argument("--yaml_file", default="artificialFloorSmallestSize.yaml")
        parser.add_argument("--number_of_requests", default=10)
        parser.add_argument("--test_locations_filename", default="testLocations.json")
        parser.add_argument("--ltl_test_name", default="2placesPatrolling")
        arenas = ["artificialFloorSmallestSize", "artificialFloorSmallSize", "artificialFloorSmallInBetween"]
        
        args, unknown = parser.parse_known_args()
        
        
        numberOfRequests = int(args.number_of_requests)
        maps_directory = settings.MAP_FOLDER
        
        for i, _ in enumerate(arenas):
            world_file = arenas[i]+".world"
            world_file_path = maps_directory+"/worlds/"+world_file
            f_world = open(world_file_path, 'r')
            testName = world_file.split('.')[0]
            world_file_text = f_world.read()
            matches_pose = re.findall('turtlebot\n\(.*?pose \[ (.*?) \].*?\)', world_file_text, re.DOTALL)
            robots_positions = [ [float(c) for c in s.split(' ')] for s in matches_pose]
            settings.ROBOTS_LOCATIONS = robots_positions
            matches_map = re.findall('floorplan.*?bitmap \"..\/(.*?).pgm\"', world_file_text, re.DOTALL)
            if len(matches_map) == 1:
                map_image_file = matches_map[0]+'.pgm'
            else:
                raise "map not detected correctly"
            
            map_description_file = arenas[i] + ".yaml"
            
            f_yaml = open(maps_directory+'/'+map_description_file, 'r')
            map_description = yaml.load(f_yaml)
            f_yaml.close()
            
            im = Image.open(settings.MAP_FOLDER+'/'+map_image_file)
            pix = im.load()
            imageLength, imageWidth = im.size
            
            imageLengthMeters = map_description["resolution"] * imageLength
            imageWidthMeters = map_description["resolution"] * imageWidth
            #pdb.set_trace()
            requests = {}
            testCasesCounter = 0
            propositions = []
            with open(settings.ROS_STATIC_FILES_FOLDER+"ltl_test_examples/"+args.ltl_test_name+"/original_ltl_propositions") as f:
                for line in f:
                    propositions.append(line.strip())
                    
                
            while testCasesCounter < numberOfRequests:
                testCaseName = 'test_'+repr(testCasesCounter)
                numberOfLocations = len(propositions)
                print(testCasesCounter, numberOfLocations)
                locationsToVisit = []
                foundLocations = 0
                while foundLocations < numberOfLocations:
                    x_coordinate = random.uniform(0, imageLengthMeters)
                    y_coordinate = random.uniform(0, imageWidthMeters)
                    
                    if isPlaceOnMapFree(x = x_coordinate, y = y_coordinate, pixels = pix, imageLength = imageLength, imageWidth=imageWidth, resolution = map_description["resolution"], safetyWindow=1.0):
                        locationsToVisit.append([x_coordinate, y_coordinate])
                        foundLocations += 1
                        
                    else:
                        print('not free')
                        continue
                if len(locationsToVisit) > 0:
                    testCasesCounter = testCasesCounter + 1
                
                    requests[testCaseName] =list(locationsToVisit)
                    testCaseId = str(testCasesCounter)
                    
                    testFilename = "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/static_files_folder/ltl_test_examples/"+args.ltl_test_name+"/"+arenas[i]+"/original_ltl_propositions"+testCaseId
                    assure_path_exists(testFilename)
                 
                with open(testFilename, "w") as f_testLocations:
                   for idx, prop in enumerate(propositions):
                       f_testLocations.write(prop+" "+str(round(locationsToVisit[idx][0],2))+" "+str(round(locationsToVisit[idx][1],2))+"\n")
if __name__ == '__main__':
    createLocations()
