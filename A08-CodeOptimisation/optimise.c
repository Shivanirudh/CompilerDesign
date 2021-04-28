#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void optimize(char *s) {
    
    // addition 
    if(s[3]=='+'){
        if(s[2]=='0'||s[4]=='0'){
            if(s[0]==s[2]||s[0]==s[4]){
                printf("\n");
            }
            else{
                printf("%c%c%c\n",s[0],s[1],s[2]=='0'?s[4]:s[2]);
            }
        }
        else{
            printf("%s",s);
        }
    }
    else if(s[3]=='*'){
        if(s[2]=='1'||s[4]=='1'){
            if(s[0]==s[2]||s[0]==s[4]){
                printf("\n");
            }else{
                printf("%c%c%c\n",s[0],s[1],s[2]=='1'?s[4]:s[2]);
            }
        }
        if(s[2]==s[4]){
            printf("%c%c%c+%c\n",s[0],s[1],s[2],s[4]);
        }
    }
    else if(s[3]=='-'){
        if(s[2]=='0'||s[4]=='0'){
            if(s[0]==s[2]||s[0]==s[4]){
                printf("\n");
            }else{
                printf("%c%c%c%c\n",s[0],s[1],s[2]=='0'?'-':' ',s[2]=='0'?s[4]:s[2]);
            }
        }
        if(s[2]==s[4]){
            printf("%c%c%c+%c\n",s[0],s[1],s[2],s[4]);
        }
    }
    else if(s[3]=='/'){
        if(s[4]=='1'){
            if(s[0]==s[2]){
                printf("\n");
            }else{
                printf("%c%c%c\n",s[0],s[1],s[2]);
            }
        }
        if(s[2]=='0'){
            printf("%c%c%c\n",s[0],s[1],'0');
        }
    }
    else if(s[2]=='p'){
        if(s[8]=='2'){
            printf("%c%c%c*%c\n",s[0],s[1],s[6],s[6]);
        }else{
            printf("%s",s);
        }
    }
}

int main(int argc, char *argv[]){
    FILE *fp;
    fp = fopen(argv[1], "r");
    int i = 0;
    int tot = 0;
    char lines[100][100];
    while(fgets(lines[i], 100, fp)) {
        lines[i][strlen(lines[i])] = '\0';
        i++;
    }
    tot = i;

    for(i = 0; i < tot; ++i) {
        optimize(lines[i]);
    }
}