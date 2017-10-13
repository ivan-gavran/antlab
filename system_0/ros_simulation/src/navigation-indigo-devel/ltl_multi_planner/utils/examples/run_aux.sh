#!/bin/bash

cd ../src/ltlparser
make
cd ../../examples/
echo "LTL parser made.."

cd ../src/ltl
make
cd ../../examples/
echo "Executable files made.."

mv ../src/ltlparser/formula_simplifier .
mv ../src/ltlparser/constraints_generator .
mv ../src/ltl/tool_z3 .
echo "Executable files moved to the current directory.."


#time z3 constraints.smt2

exit 0
