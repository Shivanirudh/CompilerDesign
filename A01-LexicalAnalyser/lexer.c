#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int check_keyword(char *token){
    int res = 1;
    FILE *fp;
    fp = fopen("Keywords.txt", "r");
    if(fp == NULL){
        printf("\nRead Error");
        return 0;
    }
    else{
        char *key = (char*)calloc(100, sizeof(char));
        char ch = fgetc(fp);
        while(ch != EOF){
            if(ch == '\n'){
                res = strcmp(token, key);
                strcpy(key, "");
                if(res == 0)
                    break;
            }
            else{
                strncat(key, &ch, 1);
            }
            ch = fgetc(fp);
        }
    }
    fclose(fp);
    return !res;
}

int check_operator(char *token){
    int res = 0;
    FILE *fp;
    fp = fopen("ArithmeticOp.txt", "r");
    if(fp == NULL){
        printf("\nRead Error");
        return 0;
    }
    else{
        char *key = (char*)calloc(100, sizeof(char));
        char ch = fgetc(fp);
        while(ch != EOF){
            if(ch == '\n'){
                res = strcmp(token, key);
                strcpy(key, "");
                if(res == 0){
                    res++;
                    fclose(fp);
                    return res;
                }
            }
            else{
                strncat(key, &ch, 1);
            }
            ch = fgetc(fp);
        }
    }
    fclose(fp);
    fp = fopen("RelationalOp.txt", "r");
    if(fp == NULL){
        printf("\nRead Error");
        return 0;
    }
    else{
        char *key = (char*)calloc(100, sizeof(char));
        char ch = fgetc(fp);
        while(ch != EOF){
            if(ch == '\n'){
                res = strcmp(token, key);
                strcpy(key, "");
                if(res == 0){
                    res+=2;
                    fclose(fp);
                    return res;
                }
            }
            else{
                strncat(key, &ch, 1);
            }
            ch = fgetc(fp);
        }
    }
    fclose(fp);
    fp = fopen("LogicalOp.txt", "r");
    if(fp == NULL){
        printf("\nRead Error");
        return 0;
    }
    else{
        char *key = (char*)calloc(100, sizeof(char));
        char ch = fgetc(fp);
        while(ch != EOF){
            if(ch == '\n'){
                res = strcmp(token, key);
                strcpy(key, "");
                if(res == 0){
                    res+=3;
                    fclose(fp);
                    return res;
                }
            }
            else{
                strncat(key, &ch, 1);
            }
            ch = fgetc(fp);
        }
    }
    fclose(fp);
}

int check_separator(char token){
    int res = 0;
    FILE *fp;
    fp = fopen("Separators.txt", "r");
    if(fp == NULL){
        printf("\nRead Error");
        return 0;
    }
    else{
        char ch = fgetc(fp);
        while(ch != EOF){
            if(ch == token){
                res = 1;
                break;
            }
            ch = fgetc(fp);
        }
    }
    fclose(fp);
    return res;
}

char* lexer(char *content){
    char *lex = (char*)calloc(100, sizeof(char));
    char *tok = strtok(content, " ");
    
    int ctr = 0;
    char *token_list[100];

    for(int i = 0;i<100;i++){
        token_list[i] = (char*)calloc(100, sizeof(char));
    }

    while(tok){
        strcpy(token_list[ctr], tok);
        ctr++;
        tok = strtok(NULL, " ");
    }

    for(int j = 0; j < ctr;j++){

        char *t = (char*)calloc(100, sizeof(char));
        strcpy(t, token_list[j]);

        if(t[strlen(t) - 1] == '/' && t[strlen(t) - 2] == '*'){
            strcat(lex, "MC ");
            break;
        }

        if (t[0] == '/'){
            if (t[1] == '/')
            {
                strcat(lex, "SC ");
                break;
            }
            else if (t[1] == '*')
            {
                strcat(lex, "MC ");
                break;
            }
        }
        int kw = check_keyword(t); //Check if keyword
        int op = check_operator(t);//Check if operator

        if(op == 1){
            strcat(lex, "ARITHOP ");
        }
        else if(op == 2){
            strcat(lex, "RELOP ");
        }
        else if(op == 3){
            strcat(lex, "LOGICALOP ");
        }
        else if(kw == 1){
            strcat(lex, "KW ");
        }
        else if(strcmp(t, "=") == 0){
            strcat(lex, "ASSIGN ");
        }
        else{
            char *cp = (char *)calloc(100, sizeof(char));
            strcpy(cp, t);
            char *token = strtok(t, "(");
            int func = check_keyword(token);
            if(func == 1){
                if((strcmp(token, "if") == 0) || (strcmp(token, "for") == 0) || (strcmp(token, "while") == 0)){
                    strcat(lex, "KW SP ");
                    token = strtok(NULL, "(");
                    for(int k = 0;token[k];k++){
                        if(isalpha(token[k])){
                            strcat(lex, "ID ");
                            while(isalpha(token[k]) || isdigit(token[k]) || token[k] == '_')
                                k++;
                            k--;
                        }
                        else if(token[k] == '=')
                            strcat(lex, "ASSIGN ");
                        else if(check_separator(token[k]))
                            strcat(lex, "SP ");
                        else if(isdigit(token[k])){
                            strcat(lex, "NUMCONSTANT ");
                            while(isdigit(token[k]))
                                k++;
                            k--;
                        }
                        else if(token[k] == '\''){
                            strcat(lex, "CHARCONSTANT ");
                            k++;
                            while(token[k] != '\'')
                                k++;
                        }
                        else if(token[k] == '\"'){
                            strcat(lex, "STRINGCONSTANT ");
                            k++;
                            while(token[k] != '\"')
                                k++;
                        }
                        else{
                            char *c = (char*)calloc(10, sizeof(char));
                            strncpy(c, &token[k], 1);
                            char next = token[k+1];
                            if(next == '=' || next == '|' || next == '&'){
                                strncat(c, &token[++k], 1);
                            }
                            else if(check_operator(&next)>0){
                                k++;
                            }
                            else;

                            int check = check_operator(c);
                            if(check == 1)
                                strcat(lex, "ARITHOP ");
                            else if(check == 2)
                                strcat(lex, "RELOP ");
                            else if(check == 3)
                                strcat(lex, "LOGICALOP ");
                            else
                                strcat(lex, "INV ");
                        }
                    }
                }
                else{
                    strcat(lex, "FC ");
                    if(strcmp(token, "main")){
                        int flag = 0;
                        while(!flag && token_list[j]){
                            t = token_list[j];
                            for(int k = 0; token[k];k++){
                                if(token[k] == ';')
                                    flag = 1;
                            }
                            j++;
                        }
                        j--;
                    }
                }
            }
            else{
                if (strcmp(token, cp) != 0)
                {
                    strcat(lex, "FC ");
                }
                else{
                    for(int i = 0;token[i];i++){
                        if(isalpha(token[i])){
                            strcat(lex, "ID ");
                            while(isalpha(token[i]) || isdigit(token[i]) || token[i] == '_')
                                i++;
                            i--;
                        }
                        else if(token[i] == '=')
                            strcat(lex, "ASSIGN ");
                        else if(check_separator(token[i]))
                            strcat(lex, "SP ");
                        else if(isdigit(token[i])){
                            strcat(lex, "NUMCONSTANT ");
                            while(isdigit(token[i]))
                                i++;
                            i--;
                        }
                        else{
                            char *c = (char*)calloc(10, sizeof(char));
                            strncpy(c, &token[i], 1);
                            char next = token[i+1];
                            if(next == '=' || next == '|' || next == '&'){
                                strncat(c, &token[++i], 1);
                            }
                            else if(check_operator(&next)>0)
                                i++;
                            else;

                            int check = check_operator(c);
                            if(check == 1)
                                strcat(lex, "ARITHOP ");
                            else if(check == 2)
                                strcat(lex, "RELOP ");
                            else if(check == 3)
                                strcat(lex, "LOGICALOP ");
                            else
                                strcat(lex, "INV ");
                            
                        }
                    }
                }
            }
        }
    }
    return lex;

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
    FILE *fp;
    char ch;
    char *filename = (char*)calloc(100, sizeof(char));
    char *content = (char*)calloc(100, sizeof(char));
    char *copy = (char*)calloc(100, sizeof(char));
    char *lex = (char*)calloc(200, sizeof(char));

    /*Single line
    scanf(" %[^\n]", content);
    strcpy(copy, content);
    strcpy(lex, lexer(copy));

    printf("Ip: %s\n", content);
    printf("Op: %s\n", lex);
    */
    //File
    printf("\nEnter file name:");scanf(" %[^\n]", filename);

    printf("______________________________________________________________________\n");
    printf("FC: Function call\n");
    printf("KW: Keyword\n");
    printf("ID:identifier");
    printf("RELOP: Relational operator\n");
    printf("LOGICALOP: Logical Operator\n");
    printf("ARITHOP: Arithmetic Operator\n");
    printf("SP:Separator\n");
    printf("______________________________________________________________________\n");

    fp = fopen(filename, "r");
    fscanf(fp, " %[^\n]", content);
    int c = 0;
    while(c < line_count(filename)){
        strcpy(copy, content);
        strcpy(lex, lexer(copy));
        printf("%s\n", lex);
        fscanf(fp, " %[^\n]", content);
        c++;
    }
    fclose(fp);

    
}