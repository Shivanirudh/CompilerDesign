#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    char *prod_set[100];
    for (int i = 0; i < 100;i++)
        prod_set[i] = (char *)calloc(100, sizeof(char));

    int prod_ctr;
    printf("\nEnter number of productions in grammar: ");
    scanf("%d", &prod_ctr);
    printf("\nEnter grammar: ");
    for (int i = 0; i < prod_ctr;i++){
        scanf(" %s", prod_set[i]);
    }
    
    for (int i = 0; i <= prod_ctr;i++){
        printf(" %s\n", prod_set[i]);
    }

    char start_sym = prod_set[0][0];

    char terminals[10];
    int tc = 0;
    char nonterminals[10];
    int ntc = 0;

    nonterminals[0] = start_sym;

    for (int i = 0; i < prod_ctr;i++){
        for (int j = 0; prod_set[i][j];j++){
            char sym = prod_set[i][j];
            if (sym >= 'A' && sym <= 'Z')
            {
                int flag = 0;
                if (prod_set[i][j + 1] == '\'')
                {
                    sym += 32;
                }
                for (int k = 0; k < tc;k++){
                    if(terminals[k] == sym){
                        flag = 1;
                    }
                }
                if(!flag)
                    terminals[tc++] = sym;
            }
            else{
                int flag = 0;
                for (int k = 0; k < tc;k++){
                    if(nonterminals[k] == sym){
                        flag = 1;
                    }
                }
                if(!flag)
                    nonterminals[ntc++] = sym;
            }
        }
    }
}