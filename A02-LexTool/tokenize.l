/*Inclusion*/
%{
    #include<stdio.h>
    #include<string.h>
%}
/*Rules*/

/*Preprocessor directives*/
inc #(.)*


/*Keywords*/
kw int|char|float|double|if|else|for|while|do

/*Function*/
funcCall [a-zA-Z]([a-zA-Z]|[0-9])*\(

/*ID*/
id [a-zA-Z]([a-zA-Z]|[0-9])*

/*Constant*/

numConst [0-9]+
charConst \'[a-zA-Z]\'
strConst \"[a-z A-Z]*\"

/*Comments*/
single \/\/(.)*
multi \/\*(.*\n?)*\*\/ 

/*Operators*/
relOp <|<=|>|>=|==|!= 
arithOp "+"|"-"|"*"|"/"|"%" 
logicOp &&|\|\||! 

/*Separators*/
sep [!@#$^&(){};:,] 

/* Pattern Action pairs*/
%%
{inc} {printf("PREDIR ");}
{relOp} {printf("RELOP ");}
{arithOp} {printf("ARITHOP ");}
{logicOp} {printf("LOGOP ");}
{numConst} {printf("NUMCONST ");}
{charConst} {printf("CHARCONST ");}
{strConst} {printf("STRCONST ");}
{single} {printf("SC ");}
{multi} {printf("MC ");}
{kw} {printf("KW ");}
{funcCall} {printf("FC ");}
{id} {printf("ID ");}
{sep} {printf("SP ");}
"=" {printf("ASSIGN ");}
"\n" {printf("\n");}
%%

int yywrap(void){}

int main(){
    char *name = (char*)calloc(100, sizeof(char));
    printf("Enter filename: ");scanf(" %[^\n]", name);

    yyin = fopen(name, "r+");
    yylex();
    return 0;
}