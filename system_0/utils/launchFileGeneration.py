import argparse
import re
import pdb


def generateLaunchFile(world_file_name = "twoRobotsCropped.world", launch_file="ros_simulation/src/multiple_robots_stage/launch/generated.launch",\
                        implan=False, implan_assignments = False, robots_positions=[], map_file="", multiPlanner="", multiPlannerParams={}):
#     maps_directory = "ros_simulation/src/multiple_robots_stage/maps"
#     world_file = maps_directory+"/worlds/"+world_file_name
#     f_world = open(world_file, 'r')
#     world_file_text = f_world.read()
#     matches_pose = re.findall('turtlebot\n\(.*?pose \[ (.*?) \].*?\)', world_file_text, re.DOTALL)
#     robots_positions = [ [float(c) for c in s.split(' ')] for s in matches_pose]
#     
#     matches_map = re.findall('floorplan.*?bitmap \"..\/(.*?).pgm\"', world_file_text, re.DOTALL)
#     if len(matches_map) == 1:
#         map_file = matches_map[0]+'.yaml'
#     else:
#         raise "map not detected correctly"
#     
#     f_world.close()
    
    f_launch = open(launch_file, 'w')
    
    intro_string = '<launch>\n \
    <arg name="world_file" default="$(find multiple_robots_stage)/maps/worlds/'+world_file_name+'" />\n \
    <arg name="map_file" default="$(find multiple_robots_stage)/maps/'+map_file+'" />\n \
    <arg name="waypoints" default="0" /><arg name="robotName1" default="robot_0" />\n \
    <arg name="robotName2" default="robot_1" />\n \
    <arg name="robotName3" default="robot_2" />\n \
    <master auto="start" />\n \
    <param name="/use_sim_time" value="true" />\n \
    <node pkg="map_server" type="map_server" name="map_server" args="$(arg map_file)" respawn="false">\n \
    <param name="frame_id" value="/map" /></node>\n \
    <node pkg="stage_ros" type="stageros" name="stageros" args="$(arg world_file)" respawn="false">\n \
    <param name="base_watchdog_timeout" value="0.2" />\n \
    </node>\n'
    intro_string = intro_string + '<node pkg="multiple_robots_stage" type="collectAllTheDistances.py" name="distance_collector" output="screen">\n \
    <param name="number_of_robots" value = "'+repr(len(robots_positions))+'"/>\n</node>\n'
    if implan_assignments == True:
        intro_string = intro_string + '<node pkg="multi_global_planner" type="multi_global_planner" name="multi_global_planner" respawn="false" launch-prefix="xterm -e gdb -ex run --args">\n \
        <param name="multi_planner" value="'+multiPlanner+'"/>\n'
        for param in multiPlannerParams:
            intro_string = intro_string + '<param name="'+param+'" value="'+str(multiPlannerParams[param])+'"/>\n'
        intro_string=intro_string +'</node>\n'
    if implan == True:
        use_implan_string = "true"
    else:
        use_implan_string = "false"
    f_launch.write(intro_string)
    for idx, position in enumerate(robots_positions):
        robot_name = 'robot_'+str(idx)
        robot_specific_string = '<group ns="'+robot_name+'">\n \
        <param name="tf_prefix" value="'+robot_name+'"/> \n'+\
        '<include file="$(find multiple_robots_stage)/launch/client_robot.launch">\n \
            <arg name="robot_name" value="'+robot_name+'" />\n \
        </include>\n'+\
        '<include \
            file="$(find multiple_robots_stage)/launch/includes/single_robot.launch">\n \
            <arg name="namespace" value="'+robot_name+'" />\n \
            <arg name="initial_pose_x" value="'+str(position[0])+'" />\n \
            <arg name="initial_pose_y" value="'+str(position[1])+'" />\n \
            <arg name="initial_pose_a" value="0.0" />\n \
            <arg name="use_multirobot_planner" value="'+use_implan_string+'" />\n \
        </include>\n'+\
        '</group>'
        f_launch.write(robot_specific_string)
    
    f_launch.write('</launch>')
    f_launch.close()
        
        
    
    
