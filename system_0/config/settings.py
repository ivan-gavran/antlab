import json

POSTGRE_DB_NAME='turtles'
POSTGRE_USERNAME = 'gavran'
POSTGRE_HOST='localhost'
POSTGRE_PORT='5432'
POSTGRE_TOY_PASSWORD = 'brhd2zz092'

cnf_json_location = 'config/cnf.json'
HIVE_ID='central_communication_hive'
REQUEST_HANDLER='request_handler'
SCHEDULER='scheduler'
SWARM_KEEPER='swarm_keeper'
TESTS_GENERATOR = 'testGenerator'
ROS_SIMULATION_ADMIN='ros_simulation_admin'
TASK_STATUS=['pending', 'scheduled', 'executing', 'finished']

SIMULATION = True
MAXIMAL_NUMBER_OF_BOTS = 10
MAXIMAL_PRIORITY_NUMBER = 10
MINIMAL_DISTANCE_TO_ANOTHER_ROBOT = 0.3
WORLD_FILE = 'ros_simulation/src/multiple_robots_stage/maps/worlds/twoRobots.world'
MAP_FOLDER="ros_simulation/src/multiple_robots_stage/maps"
IMPLAN_NAVIGATION = False
IMPLAN_ASSIGNMENT = False
IMPLAN_MAP_LENGTH = None
IMPLAN_MAP_WIDTH = None

ROS_STATIC_FILES_FOLDER = 'ros_simulation/src/multiple_robots_stage/static_files_folder/'
TESTING_STATIC_FILES_FOLDER='staticFilesTesting/'
TESTING_LOCATIONS='performanceTesting.json'
PREFERRED_UNIT_SIZE = 0.4