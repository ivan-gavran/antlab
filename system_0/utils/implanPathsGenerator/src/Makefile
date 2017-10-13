CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall


OBJS_Z3 = primitive.o readinputs.o extractoutput.o writeconstraints.o concurrentassignmentandplanning.o jsoncpp.o


all: tool_z3


tool_z3 : $(OBJS_Z3)
	$(CC) $(LFLAGS) $(OBJS_Z3) -o tool_z3


jsoncpp.o: json/json.h json/json-forwards.h jsoncpp.cpp
	$(CC) $(CFLAGS) jsoncpp.cpp

primitive.o : primitive.h primitive.cpp
	$(CC) $(CFLAGS) primitive.cpp

readinputs.o : primitive.h readinputs.h readinputs.cpp
	$(CC) $(CFLAGS) readinputs.cpp

writeconstraints.o : primitive.h readinputs.h writeconstraints.h writeconstraints.cpp
	$(CC) $(CFLAGS) writeconstraints.cpp

generatetrajectory.o : primitive.h readinputs.h generatetrajectory.cpp
	$(CC) $(CFLAGS) generatetrajectory.cpp

extractOutput.o : extractoutput.h extractoutput.cpp
	$(CC) $(CFLAGS) extractoutput.cpp

concurrentassignmentandplanning.o : primitive.h readinputs.h extractoutput.o writeconstraints.o jsoncpp.o concurrentassignmentandplanning.cpp
	$(CC) -std=c++11 $(CFLAGS) concurrentassignmentandplanning.cpp



.PHONY: clean
clean :
	rm -f *.o
	rm -f tool_*
