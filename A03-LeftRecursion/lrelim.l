/*Inclusion*/
%{
    #include<stdio.h>
    #include<string.h>
    char symbols[10];
    int ctr=0;

    void elim_lr(){
        
        char *new_prods = (char*)calloc(100, sizeof(char));
        char* prod = (char*)calloc(100, sizeof(char));
        strcpy(prod, yytext);

        char* token = strtok(prod, "->");
        char sym = token[0];
        strcat(new_prods, token);strcat(new_prods, "->");

        token = strtok(NULL, "->");

        char* tok = strtok(token, "|");
        int flag = 0;
        char *alpha = (char*)calloc(100, sizeof(char));
        char *beta[10];
        int be = 0;
        while(tok){
            if(flag == 0){
                for(int i = 1; tok[i]; i++){
                    alpha[i-1] = tok[i];
                }
                flag = 1;
            }
            else{
                beta[be++] = (char*)calloc(100, sizeof(char));
                strcpy(beta[be-1], tok);
            }
            tok = strtok(NULL, "|");
        }
        
        for(int i = 0;i<be;i++){
            strcat(new_prods, beta[i]);
            strncat(new_prods, &sym, 1);strcat(new_prods, "'");
            if(i+1 != be)
                strcat(new_prods, "|");
        }
        printf("%s\n", new_prods);
        strcpy(new_prods,"");
        strncat(new_prods, &sym, 1);strcat(new_prods, "'");
        strcat(new_prods, "-> epsilon| ");
        strcat(new_prods, alpha);
        strncat(new_prods, &sym, 1);strcat(new_prods, "'");

        printf("%s\n", new_prods);
    }

    int check_lr(){
        char* prod = (char*)calloc(100, sizeof(char));
        strcpy(prod, yytext);
        char *token = strtok(prod, "->");
        char sym = token[0];
        token = strtok(NULL, "->");
        if(sym == token[0])
            elim_lr();
        else  
            printf("%s\n", yytext);
    }
%}
/*Rules*/

prod [A-Z]([0-9'])?[-][>][A-Za-z0-9'\+\*]+([|][A-Za-z0-9'\+\*]+)? 


/* Pattern Action pairs*/
%%
{prod} {check_lr();}
%%

int yywrap(void){}

int main(){
    char *name = (char*)calloc(100, sizeof(char));
    printf("Enter filename: ");scanf(" %[^\n]", name);

    yyin = fopen(name, "r+");
    yylex();
    return 0;
}