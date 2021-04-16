%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
%}
%option yylineno

num [0-9]+
real {num}\.{num}

if if
else else
then then
begin begin
end end

rel_op ("<"|"<="|">"|">="|"=="|"!=")
add_op ("+"|"-")
mul_op ("*"|"/"|"%")
assn_op ("+="|"-="|"*="|"/="|"=")

id [a-z][a-z]*
spl (";"|","|"{"|"}"|"("|")"|"="|"&"|"|"|"!"|":")

%%
{num} {yylval.int_val = atoi(yytext);return INT_CONST;}
{real} {yylval.float_val = atof(yytext);return REAL_CONST;}
['].['] {yylval.char_val = yytext[1];return CHAR_CONST;}

"integer" {return INT;}
"real" {return REAL;}
"char" {return CHAR;}


"(" {return POPEN;}
")" {return PCLOSE;}

{if} {return IF;}
{else} {return ELSE;}
{then} {return THEN;}
{begin} {return BGN;}
{end} {return END;}

{rel_op} {yylval.str = strdup(yytext); return REL_OP;}
{mul_op} {yylval.str = strdup(yytext); return MUL_OP;}
{add_op} {yylval.str = strdup(yytext); return ADD_OP;}

{id} {yylval.str = strdup(yytext);return ID;}
{spl} {return *yytext;}
[\t\n]+  {;}
" " {;}
. {
    char errmsg[100];
    sprintf(errmsg, "Invalid Character: %s at line %d", yytext, yylineno);
    strcat(errmsg, "\n");
    yyerror(errmsg);
  }
%%