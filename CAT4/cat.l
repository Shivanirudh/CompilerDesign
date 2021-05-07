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
{num} {return NUM;}
{id} {return ID;}
("+="|"-="|"*="|"/="|"=") {return AOP;}
{mul_op} {return MUL_OP;}
{add_op} {return ADD_OP;}
";" {return SEP;}
[+\-^*/,()] {return *yytext;}
[ \t\n]+  {;}
. return yytext[0]; 
%%