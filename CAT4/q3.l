%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
%}
%option yylineno

id [a-z][a-z]*
num [0-9]+
add_op ("+"|"-")
mul_op ("*"|"/")

%%
{num} {yylval.int_val = atoi(yytext);return NUM;}
{id} {yylval.str = strdup(yytext);return ID;}
"=" {yylval.str = strdup(yytext);return AOP;}
{mul_op} {yylval.str = strdup(yytext);return MUL_OP;}
{add_op} {yylval.str = strdup(yytext);return ADD_OP;}
";" {return SEP;}
[+\-^*/,()] {return *yytext;}
[ \t\n]+  {;}

. {
    char errmsg[100];
    sprintf(errmsg, "Invalid Character: %s at line %d", yytext, yylineno);
    strcat(errmsg, "\n");
    yyerror(errmsg);
  }
%%