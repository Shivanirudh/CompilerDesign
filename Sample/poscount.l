%{
    #include<stdio.h>
    #include<string.h>
    int count = 0;
%}
zero [0]
digit [-]?[0-9]+
%%
{zero} {printf("Positive Count: %d", count);return 0;}
{digit} {if(atoi(yytext)>0) count++;}
%%
int yywrap(void){}
int main()
{
    yylex();
    return 0;
}