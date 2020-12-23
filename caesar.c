#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

void promptfortext();
void caesarCipher(int textlen, char *plaintext);

int stringcompare(char *str1,char *str2);
int stringlenght(char *str);

int key = 0;
int spaces = 0;
bool decrypt = false;

int main(int argc, char *argv[]){
    char *arguments[argc];
    for (int i = 0; i < argc; i++){
        arguments[i] = argv[i];
    }
    if (argc > 3){
        printf("\033[1;31m \b**There should only be two or less Arguments**\n./caesar 'help' for details\n");
        return 1;
    }else if (argc <= 1){
        printf("\033[1;31m \b**Atleast 1 argument required**\n");
        printf("\033[1;31m \b**Usage: ./caesar 'key' \033[1;33m \b'D'(optional for decryption)**\033[1;30m\n./caesar 'help' for details\n");
        return 1;
    }
    if (argc == 3){
        if (*arguments[2] == 'D'){
            decrypt = true;
            printf("\033[0;32m \b**Decrypting**\n\033[0m");
        }// (char)*argv[2] means value at pointer argv[2]
    }
    if (stringcompare(arguments[1],"help")){
        printf("\033[1;32m \b**Help**\n");
        printf("\033[0;0m \bUsage: ./caesar 'key' 'D'\n");
        printf("\033[1;33m \b1-'key' is first argument which is always Required!\n");
        printf("\033[1;36m \b2-'D' is second argument which is optional (For decryption).\n");
    }

    if(isdigit(*arguments[1]) != 0){
        if(*arguments[1] != ' ' && *arguments[1] > 0){
            key = atoi(arguments[1]);
            promptfortext();
        }
    }
}

void promptfortext(){
    printf("InputText: "); char *plaintext = get_string(NULL);

    int textlen = stringlenght(plaintext);

    if (textlen < 1){
        printf("\033[1;31m \b**Please Enter SomeText to be Encrypted**\n");
        return;
    }
    for (int i = 0; i < textlen; i++){
        if (isspace(plaintext[i])){
            spaces++;
        }if (spaces >= textlen){
            printf("\033[1;31m \b**Please Enter SomeText to be Encrypted**\n");
            return;
        }
    }
    printf("\033[0;33m \bplaintext: \033[0;0m \b%s\n",plaintext);
    caesarCipher(textlen,plaintext);
    printf("\033[0;32m \bciphertext: \033[0;0m \b%s\n",plaintext);
}

void caesarCipher(int textlen, char *plaintext){
    char encrypted[textlen - spaces];
    int lettervalue = 0, enlen = 0, min, max;

    bool expression1;
    bool expression2;
    int expression3;
    bool expression4;
    int expression5;

    for (int i = 0; i < textlen; i++){
        if(isalpha(plaintext[i]) != 0){

            lettervalue = plaintext[i];

            if (islower(plaintext[i])){
                min = 97;
                max = 122;
            }
            else if (isupper(plaintext[i])){
                min = 65;
                max = 90;
            }
            if (decrypt){
                expression1 = (lettervalue -= key) <= min;
                // expression2 = (int)lettervalue < min; -- not using it anymore causing bug
                expression3 = -1;
                expression4 = (lettervalue -= key) < min;
                expression5 = max;
            }
            else{
                expression1 = (lettervalue += key) >= max;
                // expression2 = (int)lettervalue > max; -- Values always being 'a'(min)
                expression3 = 1;
                expression4 = (lettervalue += key) > max;
                expression5 = min;
            }
            if (expression1){
                lettervalue = plaintext[i];
                for (int j = 0; j < key; j++){
                    lettervalue += expression3;
                    if (lettervalue > max || lettervalue < min){
                        lettervalue = expression5;
                    }
                }// printf("%s\n",expression4 ? "true" : "false");
            }
            else if (expression4){
                lettervalue = (int)plaintext[i];
                if (decrypt){
                    lettervalue -= key;
                }
                else{
                    lettervalue += key;
                }
            }
            encrypted[enlen] = lettervalue;
            enlen++;
        }
    }

    enlen = 0;

    for (int k = 0; k < textlen; k++){
        if (isalpha(plaintext[k])){
            plaintext[k] = encrypted[enlen];
            enlen++;
        }
    }
}

int stringcompare(char *str1,char *str2){
    while(*str1 == *str2){
        if (*str1 == '\0' || *str2 == '\0'){
            break;
        }
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0'){
        return -1;
    }
    else{
        return 0;
    }
}


int stringlenght(char *str){
    int lenght = 0;
    while (*str != '\0'){
        str++;
        lenght++;
    }
    return lenght;
}
