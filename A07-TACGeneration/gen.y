%{
    #include<stdio.h>

    int flag = 0;
    int yylex(void);
%}

%token NUM ID KW AOP

%%
assn_stmt : ID AOP expr  {printf("\n%s %c %c", $1, $2, $3)}
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

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Enter file name as argument!\n");
        return 1;
    }
    yyin = fopen(argv[1], "rt");
    if (!yyin){
        fprintf(stderr, "File not found!\n");
        return 2;
    }
    yyparse();
    if(flag==0) 
        printf("\nSyntactically correct\n"); 
    return 0;
}