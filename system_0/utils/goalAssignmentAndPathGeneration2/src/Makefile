CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall


OBJS_Z3 = utils.o primitive.o readinputs.o extractoutput.o writetrajectoryconstraints.o generateoptimaltrajectories.o writeassignmentconstraints.o generateoptimalassignment.o concurrentassignmentandplanning.o


all: tool_z3


tool_z3 : $(OBJS_Z3)
	$(CC) $(LFLAGS) $(OBJS_Z3) -o tool_z3


utils.o : utils.h
	$(CC) $(CFLAGS) utils.cpp

primitive.o : primitive.h primitive.cpp
	$(CC) $(CFLAGS) primitive.cpp

readinputs.o : primitive.h readinputs.h readinputs.cpp
	$(CC) $(CFLAGS) readinputs.cpp

writetrajectoryconstraints.o : utils.h  primitive.h readinputs.h writetrajectoryconstraints.h writetrajectoryconstraints.cpp
	$(CC) $(CFLAGS) writetrajectoryconstraints.cpp

generateoptimaltrajectories.o : primitive.h readinputs.h writetrajectoryconstraints.h extractoutput.h generateoptimaltrajectories.cpp
	$(CC) $(CFLAGS) generateoptimaltrajectories.cpp

writeassignmentconstraints.o : utils.h primitive.h readinputs.h writeassignmentconstraints.h writeassignmentconstraints.cpp
	$(CC) $(CFLAGS) writeassignmentconstraints.cpp

generateoptimalassignment.o : generateoptimalassignment.h generateoptimalassignment.cpp
	$(CC) $(CFLAGS) generateoptimalassignment.cpp
	
extractOutput.o : extractoutput.h extractoutput.cpp
	$(CC) $(CFLAGS) extractoutput.cpp

concurrentassignmentandplanning.o : primitive.h readinputs.h extractoutput.h generateoptimaltrajectories.h generateoptimalassignment.o concurrentassignmentandplanning.cpp
	$(CC) $(CFLAGS) concurrentassignmentandplanning.cpp



.PHONY: clean
clean :
	rm -f *.o
	rm -f tool_*
