#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void tab(int val){
    while(val--)
        printf("\t");
}

int F(char *str, int *look_ahead, int level){
    if (str[*look_ahead] == 'i')
    {
        tab(level);
        printf("F: i matched\n");
        (*look_ahead)++;
    }
}

int Tprime(char *str, int *look_ahead, int level){
    if(str[*look_ahead] == '*'){
        tab(level);
        printf("T': * matched\n");
        (*look_ahead)++;

        tab(level);
        printf("----------------------------\n");
        tab(level);
        printf("Enter F\n");
        F(str, look_ahead, level + 1);
        tab(level);
        printf("Exit F\n");
        tab(level);
        printf("----------------------------\n");

        tab(level);
        printf("----------------------------\n");
        tab(level);
        printf("Enter T'\n");
        Tprime(str, look_ahead, level + 1);
        tab(level);
        printf("Exit T'\n");
        tab(level);
        printf("----------------------------\n");
        
    }
}

int T(char *str, int *look_ahead, int level){
    tab(level);
    printf("----------------------------\n");
    tab(level);
    printf("Enter F\n");
    F(str, look_ahead, level + 1);
    tab(level);
    printf("Exit F\n");
    tab(level);
    printf("----------------------------\n");

    tab(level);
    printf("----------------------------\n");
    tab(level);
    printf("Enter T'\n");
    Tprime(str, look_ahead, level + 1);
    tab(level);
    printf("Exit T'\n");
    tab(level);
    printf("----------------------------\n");
}
int Eprime(char *str, int *look_ahead, int level){
    
    if(str[*look_ahead] == '+'){
        tab(level);
        printf("E': + matched\n");
        (*look_ahead)++;
        
        tab(level);
        printf("----------------------------\n");
        tab(level);
        printf("Enter T\n");
        T(str, look_ahead, level + 1);
        tab(level);
        printf("Exit T\n");
        tab(level);
        printf("----------------------------\n");

        tab(level);
        printf("----------------------------\n");
        tab(level);
        printf("Enter E'\n");
        Eprime(str, look_ahead, level + 1);
        tab(level);
        printf("Exit E'\n");
        tab(level);
        printf("----------------------------\n");
    }
}
int E(char *str, int *look_ahead, int level){
    tab(level);
    printf("----------------------------\n");
    tab(level);
    printf("Enter T\n");
    T(str, look_ahead, level+1);
    tab(level);
    printf("Exit T\n");
    tab(level);
    printf("----------------------------\n");

    tab(level);
    printf("----------------------------\n");
    tab(level);
    printf("Enter E'\n");
    Eprime(str, look_ahead, level+1);
    tab(level);
    printf("Exit E'\n");
    tab(level);
    printf("----------------------------\n");
}

int main(){
    /*char *prod_set[100];
    for (int i = 0; i < 100;i++)
        prod_set[i] = (char *)calloc(100, sizeof(char));

    int prod_ctr;
    printf("\nEnter number of productions in grammar: ");
    scanf("%d", &prod_ctr);
    printf("\nEnter grammar: ");
    for (int i = 0; i < prod_ctr;i++){
        scanf(" %s", prod_set[i]);
    }*/

    char *str = (char*)calloc(100, sizeof(char));
    printf("\nEnter string to parse: ");
    scanf(" %s", str);
    strcat(str, "$");
    int look_ahead = 0;
    
    printf("----------------------------\n");
    printf("Enter E\n");
    E(str, &look_ahead, 1);
    printf("Exit E\n");
    printf("----------------------------\n");
    
    if (str[look_ahead] == '$')
        printf("\nSuccess");
    else
        printf("\nFailure");
}