%{
    #include<stdio.h>
    #include "y.tab.c"
    extern YYSTYPE yylval;
%}

kw int|char|float|double|while|do
if if
else else
for for
num [0-9]+
id [a-z][a-z]*

%%
{num} {return NUM;}
{kw} {return KW;}
{if} {return IF;}
{for} {return FOR;}
{else} {return ELSE;}
"(" {return POPEN;}
")" {return PCLOSE;}
"{" {return BOPEN;}
"}" {return BCLOSE;}
{id} {return ID;}
("+="|"-="|"*="|"/="|"=") {return AOP;}
("++"|"--") {return CHANGE_OP;}
("=="|"!="|">"|"<"|">="|"<=") {return ROP;}
";" {return SEP;}
[+\-^*/,().] {return *yytext;}
[\t]
[ ]  
[\n]

. return yytext[0]; 
%%
int yywrap(){
    return 1;
}
