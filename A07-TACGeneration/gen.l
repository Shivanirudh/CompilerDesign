%{
    #include<stdio.h>
    #include "y.tab.c"
    extern YYSTYPE yylval;
%}

kw int|char|float|double|while|do
num [0-9]+
id [a-z][a-z]*

%%
{num} {return *yytext;}
{kw} {return KW;}
{id} {return *yytext;}
("+="|"-="|"*="|"/="|"=") {return *yytext;}

[+\-^*/,().] {return *yytext;}
[\t]
[ ]  
[\n]

. return yytext[0]; 
%%
int yywrap(){
    return 1;
}