
CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g


LTLPARSER_DIR = ../ltlparser


OBJS_LTL = $(LTLPARSER_DIR)/generateloopconstraints.o
OBJS_Z3 = $(OBJS_LTL) primitive.o readinputs.o writeconstraints.o generatetrajectory.o definepropositions.o ltlmotionplanning.o


all: ltlparser tool_z3


tool_z3 : $(OBJS_Z3)
	$(CC) $(LFLAGS) $(OBJS_Z3) -o tool_z3


primitive.o : primitive.h primitive.cpp
	$(CC) $(CFLAGS) primitive.cpp

readinputs.o : primitive.h readinputs.h readinputs.cpp
	$(CC) $(CFLAGS) readinputs.cpp

writeconstraints.o : primitive.h readinputs.h $(LTLPARSER_DIR)/generateloopconstraints.h writeconstraints.h writeconstraints.cpp
	$(CC) $(CFLAGS) writeconstraints.cpp

generatetrajectory.o : primitive.h readinputs.h definepropositions.h generatetrajectory.cpp
	$(CC) $(CFLAGS) generatetrajectory.cpp

definepropositions.o : primitive.h readinputs.h definepropositions.h definepropositions.cpp
	$(CC) $(CFLAGS) definepropositions.cpp

ltlmotionplanning.o : primitive.h readinputs.h writeconstraints.h definepropositions.h ltlmotionplanning.cpp
	$(CC) $(CFLAGS) ltlmotionplanning.cpp


ltlparser:
	$(MAKE) -C $(LTLPARSER_DIR) generateloopconstraints.o


.PHONY: clean
clean : 
	rm -f *.o
	rm -f tool_*
	$(MAKE) -C $(LTLPARSER_DIR) clean 
