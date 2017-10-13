%{
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generateconstraints_yacc.h"

using namespace std;

int yylex();
int yyerror(char *s);
char* findProposition(char *);
void declareVariable(FILE * , char * , char * );

struct s
{
  char x[10000];
  char y[10000];
};

typedef struct s prop_t;

typedef std::vector<prop_t> prop_vec_t;

FILE *ofp1, *ofp2;
char str[10000];
char str1[10000], str2[10000];
unsigned int variable_count = 1;
unsigned int bounded_operator_count = 1;
unsigned int until_count = 1;
unsigned int release_count = 1;
int loop_count;
int length;
prop_vec_t propositions;
int lower_limit, upper_limit;
int count1, count2, count3;
%}


%union{
  char s[10000];
}


%token <s> IDENTIFIER CONSTANT
%token <s> TRUE FALSE
%left <s> NEXT UNTIL RELEASE
%left <s> NOT OR AND
%token <s> '(' ')'

%type <s> formula main_formula constant_formula

%start formula

%%

formula
 	: main_formula
          {
          }
        ;


main_formula
	: IDENTIFIER
          {
            strcpy($$, $1);
          }
        | constant_formula
          {
            strcpy($$, $1);
          }
 	| '(' main_formula ')'
          {
            sprintf($$, "%s", $2);
          }
        | NOT main_formula
          {
            sprintf(str, "not %s", $2);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            } 
            printf("  == %s => %s\n", str, $$);

            for (loop_count = 1; loop_count <= length + 1; loop_count++)
            {
              if (strcmp($2, "true") == 0)
                strcpy(str1, "false");
              else if (strcmp($2, "false") == 0)
                strcpy(str1, "true");
              else
                sprintf(str1, "(= %s_%d false)", $2, loop_count);
              fprintf(ofp1, "(assert (=> %s_%d %s))\n", $$, loop_count, str1);
              fprintf(ofp1, "(assert (=> %s %s_%d))\n", str1, $$, loop_count);
            }
            fprintf(ofp1, "\n");
          }
	| main_formula AND main_formula
          {
            sprintf(str, "%s /\\ %s", $1, $3);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }
            printf("  == %s => %s\n", str, $$);

            for (loop_count = 1; loop_count <= length + 1; loop_count++)
            {
              if (strcmp($1, "true") == 0)
                strcpy(str1, "true");
              else if (strcmp($1, "false") == 0)
                strcpy(str1, "false");
              else
	        sprintf(str1, "%s_%d", $1, loop_count);
              if (strcmp($3, "true") == 0)
                strcpy(str2, "true");
              else if (strcmp($3, "false") == 0)
                strcpy(str2, "false");
              else
	        sprintf(str2, "%s_%d", $3, loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (and %s %s)))\n", $$, loop_count, str1, str2);
              fprintf(ofp1, "(assert (=> (and %s %s) %s_%d))\n", str1, str2, $$, loop_count);
            }
            fprintf(ofp1, "\n");
          }
	| main_formula OR main_formula
          {
            sprintf(str, "%s \\/ %s", $1, $3);
	    if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }  
            printf(" == %s => %s\n", str, $$);
            
            for (loop_count = 1; loop_count <= length + 1; loop_count++)
            {
              if (strcmp($1, "true") == 0)
                strcpy(str1, "true");
              else if (strcmp($1, "false") == 0)
                strcpy(str1, "false");
              else
                sprintf(str1, "%s_%d", $1, loop_count);
              if (strcmp($3, "true") == 0)
                strcpy(str2, "true");
              else if (strcmp($3, "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", $3, loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (or %s %s)))\n", $$, loop_count, str1, str2);
              fprintf(ofp1, "(assert (=> (or %s %s) %s_%d))\n", str1, str2, $$, loop_count);
            }
            fprintf(ofp1, "\n");
          }
   	| NEXT main_formula
          {
            sprintf(str, "X %s", $2);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }
            printf("  == %s => %s\n", str, $$);
           
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              fprintf(ofp1, "(assert (=> %s_%d %s_%d))\n", $$, loop_count, $2, loop_count + 1);
              fprintf(ofp1, "(assert (=> %s_%d %s_%d))\n", $2, loop_count + 1, $$, loop_count);
            }
            fprintf(ofp1, "\n");
          }
	| main_formula UNTIL main_formula
          {
            sprintf(str, "%s U %s", $1, $3);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }            
            printf("  == %s => %s\n", str, $$);
            
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              fprintf(ofp2, "(declare-const f_%d_%d Bool)\n", until_count, loop_count);
            }
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              if (strcmp($1, "true") == 0)
                strcpy(str1, "true");
              else if (strcmp($1, "false") == 0)
                strcpy(str1, "false");
              else
                sprintf(str1, "%s_%d", $1, loop_count);
              if (strcmp($3, "true") == 0)
                strcpy(str2, "true");
              else if (strcmp($3, "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", $3, loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (or %s (and %s %s_%d))))\n", $$, loop_count, str2, str1, $$, loop_count + 1);
              fprintf(ofp1, "(assert (=> (or %s (and %s %s_%d)) %s_%d))\n", str2, str1, $$, loop_count + 1, $$, loop_count);
            }           
            fprintf(ofp1, "\n");
            fprintf(ofp1, "(assert (= f_%d_1 false))\n", until_count);
            fprintf(ofp1, "(assert (=> loopexists (=> %s_%d f_%d_%d)))\n", $$, length, until_count, length);
            for(loop_count = 2; loop_count <= length; loop_count++)
            {
              fprintf(ofp1, "(assert (=> f_%d_%d (or f_%d_%d (and inloop_%d %s_%d))))\n", until_count, loop_count, until_count, loop_count - 1, loop_count, $3, loop_count);
              fprintf(ofp1, "(assert (=> (or f_%d_%d (and inloop_%d %s_%d)) f_%d_%d))\n", until_count, loop_count - 1, loop_count, $3, loop_count, until_count, loop_count);
            }  
            fprintf(ofp1, "\n");
            until_count = until_count + 1;
          }
      	| main_formula RELEASE main_formula
          {
            sprintf(str, "%s R %s", $1, $3);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }  
            printf("  == %s => %s\n", str, $$);
            
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              fprintf(ofp2, "(declare-const g_%d_%d Bool)\n", release_count, loop_count);
            }

            for (loop_count = 1; loop_count <= length; loop_count++)
            {
	      if (strcmp($1, "true") == 0)
                strcpy(str1, "true");
              else if (strcmp($1, "false") == 0)
                strcpy(str1, "false");
              else
                sprintf(str1, "%s_%d", $1, loop_count);
              if (strcmp($3, "true") == 0)
                strcpy(str2, "true");
              else if (strcmp($3, "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", $3, loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (and %s (or %s %s_%d))))\n", $$, loop_count, str2, str1, $$, loop_count + 1);
              fprintf(ofp1, "(assert (=> (and %s (or %s %s_%d)) %s_%d))\n", str2, str1, $$, loop_count + 1, $$, loop_count);
            }
            fprintf(ofp1, "\n");
            /*
            fprintf(ofp1, "(assert (= g_%d_1 true))\n", release_count);
            fprintf(ofp1, "(assert (=> loopexists (=> g_%d_%d %s_%d)))\n", release_count, length, $$, length);
            for(loop_count = 2; loop_count <= length; loop_count++)
            {
              fprintf(ofp1, "(assert (=> g_%d_%d (and g_%d_%d (or (not inloop_%d) %s_%d))))\n", release_count, loop_count, release_count, loop_count - 1, loop_count, $3, loop_count);
              fprintf(ofp1, "(assert (=> (and g_%d_%d (or (not inloop_%d) %s_%d)) g_%d_%d))\n", release_count, loop_count - 1, loop_count, $3, loop_count, release_count, loop_count);
            }  
            fprintf(ofp1, "\n");
            */
            release_count = release_count + 1;
          }
        | main_formula UNTIL '[' CONSTANT ',' CONSTANT ']' main_formula
          {
            lower_limit = atoi($4) + 1;
	    upper_limit = atoi($6) + 1;
            
            sprintf(str, "%s U[%s,%s] %s", $1, $4, $6, $8);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }
            printf("  == %s => %s\n", str, $$);
            
	    for (loop_count = 1; loop_count <= (upper_limit - lower_limit + 1); loop_count++)
            {
              sprintf(str1, "%s U[%d,%d] %s", $1, loop_count, (upper_limit - lower_limit + 1), $8);
              sprintf(str2, "q_%d_%d", bounded_operator_count, loop_count);
              declareVariable(ofp2, str1, str2);
            }
         
            for (loop_count = 1; loop_count <= length - lower_limit + 1; loop_count++)
            {
	      fprintf(ofp1, "(assert (=> %s_%d", $$, loop_count);
              fprintf(ofp1, " (and");
              for (count1 = loop_count; count1 < loop_count + lower_limit - 1; count1++)
              {
                if (strcmp($1, "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp($1, "false") == 0)
                  strcpy(str1, "false");
                else
                    sprintf(str1, "%s_%d", $1, count1);
                fprintf(ofp1, " %s", str1);
              }
              fprintf(ofp1, " q_%d_%d_%d)))\n", bounded_operator_count, upper_limit - lower_limit + 1, loop_count + lower_limit - 1);
              fprintf(ofp1, "(assert (=>");
              fprintf(ofp1, " (and");
              for (count1 = loop_count; count1 < loop_count + lower_limit - 1; count1++)
              {
                if (strcmp($1, "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp($1, "false") == 0)
                  strcpy(str1, "false");
                else
                    sprintf(str1, "%s_%d", $1, count1);
                fprintf(ofp1, " %s", str1);
              }
              fprintf(ofp1, " q_%d_%d_%d)", bounded_operator_count, upper_limit - lower_limit + 1, loop_count + lower_limit - 1);  
              fprintf(ofp1, " %s_%d))\n", $$, loop_count);
            }
            for(loop_count = length - lower_limit + 2; loop_count <= length; loop_count++)
            {
              if (loop_count > 0)
              {
                fprintf(ofp1, "(assert (= %s_%d false))\n", $$, loop_count);
              }
            }

	    for(loop_count = lower_limit; loop_count <= length - 1; loop_count++)
            {
              for (count1 = 1 ; count1 <= ((length - loop_count) <= (upper_limit - lower_limit) ? (length - loop_count) : (upper_limit - lower_limit)) ; count1++)
              {
                if (strcmp($1, "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp($1, "false") == 0)
                  strcpy(str1, "false");
                else
                  sprintf(str1, "%s_%d", $1, loop_count + count1 - 1);

                if (strcmp($8, "true") == 0)
                  strcpy(str2, "true");
                else if (strcmp($8, "false") == 0)
                  strcpy(str2, "false");
                else
                  sprintf(str2, "%s_%d", $8, loop_count + count1 - 1);
                fprintf(ofp1, "(assert (=> q_%d_%d_%d (or %s (and %s q_%d_%d_%d))))\n", bounded_operator_count, (upper_limit - lower_limit + 1) - (count1 - 1), loop_count + (count1 - 1), str2, str1, bounded_operator_count, (upper_limit - lower_limit + 1) - count1, loop_count + count1);
                fprintf(ofp1, "(assert (=> (or %s (and %s q_%d_%d_%d)) q_%d_%d_%d))\n", str2, str1, bounded_operator_count, (upper_limit - lower_limit + 1) - count1, loop_count + count1, bounded_operator_count, (upper_limit - lower_limit + 1) - (count1 - 1), loop_count + (count1 - 1));
              }
            }
           
            for (loop_count = upper_limit; loop_count <= length; loop_count++)
            {
	      if (strcmp($8, "true") == 0)
                strcpy(str2, "true");
              else if (strcmp($8, "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", $8, loop_count);
              fprintf(ofp1, "(assert (=> q_%d_1_%d %s))\n", bounded_operator_count, loop_count, str2);
              fprintf(ofp1, "(assert (=> %s q_%d_1_%d))\n", str2, bounded_operator_count, loop_count);
            }  

            if (strcmp($8, "true") == 0)
              strcpy(str2, "true");
            else if (strcmp($8, "false") == 0)
              strcpy(str2, "false");
            else
              sprintf(str2, "%s_%d", $8, length);
            for (loop_count = 2; loop_count <= (upper_limit - lower_limit + 1); loop_count++)
            {
              fprintf(ofp1, "(assert (=> q_%d_%d_%d %s))\n", bounded_operator_count, loop_count, length, str2);
              fprintf(ofp1, "(assert (=> %s q_%d_%d_%d))\n", str2, bounded_operator_count, loop_count, length);
            }

            bounded_operator_count++;
            fprintf(ofp1, "\n");
          }
        | main_formula RELEASE '[' CONSTANT ',' CONSTANT ']' main_formula
	  {
            lower_limit = atoi($4) + 1;
            upper_limit = atoi($6) + 1;
            sprintf(str, "%s R[%s,%s] %s", $1, $4, $6, $8);
            if (findProposition(str) == NULL)
            {
              sprintf($$, "p_%d", variable_count);
              declareVariable(ofp2, str, $$);
              variable_count++;
            }
            else
            {
              strcpy($$, findProposition(str));
            }
            printf("  == %s => %s\n", str, $$);
            
            for (loop_count = 1; loop_count <= (upper_limit - lower_limit + 1); loop_count++)
            {
              sprintf(str1, "%s R[%d,%d] %s", $1, loop_count, (upper_limit - lower_limit + 1), $8);
              sprintf(str2, "q_%d_%d", bounded_operator_count, loop_count);
              declareVariable(ofp2, str1, str2);
            }
            
            for (loop_count = 1; loop_count <= length - lower_limit + 1; loop_count++)
            {
              fprintf(ofp1, "(assert (=> %s_%d", $$, loop_count);
              fprintf(ofp1, " (or");
              for (count1 = loop_count; count1 < loop_count + lower_limit - 1; count1++)
              {
                if (strcmp($1, "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp($1, "false") == 0)
                  strcpy(str1, "false");
                else
                    sprintf(str1, "%s_%d", $1, count1);
                fprintf(ofp1, " %s", str1);
              }
              fprintf(ofp1, " q_%d_%d_%d)))\n", bounded_operator_count, upper_limit - lower_limit + 1, loop_count + lower_limit - 1);
              fprintf(ofp1, "(assert (=>");
              fprintf(ofp1, " (or");
              for (count1 = loop_count; count1 < loop_count + lower_limit - 1; count1++)
              {
                if (strcmp($1, "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp($1, "false") == 0)
                  strcpy(str1, "false");
                else
                  sprintf(str1, "%s_%d", $1, count1);
                fprintf(ofp1, " %s", str1);
              }
              fprintf(ofp1, " q_%d_%d_%d) ", bounded_operator_count, upper_limit - lower_limit + 1, loop_count + lower_limit - 1);
              fprintf(ofp1, "%s_%d))\n", $$, loop_count);
            }
            for(loop_count = length - lower_limit + 2; loop_count <= length; loop_count++)
            {
              if (loop_count > 0)
              {
                fprintf(ofp1, "(assert (=> %s_%d", $$, loop_count);
                fprintf(ofp1, " (or");
                for (count1 = loop_count; count1 <= length; count1++)
                {
                  if (strcmp($1, "true") == 0)
                    strcpy(str1, "true");
                  else if (strcmp($1, "false") == 0)
                    strcpy(str1, "false");
                  else
                    sprintf(str1, "%s_%d", $1, count1);
                  fprintf(ofp1, " %s", str1);
                }
                fprintf(ofp1, ")))\n");
                
                fprintf(ofp1, "(assert (=>");
                fprintf(ofp1, " (or");
                for (count1 = loop_count; count1 <= length; count1++)
                {
                  if (strcmp($1, "true") == 0)
                    strcpy(str1, "true");
                  else if (strcmp($1, "false") == 0)
                    strcpy(str1, "false");
                  else
                    sprintf(str1, "%s_%d", $1, count1);
                  fprintf(ofp1, " %s", str1);
                }
                fprintf(ofp1, ")");
                fprintf(ofp1, " %s_%d))\n", $$, loop_count);
              }
            }
            for(loop_count = lower_limit; loop_count <= length - 1; loop_count++)
            {
              for (count1 = 1 ; count1 <= ((length - loop_count) <= (upper_limit - lower_limit) ? (length - loop_count) : (upper_limit - lower_limit)) ; count1++)
              {
                if (strcmp($1, "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp($1, "false") == 0)
                  strcpy(str1, "false");
                else
                  sprintf(str1, "%s_%d", $1, loop_count + count1 - 1);
                if (strcmp($8, "true") == 0)
                  strcpy(str2, "true");
                else if (strcmp($8, "false") == 0)
                  strcpy(str2, "false");
                else
                  sprintf(str2, "%s_%d", $8, loop_count + count1 - 1);
                fprintf(ofp1, "(assert (=> q_%d_%d_%d (and %s (or %s q_%d_%d_%d))))\n", bounded_operator_count, (upper_limit - lower_limit + 1) - (count1 - 1), loop_count + (count1 - 1), str2, str1, bounded_operator_count, (upper_limit - lower_limit + 1) - count1, loop_count + count1);
                fprintf(ofp1, "(assert (=> (and %s (or %s q_%d_%d_%d)) q_%d_%d_%d))\n", str2, str1, bounded_operator_count, (upper_limit - lower_limit + 1) - count1, loop_count + count1, bounded_operator_count, (upper_limit - lower_limit + 1) - (count1 - 1), loop_count + (count1 - 1));
              }
            }
            for (loop_count = upper_limit; loop_count <= length; loop_count++)
            {
              if (strcmp($8, "true") == 0)
                strcpy(str2, "true");
              else if (strcmp($8, "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", $8, loop_count);
              fprintf(ofp1, "(assert (=> q_%d_1_%d %s))\n", bounded_operator_count, loop_count, str2);
              fprintf(ofp1, "(assert (=> %s q_%d_1_%d))\n", str2, bounded_operator_count, loop_count);
            }

            if (strcmp($8, "true") == 0)
              strcpy(str2, "true");
            else if (strcmp($8, "false") == 0)
              strcpy(str2, "false");
            else
              sprintf(str2, "%s_%d", $8, length);
            for (loop_count = 2; loop_count <= (upper_limit - lower_limit + 1); loop_count++)
            {
              fprintf(ofp1, "(assert (= q_%d_%d_%d false))\n", bounded_operator_count, loop_count, length);
            }
            bounded_operator_count++;
            fprintf(ofp1, "\n");
          }
        ;


constant_formula
	: TRUE 
          {
            strcpy($$, "true");
          }
	| FALSE
          {
            strcpy($$, "false");
          }
	;

%%



extern FILE* yyin;
extern char yytext[];
extern int column;


char* findProposition(char *str)
{
  unsigned int loop_count; 

  for(loop_count = 0; loop_count < propositions.size(); loop_count++)
  {
    if (strcmp(propositions[loop_count].x, str) == 0)
      return(propositions[loop_count].y);
  }
  return NULL;
}


void declareVariable(FILE *ofp, char *str1, char *str2)
{
  unsigned int loop_count;
  prop_t prop;

    strcpy(prop.x, str1);
    strcpy(prop.y, str2);
    propositions.push_back(prop);
    for (loop_count = 1; loop_count <= length + 1; loop_count++)
    {
      fprintf(ofp, "(declare-const %s_%d Bool)\n", str2, loop_count);
    }
}


void writeLastStateConstraints(FILE *ofp, unsigned int length, unsigned int variable_count)
{
  unsigned int count1, count2;
  
  for (count1 = 1; count1 < variable_count; count1++)
  {
    fprintf(ofp, "(assert (=> (not loopexists) (= p_%d_%d false)))\n", count1, length + 1);
  }
  fprintf(ofp, "\n");

  for (count1 = 1; count1 < variable_count; count1++)
  {
    for (count2 = 2; count2 <= length; count2++)
    {
      fprintf(ofp, "(assert (=> l_%d (= p_%d_%d p_%d_%d)))\n", count2, count1, length + 1, count1, count2);
    }
  }
  fprintf(ofp, "\n");
}


void writeInitialStateConstraint(FILE *ofp, unsigned int variable_count)
{
  fprintf(ofp, "(assert (= p_%d_1 true))\n", variable_count - 1); 
}


int main(int argc, char *argv[]) 
{
  if (argc != 3)
  {  
    printf("USAGE: ./parser <input file name> <length of the trajectory>");
    exit(0);
  }
  length = atoi(argv[2]);  
  
  ofp1 = fopen("ltlconstraints.txt", "w");
  ofp2 = fopen("ltlvariables.txt", "w");

  yyin = fopen(argv[1], "r");
  yyparse();
  writeLastStateConstraints(ofp1, length, variable_count);
  writeInitialStateConstraint(ofp1, variable_count);
 
  fclose(ofp1);
  fclose(ofp2);
}


int yyerror(char *s)
{
  printf("\n%*s\n%*s\n", column, "^", column, s);
  return 0;
}
