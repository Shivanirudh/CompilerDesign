%{
    #include<stdio.h>
    int flag = 0;
    int yylex(void);
    int yyerror(char *);
    int yywrap();
    extern int yy_flex_debug; 
%}

%token NUM ID AOP
%token SEP
%token MUL_OP ADD_OP

%right MUL_OP
%left ADD_OP

%%
program : assn_stmts assn_stmt
;
assn_stmts : assn_stmt assn_stmts
           | assn_stmt
;
assn_stmt : ID AOP expr {printf("\nAssignment statement found\n");}
;
expr : expr ADD_OP expr  
  | expr MUL_OP expr 
  | NUM 
  | ID 
;
%%
int yyerror(char* str){
    //flag = 1;
    //printf("\n%s", str);
    return 0;
}
int yywrap(){
    return 1;
}

int main(){
    yy_flex_debug = 1;
    yyparse();
    if(flag==0) 
        printf("\nSyntactically correct\n"); 
    return 0;
}