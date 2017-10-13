import random
import pdb
from config import settings
import os
import json

x_max = 32
y_max = 30
def isAllowed(x, y):
    allowedSpaces = [ ([1,31], [14.5, 17]), ([14.5, 17],[1,29]) ]
    if (x > allowedSpaces[0][0][0] and x < allowedSpaces[0][0][1] and y > allowedSpaces[0][1][0] and y < allowedSpaces[0][1][1])\
    or ( x > allowedSpaces[1][0][0] and x < allowedSpaces[1][0][1] and y > allowedSpaces[1][1][0] and y < allowedSpaces[1][1][1] ):
        return True
    else:
        return False
def createLocations():
    maxNumberOfRequests = 10
    currentNumberOfRequests = 0
    areas = [ \
             [ [1, 14],[15, 16.5] ],\
             [ [18.5, 30], [14.5, 16.5] ], \
             [ [15, 16.5],[1,13] ],\
             [ [15, 16.5],[19, 29] ]
              ]
    requests = []
    while currentNumberOfRequests < maxNumberOfRequests:
        areaToChooseFrom = areas[currentNumberOfRequests % len(areas)]
        location_x = random.uniform(areaToChooseFrom[0][0], areaToChooseFrom[0][1])
        location_y = random.uniform(areaToChooseFrom[1][0], areaToChooseFrom[1][1])
        requests.append([location_x, location_y])
        requests.append([16,16])
        currentNumberOfRequests += 1
    testFilename = settings.TESTING_STATIC_FILES_FOLDER+'corridor'+'/'+'testLocations.json'
    os.makedirs(os.path.dirname(testFilename), exist_ok = True)
    with open(testFilename, "w") as f_testLocations:
        
        jsonToDump = {"locations":{'test_0':requests}}
        json.dump(jsonToDump, f_testLocations)
    print('done')

if __name__ == '__main__':
    createLocations()
