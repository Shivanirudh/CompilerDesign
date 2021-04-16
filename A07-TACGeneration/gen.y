%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    int yylex(void);
    int yyerror(char *);
    int yywrap();

    int tmp = 0;
    int jump = 0;

    struct info{
        char *var;
        char *code;
        int int_val;
        float float_val;
        char char_val;
    };

    typedef struct info node;

    node *makeNode(){
        node *n = (node*)calloc(1, sizeof(node));
        n->int_val = 0;
        n->float_val = 0;
        n->char_val = 0;
        n->var = (char*)calloc(50, sizeof(char));
        n->code = (char*)calloc(5000, sizeof(char));
        return n;
    }
%}

%token BGN END
%token INT REAL CHAR
%token INT_CONST REAL_CONST CHAR_CONST
%token ID
%token IF ELSE THEN REL_OP
%token POPEN PCLOSE
%token MUL_OP ADD_OP

%right MUL_OP
%left ADD_OP

%union{
    int int_val;
    float float_val;
    char char_val;
    char *str;
    struct info *Node;
}

/*Declaring types for the tokens*/
%type<str> ID REL_OP ADD_OP MUL_OP
%type<int_val> INT_CONST
%type<float_val> REAL_CONST
%type<char_val> CHAR_CONST
%type<Node> program structure decl_stmts stmts
%type<Node> decl_stmt type value stmt
%type<Node> assn_stmt cond_stmt condition expr
%type<Node> E T F

%%

program : structure{
            printf("\nL%-5d - |\n%s", 0, $$->code);
          }
;

structure : decl_stmts BGN stmts END{
                sprintf($$->code, "%s%10s\n%s", $1->code, "|", $3->code);
            }
;

decl_stmts : decl_stmt decl_stmts{
                $$ = makeNode();
                sprintf($$->code, "%s%s", $1->code, $2->code);
             }

           | decl_stmt{
                $$ = $1;
             }
;

decl_stmt : ID ':' type ';' {
                $$ = makeNode();
                sprintf($$->code, "%10s %-5s := %s\n", "|", $1, $3->var);
            }

          | ID ':' type '=' value ';'{
                $$ = makeNode();
                sprintf($$->code, "%10s %-5s := %s\n", "|", $1, $5->var);
            }
;

type : INT{
            $$ = makeNode();
            $$->int_val = 0;
            sprintf($$->var, "%d", 0);
            sprintf($$->code, "");
       }
                
     | REAL{
            $$ = makeNode();
            $$->float_val = 0.0;
            sprintf($$->var, "%.2f", 0.0);
            sprintf($$->code, "");
       }
                
     | CHAR{
            $$ = makeNode();
            $$->char_val = 0;
            sprintf($$->var, "%s", "NULL");
            sprintf($$->code, "");
       }
                ;

value : INT_CONST{
            $$ = makeNode();
            $$->int_val = $1;
            sprintf($$->var, "%d", $1);
            sprintf($$->code, "");
        }       
      | REAL_CONST{
            $$ = makeNode();
            $$->float_val = $1;
            sprintf($$->var, "%.2f", $1);
            sprintf($$->code, "");
        }
      | CHAR_CONST{
            $$ = makeNode();
            $$->int_val = $1;
            sprintf($$->var, "%c", $1);
            sprintf($$->code, "");
        }
;

stmts : stmt stmts{
            $$ = makeNode();
            sprintf($$->code, "%s%s", $1->code, $2->code);
        }  
      | stmt{
            $$ = $1;
        }
;

stmt : assn_stmt {
        $$ = $1;
       }
     | cond_stmt{
            $$ = $1;
       }
;

assn_stmt : ID '=' expr ';'{
                $$ = makeNode();
                char tac[100];
                sprintf($$->var, "%s", $1);
                sprintf(tac, "%10s %-5s := %s\n", "|", $$->var, $3->var);
                sprintf($$->code, "%s%s", $3->code, tac);
            }
;

expr : E{
        $$ = $1;
       }
;

E : T MUL_OP E{
        $$ = makeNode();
        char tac[100];
        sprintf($$->var, "x%d", ++tmp);
        sprintf(tac, "%10s %-5s := %s %s %s\n", "|", $$->var, $1->var, $2, $3->var);
        sprintf($$->code, "%s%s%s", $1->code, $3->code, tac);
    }
  | T{
        $$ = $1;
    }      
  | F{
        $$ = $1;
    }
;

T : T ADD_OP F{
        $$ = makeNode();
        char tac[100];
        sprintf($$->var, "x%d", ++tmp);
        sprintf(tac, "%10s %-5s := %s %s %s\n", "|", $$->var, $1->var, $2, $3->var);
        sprintf($$->code, "%s%s%s", $1->code, $3->code, tac);
    }
  | F{
        $$ = $1;
    }
;

F : ID{
        $$ = makeNode();
        sprintf($$->var, "%s", $1);
        sprintf($$->code, "");
    }
    | INT_CONST{
            $$ = makeNode();
            $$->int_val = $1;
            sprintf($$->var, "%d", $1);
            sprintf($$->code, "");
      }
    | REAL_CONST{
            $$ = makeNode();
            $$->float_val = $1;
            sprintf($$->var, "%.2f", $1);
            sprintf($$->code, "");
      }
    | CHAR_CONST{
            $$ = makeNode();
            $$->char_val = $1;
            sprintf($$->var, "'%c'", $1);
            sprintf($$->code, "");
      }
;

cond_stmt : IF POPEN condition PCLOSE THEN stmts ELSE stmts END IF{
                $$ = makeNode();
                int condBlock = ++jump;
                int endBlock = ++jump;
                sprintf($$->code, "%s%10s if %s then goto L%d\n%s%10s goto L%d\n%10s\nL%-5d - |\n%s%10s\nL%-5d - |\n", $3->code, "|", $3->var, condBlock, $8->code, "|", endBlock, "|", condBlock, $6->code, "|", endBlock);
            }
;

condition : expr REL_OP expr{
            $$ = makeNode();
            char tac[100];
            sprintf($$->var, "%s%s%s", $1->var, $2, $3->var);
            sprintf($$->code, "%s%s", $1->code, $3->code);
       }
;
%%

int yyerror(char* str){
    printf("\n%s", str);
    return 0;
}

int yywrap(){
    return 1;
}

int main(){
    printf("\nGiven code\n");
    system("cat file.txt");
    printf("\n-----------------------------------------------------------------------------------------\n");
    printf("\nThree Address Code\n");

    yyparse();
    return 0;
}