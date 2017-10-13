#!/bin/bash

cd ../src
make
cd ../examples
echo "Executable files made.."

mv ../src/tool_z3 .
echo "Executable files moved to the current directory.."

./tool_z3

exit 0
