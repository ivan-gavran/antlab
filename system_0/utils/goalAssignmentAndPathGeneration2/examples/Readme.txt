INPUT FILES

2d_template.txt
The file contains the motion primitives for the robots.
We assume that we have a homogeneous set of robots that
share the same set of motion primitives.

dimension.txt
The file contains the dimension of the workspace.

obstacle.txt
This file contains the location of the obstacles in the
workspace.

initpos.txt
This file contains the initial locations of the robots
available for this round.

finalpos.txt
This file contains the location of the destinations of
the robots.



HOW TO RUN THE PROGRAM

The motion planning tool relies on the SMT solver Z3.
Download Z3 from the following website, install it and 
keep it in the system path.

https://github.com/Z3Prover/z3

To run the program, type the following in the command 
prompt in the examples directory:

./run.sh

The output trajectories will be stored in the files
planner_output_1, ... , planner_output_N, where N is
the number of destination locations that the robots 
have to visit.


