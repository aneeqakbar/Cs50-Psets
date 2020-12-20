#include <stdio.h>
#define MAX_LENGHT (300)
#define ALPHA_LENGHT (26)

char convertupper(int letter);
char convertlower(int letter);
int strlen(char array[]);
int isalpha(int intager);

int argumentvalidation(int argc, char *argv[]);
void promptUser();
void modeChecker(char userText[]);
char cryption(int letter);

int decrypt = 0;
char alphabets[ALPHA_LENGHT] = {"abcdefghijklmnopqrstuvwxyz"};
char encrypted[MAX_LENGHT];
char userText[MAX_LENGHT];
char userCode[ALPHA_LENGHT];

// abcdefghijklmnopqrstuvwxyz
// KLMNOPQRSTUVWXYZabcdefghiJ

int main(int argc, char *argv[])
{
    if (argumentvalidation(argc, argv) == 1)
    {
        return 1;
    }
    promptUser();
    printf("\033[1;33m \bEncrypted Text: \033[0m \b%s\n", encrypted);
}

void promptUser()
{
    printf("\033[1;31m \bEnter Text: \033[0m");

    // scanf("%[^\n]",userText);
    fgets(userText, MAX_LENGHT, stdin);

    modeChecker(userText);

    printf("\n");
}

void modeChecker(char userText[])
{
    int lenght = strlen(userText);
    int alphalenght = strlen(alphabets);

    if (decrypt == 1)
    {
        char decryptCode[ALPHA_LENGHT];
        for (int i = 0; i < alphalenght; i++)
        {
            decryptCode[i] = alphabets[i];
            alphabets[i] = userCode[i];
            userCode[i] = decryptCode[i];
        }
    }

    for (int i = 0; i < lenght; i++)
    {
        encrypted[i] = cryption(userText[i]);
    }
}

char cryption(int letter)
{
    int lenght = strlen(alphabets);
    if (isalpha(letter))
    {
        for (int i = 0; i < lenght; i++)
        {
            if (letter == (int)convertupper(alphabets[i]))
            {
                letter = convertupper(userCode[i]);
                return letter;
            }
            else if (letter == (int)convertlower(alphabets[i]))
            {
                letter = convertlower(userCode[i]);
                return letter;
            }
        }
    }
    return letter;
}

int argumentvalidation(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("\033[1;32m \bUsage: ./subsitution key mode\n \033[0m");
        printf("\033[0;31m\bErrorCode: 404\n\033[0;33m \bKey Not Found\n\033[0m");
        return 1;
    }
    if (argc > 3)
    {
        printf("\033[1;32m \bUsage: ./subsitution key mode\n \033[0m");
        printf("\033[0;31m\bErrorCode: 387\n\033[0;33m \bToo Many Arguments\n\033[0m");
        return 1;
    }

    if (argc == 3)
    {
        if ((int)*argv[2] == 68)
        {
            printf("\033[1;32m**Decrypting**\n\033[0m");
            decrypt = 1;
        }
    }

    if (strlen(argv[1]) == 26)
    {
        int i = 0;
        while (*&argv[1][i] != '\0')
        {
            userCode[i] = argv[1][i];
            i++;
        }
    }
    else
    {
        printf("\033[1;32m \bUsage: ./subsitution key(26 Characters) mode\n \033[0m");
        printf("\033[0;31m\bErrorCode: 293\n\033[0;33m \bInvalid Key\n\033[0m");
        return 1;
    }

    for (int i = 0; i < ALPHA_LENGHT; i++)
    {
        int counts = 2;
        for (int j = i; j < ALPHA_LENGHT; j++)
        {
            if (convertupper(userCode[i]) == convertupper(userCode[j]))
            {
                counts--;
            }
            if (counts <= 0)
            {
                printf("\033[1;32m \bUsage: ./subsitution key(26 Characters) mode\n \033[0m");
                printf("\033[0;31m\bErrorCode: 240\n\033[0;33m \bConflicting Alphabets\n\033[0m");
                return 1;
            }
        }
    }
}

int strlen(char array[])
{
    int i = 0;
    int lenght = 0;
    while (array[i] != '\0')
    {
        lenght++;
        i++;
    }
    return lenght;
}

int isalpha(int intager)
{
    if (intager <= 90 && intager >= 65 || intager <= 122 && intager >= 97)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char convertupper(int letter)
{
    if (letter <= 122 && letter >= 97)
    {
        letter -= 32;
    }
    return letter;
}
char convertlower(int letter)
{
    if (letter <= 90 && letter >= 65)
    {
        letter += 32;
    }
    return letter;
}
