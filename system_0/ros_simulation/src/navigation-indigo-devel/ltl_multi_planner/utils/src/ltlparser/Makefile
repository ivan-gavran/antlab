
CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall


all: formula_simplifier constraints_generator


formula_simplifier : simplifyformula_lex.c simplifyformula_yacc.c simplifyformula_yacc.h
	$(CC) simplifyformula_lex.c simplifyformula_yacc.c -o formula_simplifier

simplifyformula_lex.c : simplifyformula.l 
	lex simplifyformula.l
	mv lex.yy.c simplifyformula_lex.c

simplifyformula_yacc.c : simplifyformula.y
	yacc -d simplifyformula.y
	mv y.tab.c simplifyformula_yacc.c
	mv y.tab.h simplifyformula_yacc.h


constraints_generator : generateconstraints_lex.c generateconstraints_yacc.c generateconstraints_yacc.h
	$(CC) generateconstraints_lex.c generateconstraints_yacc.c -o constraints_generator

generateconstraints_lex.c : generateconstraints.l 
	lex generateconstraints.l
	mv lex.yy.c generateconstraints_lex.c

generateconstraints_yacc.c : generateconstraints.y
	yacc -d generateconstraints.y
	mv y.tab.c generateconstraints_yacc.c
	mv y.tab.h generateconstraints_yacc.h


generateloopconstraints.o : generateloopconstraints.h generateloopconstraints.cpp
	$(CC) $(CFLAGS) generateloopconstraints.cpp

.PHONY: clean
clean : 
	rm -f *.o
	rm -f formula_simplifier
	rm -f simplifyformula_lex.c
	rm -f simplifyformula_yacc.c
	rm -f simplifyformula_yacc.h
	rm -f constraints_generator
	rm -f generateconstraints_lex.c
	rm -f generateconstraints_yacc.c
	rm -f generateconstraints_yacc.h
	rm -f ltlconstraints.txt
	rm -f ltlvariables.txt
