%{
    #include<stdio.h>
    #define YYSTYPE double

    int flag = 0;
    int yylex(void);
%}

%token NUM ID KW AOP
%token IF ELSE ROP
%token POPEN PCLOSE BOPEN BCLOSE
%token FOR WHILE
%token SEP
%token CHANGE_OP


%%
stmt : assn_stmt
  | cond_stmt
  | loop_stmt
;
assn_stmt : ID AOP expr {printf("\nAssignment statement found\n");}
;
expr : expr '+' expr  
  | expr '-' expr 
  | expr '*' expr 
  | expr '/' expr 
  | NUM 
  | ID 
;

cond_stmt : IF cond stmt continue {printf("\nConditional statement found\n");}
;
cond : POPEN rel_expr PCLOSE
;
continue : ELSE stmt
         | 
;
rel_expr : expr ROP expr
;

loop_stmt : for_stmt
          | while_stmt
;
for_stmt : FOR POPEN assn_stmt SEP rel_expr SEP inc_expr PCLOSE BOPEN stmt BCLOSE {printf("\nLooping statement found\n");}
;

inc_expr :  assn_stmt
           | expr CHANGE_OP
;
while_stmt : WHILE cond BOPEN stmt BCLOSE
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