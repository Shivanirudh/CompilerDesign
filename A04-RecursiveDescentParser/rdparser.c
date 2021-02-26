#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int elim_lr(char* production, char* prod_set[100], int* prod_ctr){
    printf("\nHI1\n");
    char* prod = (char*)calloc(100, sizeof(char));
    char *newprod = (char *)calloc(100, sizeof(char));
    strcpy(prod, production);
    printf("\nHI2\n");
    char* token = strtok(prod, "->");
    char sym = token[0];
    printf("%c->", sym);
    printf("\nHI3\n");
    //prod_set[*prod_ctr] = (char *)calloc(100, sizeof(char));
    strncat(newprod, &sym, 1);
    //prod_set[(*prod_ctr)][0] = sym;
    printf("\nHI4\n");
    strcat(newprod, "->");
    printf("\nHI5\n");
    token = strtok(NULL, "->");
    printf("\nHI4\n");
    char* tok = strtok(token, "|");
    
    char *alpha[10];
    int al = 0;
    char *beta[10];
    int be = 0;printf("\nHI5\n");
    while(tok){
        if(sym == tok[0]){
            printf("\nHI6\n");
            alpha[al] = (char *)calloc(100, sizeof(char));
            for(int i = 1; tok[i]; i++){
                alpha[al][i-1] = tok[i];
            }
            al++;
            printf("\nHI7\n");
        }
        else{
            printf("\nHI8\n");
            beta[be++] = (char*)calloc(100, sizeof(char));
            strcpy(beta[be-1], tok);
            printf("\nHI9\n");
        }
        tok = strtok(NULL, "|");
    }
    printf("\nHI10\n");
    if(be == 0){
        printf("%s is a Left Recursive production, but cannot be reduced", production);
        return 0;
    }
    printf("\nHI11\n");

    for(int i = 0;i<be;i++){
        printf("\nHI12\n");
        printf("%s%c'", beta[i], sym);
        strcat(newprod, beta[i]);
        strncat(newprod, &sym, 1);
        strcat(newprod, "'");
        if (i + 1 != be){
            printf(" | ");
            strcat(newprod, "|");
        }
        printf("\nHI13\n");
    }
    printf("\nHI14\n");
    printf("\n");
    printf("Prod:%s\n", newprod);
    //int n = (*prod_ctr);
    //strcpy(prod_set[n], newprod);
    (*prod_ctr)++;

    strncpy(newprod, &sym, 1);
    strcat(newprod, "->epsilon|");
    printf("%c' -> epsilon| ", sym);
    printf("\nHI15\n");
    for (int i = 0; i < al;i++){
        printf("\nHI16\n");
        strcat(newprod, alpha[i]);
        strncat(newprod, &sym, 1);
        strcat(newprod, "'");
        printf("%s%c'", alpha[i], sym);
        if(i+1 != al){
            printf(" | ");
            strcat(newprod, "|");
        }
        printf("\nHI17\n");
    }
    //strcpy(prod_set[*prod_ctr], newprod);
    (*prod_ctr)++;
    printf("Prod:%s\n", newprod);
    printf("\nHI18\n");
}

int check_lr(char* production, char* prod_set[100], int* prod_ctr){
    char* prod = (char*)calloc(100, sizeof(char));
    strcpy(prod, production);
    char *token = strtok(prod, "->");
    char sym = token[0];
    token = strtok(NULL, "->");
    if(sym == token[0]){
        printf("\nHI-11\n");
        *prod_ctr--;
        elim_lr(production, prod_set, prod_ctr);
        printf("\nHI-12\n");
    }
    else  
        printf("%s\n", production);
}    

int line_count(char *file){
    FILE *fp;
    int count = 0;
    fp = fopen(file, "r");

    if (fp == NULL){ 
        return 0; 
    } 
    for(char c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n')
            count = count + 1; 
    fclose(fp); 
    return count;
}

int main(){
    char *file_name = (char*)calloc(100, sizeof(char));
    char *production = (char *)calloc(100, sizeof(char));
    printf("\nEnter file name: ");
    scanf(" %[^\n]", file_name);

    char *prod_set[100];
    for (int i = 0; i < 100;i++)
        prod_set[i] = (char*)calloc(100, sizeof(char));
    int prod_ctr = 0;
    FILE *fp;
    fp = fopen(file_name, "r+");
    int ctr = 0;
    fscanf(fp, " %[^\n]", production);

    while (ctr < line_count(file_name))
    {
        //prod_set[prod_ctr] = (char *)calloc(100, sizeof(char));
        strcpy(prod_set[prod_ctr], production);
        prod_ctr++;
        printf("\nHI-1\n");
        check_lr(production, prod_set, &prod_ctr);
        fscanf(fp, " %[^\n]", production);
        ctr++;
        printf("\nHI-2\n");
    }

    printf("\nSet of productions are:");
    for (int i = 0; i < prod_ctr; i++)
    {
        printf("%s\n", prod_set[i]);
    }
}