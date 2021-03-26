%{
    #include<stdio.h>
    #define YYSTYPE double

    int flag = 0;
    int yylex(void);
%}

%token NUM ID KW AOP

%%
P : A_EX   { printf("Result\n");return 0; }
;
A_EX : ID AOP expr {printf("\nAssignment expression\n");}
;
expr : expr '+' expr  
  | expr '-' expr 
  | expr '*' expr 
  | expr '/' expr 
  | NUM 
  | ID 

;
%%

int yyerror (char const* s)
{
    printf("\nSyntactically Incorrect: %s\n", s); 
    flag=1; 
}

int main (void){
    printf("\nEnter expression: ");
    yyparse();
    if(flag==0) 
        printf("\nSyntactically correct\n"); 
    return 0;
}