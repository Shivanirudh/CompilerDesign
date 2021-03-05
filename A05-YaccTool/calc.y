%{
    #include<stdio.h>
    #define YYSTYPE double
    int flag = 0;

    int yylex(void);

    double pow(double x, double y){
        double pdt = 1.0;
        while(y--){
            pdt *= x;
        }
        return pdt;
    }

%}

%token  NUM
%left '+' '-'
%left '/' '*' '%'
%right '^'
%left '(' ')'

%%
P : E {printf("\nResult: %lf\n", $$);}
E : E '+' E {$$ = $1 + $3;}
  | E '-' E {$$ = $1 - $3;}
  | E '*' E {$$ = $1 * $3;}
  | E '/' E {$$ = $1 / $3;}
  | E '^' E {$$ = pow($1, $3);}
  |'('E')' {$$=$2;} 
  | NUM {$$ = $1;}
  ;
%%
int yyerror ()
{
    printf("\nEntered arithmetic expression is Invalid\n\n"); 
   flag=1; 
   
}

int main (void){
    printf("\nEnter expression: ");
    yyparse();
    if(flag==0) 
        printf("\nEntered arithmetic expression is Valid\n\n"); 
    return 0;
}