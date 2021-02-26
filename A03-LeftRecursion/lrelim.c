#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int elim_lr(char* production){
    
    char* prod = (char*)calloc(100, sizeof(char));
    strcpy(prod, production);

    char* token = strtok(prod, "->");
    char sym = token[0];

    token = strtok(NULL, "->");

    char* tok = strtok(token, "|");
    char *alpha[10];
    int al = 0;
    
    char *beta[10];
    int be = 0;
    while(tok){
        if(sym == tok[0]){
            alpha[al] = (char *)calloc(100, sizeof(char));
            for(int i = 1; tok[i]; i++){
                alpha[al][i-1] = tok[i];
            }
            al++;
        }
        else{
            beta[be++] = (char*)calloc(100, sizeof(char));
            strcpy(beta[be-1], tok);
        }
        tok = strtok(NULL, "|");
    }
    
    if(be == 0){
        printf("%s is a Left Recursive production, but cannot be reduced", production);
        return 0;
    }

    printf("%c -> ", sym);
    for(int i = 0;i<be;i++){
        printf("%s%c'", beta[i], sym);
        if(i+1 != be)
            printf(" | ");
    }
    printf("\n");
    printf("%c' -> epsilon| ", sym);
    for (int i = 0; i < al;i++){
        printf("%s%c'", alpha[i], sym);
        if(i+1 != al)
            printf(" | ");
    }
    printf("\n");
}

int check_lr(char* production){
    char* prod = (char*)calloc(100, sizeof(char));
    strcpy(prod, production);
    char *token = strtok(prod, "->");
    char sym = token[0];
    token = strtok(NULL, "->");
    if(sym == token[0])
        elim_lr(production);
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

    FILE *fp;
    fp = fopen(file_name, "r+");
    int ctr = 0;
    fscanf(fp, " %[^\n]", production);
    while (ctr < line_count(file_name))
    {
        check_lr(production);
        fscanf(fp, " %[^\n]", production);
        ctr++;
    }
}