A simple system that contains web API, actor-based scheduler, swarm-keeper, task organizer and task executors.
In order to run it, it is necessary to add system_0 to PYTHONPATH (in order to use custom xudd, but also some imports are not done properly).
Afterwards, the simulation is run by
`roslaunch multiple_robots_stage robots_in_stage.launch`
(before that, it is necessary to make *ros\_simulation* a catkin workspace (by sourcing ros_simulation/devel/setup.bash)
The system is run by `python system_0/start.py`. Afterwards, the tasks are given by using web api
described in .postman_collection file.