%{
#include <stdio.h>
#include <string.h>

int yyerror(char * );
int yylex();

char str[10000], str1[10000], str2[10000];
FILE *OFP;

%}

%union{
  char s[10000];
}


%token <s> IDENTIFIER CONSTANT
%token <s> TRUE FALSE
%left <s> ALWAYS EVENTUALLY UNTIL RELEASE NEXT
%left <s> NOT OR AND IMPL
%token <s> '(' ')'

%type <s> formula main_formula constant_formula

%start formula

%%

formula
 	: main_formula
          {
            OFP = fopen("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/output", "w");
            fprintf(OFP, "%s\n", $1);
            fclose(OFP);
          }
        ;


main_formula
	: IDENTIFIER
        | constant_formula 
          {
            strcpy($$, $1);
          }
 	| '(' main_formula ')'
          {
            sprintf($$, "(%s)", $2);
          }
        | NOT main_formula
          {
            sprintf(str, "!%s", $2);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
	| main_formula AND main_formula
          {
            sprintf(str, "%s /\\ %s", $1, $3);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
	| main_formula OR main_formula
          {
            sprintf(str, "%s \\/ %s", $1, $3);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
        | main_formula IMPL main_formula
          {
            sprintf(str, "!%s \\/ %s", $1, $3);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
	| ALWAYS main_formula
          {
            //sprintf(str, "(false R %s)", $2);
            sprintf(str, "(! (true U (!%s)))", $2);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
	| EVENTUALLY main_formula
          {

            sprintf(str, "(true U %s)", $2);
            strcpy($$, str);
            printf("  ==%s==\n", $$);
          }
        | ALWAYS '[' CONSTANT ',' CONSTANT ']' main_formula
	  {
            //sprintf(str, "(false R[%s,%s] %s)", $3, $5, $7);
            sprintf(str, "(! (true U[%s,%s] (!%s)))", $3, $5, $7);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
	| EVENTUALLY '[' CONSTANT ',' CONSTANT ']' main_formula
          {
            sprintf(str, "(true U[%s, %s] %s)", $3, $5, $7);
            strcpy($$, str);
            printf("  ==%s==\n", $$);
          }
   	| NEXT main_formula
          {
            sprintf(str, "X %s", $2);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
	| main_formula UNTIL main_formula
          {
            sprintf(str, "%s U %s", $1, $3);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
      	| main_formula RELEASE main_formula
          {
            sprintf(str, "%s R %s", $1, $3);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
        | main_formula UNTIL '[' CONSTANT ',' CONSTANT ']' main_formula
          {
            sprintf(str, "%s U[%s,%s] %s", $1, $4, $6, $8);
            strcpy($$, str);
            printf("  ==%s==\n", str);
          }
        | main_formula RELEASE '[' CONSTANT ',' CONSTANT ']' main_formula
          {
            sprintf(str, "%s R[%s,%s] %s", $1, $4, $6, $8);
            strcpy($$, str);
            printf("  ==%s==\n", str);
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

#include <stdio.h>
#include "simplifyformula_yacc.h"


extern FILE* yyin;
extern char yytext[];
extern int column;

int main(int argc, char *argv[]) {
  printf("have to open: %s", argv[1]);
  yyin = fopen(argv[1], "r");
  yyparse();
}


int yyerror(char *s)
{
  //fflush(stdout);
  printf("\n%*s\n%*s\n", column, "^", column, s);
  return 0;
}
