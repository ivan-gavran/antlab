# antlab
Antlab is a multi-robot task server that accepts task specifications as LTL formulas, assigns task to set of robots, creates plans and executes requests.



## Setting up Antlab (tested on Ubuntu 14.04):

 _More detailed instructions - or a virtual machine with everything set up - coming soon_
 
 - [install](http://wiki.ros.org/indigo/Installation/Ubuntu) ROS Indigo
 - clone Antlab and make the ROS files with catkin_make
 - [set up](https://virtualenvwrapper.readthedocs.io/en/latest/) virtual environment for Python3
 - download modified XUDD library from https://github.com/gergia/xudd and add to your python3 path
 - install postgre database. setup username and password at will, but make sure to change the values in  antlab/system_0/config/settings.py accordingly
 - run files  antlab/system_0/db/dumps/tasks_create_script.sql and  antlab/system_0/db/dumps/turtlebot_agents_create_script.sql 
 - open a terminal and use python3 environment. run `python start.py --arena_name=emptyRectangleTiny --use_ltl_implan --use_implan --multi_planner=ltl_multi_planner::LtlMultiPlanner --only_file_generation`
 - open another terminal and run `roslaunch multiple_robots_stage generated.launch`
 -back to original terminal, run `(vdero3) ivan@wks-51-57:~/antlab-repo/system_0$ python start.py --arena_name=emptyRectangleTiny --use_ltl_implan --use_implan --multi_planner=ltl_multi_planner::LtlMultiPlanner`
 - open the address http://127.0.0.1:8888/ and use form for LTL request. Default request is given to illustrate usage of operators
