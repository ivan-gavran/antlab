from __future__ import print_function
from PIL import Image, ImageFilter
import argparse
import os
import pdb
import math
import csv
from config import settings
from utils.implanFormatConverter import gridUnitsToMeters, metersToGridUnits

# the assumption is that dynamic obstacles is supplied in implan units already
def generateMap(scale=8, imageFile="twoRoomsCropped.pgm",\
                obstacleFile="obstacle.txt",\
                dimensionFile="dimension.txt",\
                map_folder = settings.MAP_FOLDER,\
                static_files_folder = settings.ROS_STATIC_FILES_FOLDER,\
                protectionZone=None,\
                dynamicObstaclesOriginalFile ="original_always_eventually_obstacles.txt",\
                dynamicObstaclesFile="dynamic_obstacles_always_eventually.txt"):
                
    #Read image
    
    if dimensionFile == None:
        dimensionFile = "obstacle.txt"
    if obstacleFile == None:
        obstacleFile="obstacle.txt"
    im = Image.open(map_folder+'/'+imageFile)
    pix = im.load()
    (x1, y1, x2, y2) = im.getbbox() 
    print("x1 = %d  y1 = %d    x2 = %d  y2 = %d" % (x1, y1, x2, y2))
    length = int(x2 / scale) #- 1
    width = int(y2 / scale) #- 1 
    
    settings.IMPLAN_MAP_LENGTH = length
    settings.IMPLAN_MAP_WIDTH = width
    print("length = %d  width = %d" % (length, width))
    fo = open(static_files_folder+dimensionFile, "w")
    fo.write("%d\n" % length)
    fo.write("%d" % width)
    fo.close()
    
    img = Image.new( 'RGB', (x2,y2), "white") # create a new black image
    pixels = img.load() # create the pixel map
    
    fo = open(static_files_folder+obstacleFile, "w")
    obstacleFieldsSet = set()
    if protectionZone == None:
        protectionZone = math.ceil(0.4 / settings.IMPLAN_UNIT_SIZE)
    print("protection zone " + str(protectionZone))
    for count1 in range(0, length):
        obstacleFieldsSet.add((count1, width))
        obstacleFieldsSet.add((count1, 0))
        #obstacleFieldsSet.add((count1, 1))
    for count2 in range(0, width):
        obstacleFieldsSet.add((length, count2))
        obstacleFieldsSet.add((0, count2))
        #obstacleFieldsSet.add((1, count2))
    for count1 in range(0, length):
       for count2 in range(0, width):
           pixels[count1*scale + scale,count2 *scale + scale] = 100
           obstacle_flag = 0;
           for x in range (count1*scale, count1*scale + scale):
               for y in range (count2*scale, count2*scale + scale):
                   occ = (255 - pix[x,y]) / 255.0
                   #fo.write("%f\n" % occ) 
                   if occ > 0.197:
                   #if occ > 0.75:
                       obstacle_flag = 1
        
           if obstacle_flag == 1:
               #fo.write("%d %d\n" % (count1, count2))
               obstacleFieldsSet.add((count1, count2))
               for i in range(-protectionZone, protectionZone):
                   for j in range(-protectionZone, protectionZone):
                       obstacleFieldsSet.add( (min(max(count1+i, 0), length), min(max(count2+j,0), width)))
               
    for gridPoint in sorted(obstacleFieldsSet):
        fo.write("%d %d\n" %gridPoint)
        count1 = gridPoint[0]
        count2 = gridPoint[1]
        for x in range (count1*scale, count1*scale + scale):
            for y in range (count2*scale, count2*scale + scale):
                try:
                    pixels[x, y] = 255
                except:
                    pass
    fo.close()
    
    fdo = open(static_files_folder+dynamicObstaclesFile, "w")    
    dynamicObstacles = {'boxDiamond':[]}
    with open(static_files_folder+dynamicObstaclesOriginalFile) as csvfile:
        dynObstaclesReader = csv.reader(csvfile, delimiter=',')
        for row in dynObstaclesReader:
            xStart = int(row[0])
            xEnd = int(row[1])
            yStart = int(row[2])
            yEnd = int(row[3])
            cost = int(row[4])
            
            (xGridStart, yGridStart) = metersToGridUnits(xStart, yStart)
            (xGridEnd, yGridEnd) = metersToGridUnits(xEnd, yEnd)
            if xGridStart > xGridEnd:
                xGridStart, xGridEnd = xGridEnd, xGridStart
            if yGridStart > yGridEnd:
                yGridStart, yGridEnd = yGridEnd, yGridStart
            for x in range(xGridStart, xGridEnd+1):
                for y in range(yGridStart, yGridEnd+1):
                    dynamicObstacles['boxDiamond'].append((x, y, cost))        
    # show dynamic obstacles in green color
    for dynObsPoint in dynamicObstacles['boxDiamond']:
        
        count1 = dynObsPoint[0]
        count2 = dynObsPoint[1]
        cost = dynObsPoint[2]
        fdo.write("%d %d %d \n" % (count1, count2, cost))
        
        
        for x in range (count1*scale, count1*scale + scale):
            for y in range (count2*scale, count2*scale + scale):
                try:
                    pixels[x, y] = (1,250,200)
                except Exception as e:
                    pass
                    
        
    fdo.close()    
    #img.show()
    return (length, width)

