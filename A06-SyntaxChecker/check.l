%{
    #include<stdio.h>
    #include "y.tab.c"
    extern YYSTYPE yylval;
%}

kw int|char|float|double|if|else|for|while|do
num [0-9]+
id [a-z][a-z]+
%%
{num} {return NUM;}
{kw} {return KW;}
{id} {return ID;}
("+="|"-="|"*="|"/="|"=") {printf("%s is an assign op\n", yytext);return AOP;}
[+\-^*/,().] {return *yytext;}
[\t]  

[\n] return 0; 

. return yytext[0]; 
%%
int yywrap(){
    return 1;
}
