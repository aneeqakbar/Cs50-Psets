#include <stdio.h>
#include <unistd.h>
#include <cs50.h>
#include <string.h>

void questions();

int main(void){
    questions();
}

void questions(){
    string name = get_string("Whats your name?.\n");
    printf("Hello %s, Hope that you'r fine.\n", name);
    sleep(1);
    printf("So %s, We need some information from you for some reason.\nSo, Can you give us some information about you? (yes/no)\n", name);
    string confirm = get_string("");
    if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "y") == 0){
        int age = get_int("Please let me know your age?\n");
        string profession = get_string("Kindly tell me your profession.\n");

       for (int loop = 0; loop < 2; loop++){
            for (int each = 0; each < 4; each++) {
                printf("\rProcessing%.*s   \b\b\b", each, "...");
                sleep(1);
            }
        }
        printf("\n");

        printf("So, You are %s and you'r %i years old currently working as a %s\n", name, age, profession);
    }else{
        printf("Ok %s, No problem we appreciate your time.\n", name);
    }
}