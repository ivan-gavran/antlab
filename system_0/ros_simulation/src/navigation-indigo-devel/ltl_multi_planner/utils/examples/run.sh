#!/bin/bash


#cd ../src/ltlparser
#make
#cd ../../examples/
#echo "LTL parser made.."

#cd ../src/ltl
#make
#cd ../../examples/
#echo "Executable files made.."

#mv /home/ivan/antlab/system_0/ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/src/ltlparser/formula_simplifier .
#mv /home/ivan/antlab/system_0/ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/src/ltlparser/constraints_generator .
#mv /home/ivan/antlab/system_0/ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/tool_z3 .
echo "Executable files moved to the current directory.."

src/navigation-indigo-devel/ltl_multi_planner/utils/examples/tool_z3


#time z3 constraints.smt2

exit 0
