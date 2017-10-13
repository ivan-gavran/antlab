D		[0-9]
L		[a-zA-Z_]

%{
#include <stdio.h>
#include "simplifyformula_yacc.h"

int comment();
void count();
%}

%%

"/*"				{ comment(); }

"true"				{ count(); return(TRUE); }
"false"				{ count(); return(FALSE); }
"!"				{ count(); return(NOT); }
"/\\"				{ count(); return(AND); }
"\\/"				{ count(); return(OR); }
"->"				{ count(); return(IMPL); }
"[]" 				{ count(); return(ALWAYS); }
"<>"				{ count(); return(EVENTUALLY); }
"U"				{ count(); return(UNTIL); }
"R"				{ count(); return(RELEASE); }
"X"				{ count(); return(NEXT); }
"["                             { count(); return('['); }
"]"                             { count(); return(']'); }
"(" 				{ count(); return('('); }
")" 				{ count(); return(')'); }
","				{ count(); return(','); }

{D}*				{ count();
				  strcpy(yylval.s, strdup(yytext));
                                  return(CONSTANT); 
                                }

{L}({L}|{D})*		        { count();
                                  //yylval.s = strdup(yytext);
                                  strcpy(yylval.s, strdup(yytext));
                                  return(IDENTIFIER); 
                                }


[ \t\v\n\f]		        { count(); }
.                               { }



%%

int yywrap()
{
	return(1);
}


int comment()
{
  char c, c1;
	
  printf("%s", yytext);

  loop:
  while ((c = getchar()) != '*' && c != 0)
  putchar(c);

  putchar(c);
  if ((c1 = getchar()) != '/' && c != 0) 
  {
    unput(c1);
    goto loop;
  }

  if (c != 0)
  {
    putchar(c1);
  }
  return 0;
}


int column = 0;

void count()
{
  int i;

  for (i = 0; yytext[i] != '\0'; i++)
  if (yytext[i] == '\n')
    column = 0;
  else if (yytext[i] == '\t')
    column += 8 - (column % 8);
  else
    column++;

  ECHO;
}
