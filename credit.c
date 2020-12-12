#import <stdio.h>
// used for get_long
#import <cs50.h>

int countdigit(long num);
int verifycard(long cardnum);
void cardidentify(long cardnum);

int main(void){
    long creditcardnum = get_long("What's your credit card number?\n");
    if (countdigit(creditcardnum) >= 13 && countdigit(creditcardnum) < 17){
        // verifies card
        if (verifycard(creditcardnum) == 0){
            printf("This is a Verified ");
            // Identify that which card company it belongs to ---- Only if its verified
            cardidentify(creditcardnum);
        }else{
            // if not verified
            printf("Not Verified\n");
        }
    }else{
        printf("Please enter a valid Card Number!\n");
    }
}

int verifycard(long cardnum){
    int finalvalue = 0, currentvalue = 0, fProduct1 = 0, fProduct2 = 0;
    long product1 = cardnum, product2 = cardnum;

    //  Processes first part of algorithm.
    while(product1 != 0){
        int digit;

        // selects every 2nd number of number in a different pattern
        product1 = product1 / 10;
        digit = product1 % 10;
        product1 = product1 / 10;

        currentvalue = digit * 2;

        int valuelenght = countdigit(currentvalue);

        // converts product in to digits
        for (int i = 0; i <= valuelenght; i++){
            digit = currentvalue % 10;
            fProduct1 = fProduct1 + digit;
            currentvalue = currentvalue / 10;
        }
    }

    //  Processes second part of algorithm.
    while(product2 != 0){
        int digit;

    // selects every 2nd number of number
        digit = product2 % 10;
        product2 = product2 / 100;

        fProduct2 = fProduct2 + digit;
    }

    finalvalue = fProduct1 + fProduct2;

    if ((finalvalue % 10) == 0){
        return 0;
    }else{
        return 1;
    }
}

// identify name
void cardidentify(long cardnum){

    int digits = countdigit(cardnum);

    if (digits == 15){
    long num = cardnum;

        do{
            num = num/10;
        }while(num > 99);

        if (num == 34 || num == 37){
            printf("American Express\n");
        }else{
        printf("but unidentified card\n");
        }
    }else if (digits >= 13 && digits <= 16){
    long num = cardnum;

        do{
            num = num/10;
        }while(num > 99);

        if (num == 51 || num == 52 || num == 53 || num == 54 || num == 55){
            printf("Master Card\n");
        }else{
            do{
                num = num/10;
            }while(num > 9);

            if (num == 4){
                printf("Visa Card\n");
            }else{
                printf("but unidentified card\n");
            }
        }
    }
}

// count digits in number
int countdigit(long num){
    int digits = 0;
    do{
        num = num / 10;
        digits++;
    }while(num != 0);
    return digits;
}
