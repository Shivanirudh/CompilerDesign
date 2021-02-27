#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void tab(int val){
    while(val--)
        printf("\t");
}

int F(char *str, int *look_ahead){
    if (str[*look_ahead] == 'i')
    {
        tab((*look_ahead) + 1);
        printf("F: i matched\n");
        (*look_ahead)++;
    }
}

int Tprime(char *str, int *look_ahead){
    if(str[*look_ahead] == '*'){
        tab((*look_ahead) + 1);
        printf("T': * matched\n");
        (*look_ahead)++;

        tab((*look_ahead) + 1);
        printf("Enter F\n");
        F(str, look_ahead);
        tab((*look_ahead) + 1);
        printf("Exit F\n");

        tab((*look_ahead) + 1);
        printf("Enter T'\n");
        Tprime(str, look_ahead);
        tab((*look_ahead) + 1);
        printf("Exit T'\n");
        
    }
}

int T(char *str, int *look_ahead){
    tab((*look_ahead) + 1);
    printf("Enter F\n");
    F(str, look_ahead);
    tab((*look_ahead) + 1);
    printf("Exit F\n");
    
    tab((*look_ahead) + 1);
    printf("Enter T'\n");
    Tprime(str, look_ahead);
    tab((*look_ahead) + 1);
    printf("Exit T'\n");
}
int Eprime(char *str, int *look_ahead){
    
    if(str[*look_ahead] == '+'){
        tab((*look_ahead) + 1);
        printf("E': + matched\n");
        (*look_ahead)++;
        
        tab((*look_ahead) + 1);
        printf("Enter T\n");
        T(str, look_ahead);
        tab((*look_ahead) + 1);
        printf("Exit T\n");

        tab((*look_ahead) + 1);
        printf("Enter E'\n");
        Eprime(str, look_ahead);
        tab((*look_ahead) + 1);
        printf("Exit E'\n");
    }
    printf("Exit E'\n");
}
int E(char *str, int *look_ahead){
    tab((*look_ahead) + 1);
    printf("Enter T\n");
    T(str, look_ahead);
    tab((*look_ahead) + 1);
    printf("Exit T\n");
    
    tab((*look_ahead) + 1);
    printf("Enter E'\n");
    Eprime(str, look_ahead);
    tab((*look_ahead) + 1);
    printf("Exit E'\n");
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
    printf("Enter E\n");
    E(str, &look_ahead);
    printf("Exit E\n");
    if (str[look_ahead] == '$')
        printf("\nSuccess");
    else
        printf("\nFailure");
}