#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int F(char *str, int *look_ahead){
    printf("\nEnter F\n");
    if (str[*look_ahead] == 'i')
    {
        printf("F: i matched");
        *look_ahead++;
    }
    printf("\nExit F\n");
}

int Tprime(char *str, int *look_ahead){
    printf("\nEnter T'\n");
    if(str[*look_ahead] == '*'){
        printf("T': * matched");
        *look_ahead++;
        F(str, look_ahead);
        Tprime(str, look_ahead);
        
    }
    printf("\nExit T'\n");
}

int T(char *str, int *look_ahead){
    printf("\nEnter T\n");
    F(str, look_ahead);
    Tprime(str, look_ahead);
    printf("\nExit T\n");
}
int Eprime(char *str, int *look_ahead){
    printf("\nEnter E'\n");
    if(str[*look_ahead] == '+'){
        printf("E': + matched");
        *look_ahead++;
        T(str, look_ahead);
        Eprime(str, look_ahead);
    }
    printf("\nExit E'\n");
}
int E(char *str, int *look_ahead){
    printf("\nEnter E\n");
    T(str, look_ahead);
    Eprime(str, look_ahead);
    printf("\nExit E\n");
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
    E(str, &look_ahead);
    if (str[look_ahead] == '$')
        printf("\nSuccess");
    else
        printf("\nFailure");
}