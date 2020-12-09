#import <stdio.h>
#import <cs50.h>
#import <math.h>

void printcoins(char *name,int coin);

int main(void){
    float dollars;
    int cents;

    int coins = 0;

    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    do{
        dollars = get_float("Enter ammount we owe: $");
        cents = round(dollars * 100);
        if(dollars <= 0){
            printf("\033[1;31m");
            printf("Dollars owed should be more than 0.00 to proceed\n");
            printf("\033[0m");
        }
    }while(dollars <= 0);

    printf("Total cents are %i\n", cents);

    // 1 quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).

    do{
        if(cents >= 25){
            cents -= 25;
            quarters += 1;
            coins++;
        }
        else if(cents >= 10 && cents < 25){
            cents -= 10;
            dimes += 1;
            coins++;
        }
        else if(cents >= 5 && cents < 10){
            cents -= 5;
            nickels += 1;
            coins++;
        }
        else if(cents >= 1 && cents < 5){
            cents -= 1;
            pennies += 1;
            coins++;
        }
    }while(cents > 0);

    // printf("Change to return: %i quarters, %i dimes, %i nickels and %i pennies\n", quarters, dimes, nickels, pennies);
    printf("Coins to return: %i\n",coins);

    printcoins("Quarters",quarters); printcoins("Dimes",dimes); printcoins("Nickels",nickels); printcoins("Pennies",pennies);

    printf("\nCents left owed: %i\n",cents);
}

void printcoins(char *name , int coin){
    if (coin != 0){
        printf("%s:%i ",name,coin);
    }
}




