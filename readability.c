#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

float average(int number,int numOfWords);
void digitcounter(char *text,int textlen);

int letters = 0,words = 1,sentences = 0;
float Grade;

int main(void){
    // A string is actually one-dimensional array of characters in C language
    char *text = get_string("Text: ");
    int textlen = strlen(text);
    // To count how many letters, words and sentences there are in text.
    digitcounter(text,textlen);

    // Calculates Grade
    Grade = 0.0588 * average(letters,words) - 0.296 * average(sentences,words) - 15.8;

    printf("%i letters & %i Words & %i Sentences\n",letters,words,sentences);
    // printf("%f\n",average(letters,words));
    // printf("%f\n",average(sentences,words));
    if (round(Grade) >= 16){
        printf("Grade 16+\n");
    }else if (round(Grade) < 1){
        printf("Before Grade 1\n");
    }else{
        printf("Grade %.lf\n",round(Grade));
    }
}

// Finds avg of letter or sentences per 100 words
float average(int number,int numOfWords){
    float avg;
    // Atleat 1 divisor has to be float in order to output decimal
    return avg = (float)number / numOfWords * 100;
}

void digitcounter(char *text,int textlen){
    char ch[textlen + 1];

    for (int i = 0; i < textlen; i++){
        ch[i] = text[i];
        // Counts num of letters
        if (isalpha(ch[i])){
            letters++;
        // Counts num of words
        }else if (isspace(ch[i])){
            words++;
            // If there is two spaces together then it decrements num of words
            if (isspace(ch[i-1])){
                words--;
            }
        }else if (ch[i] == '.' || ch[i] == '?' || ch[i] == '!'){ //
            // Increments sentences even if its not actually a sentence
            sentences++;

            // If there's two or three dots together (..) or (...) it counts it as one sentence
            if (ch[i-1] == '.'){
                sentences--;
            } // If character is "!" then it will check the following conditions to make sure that its end of a sentence.
            else if (ch[i] == '!'){
                // Basically if there's two or more than two Spaces(" ") or Words before '!'
                // then it will likely be a confirm sentence atleast in this case
                int wordsBeforeEx = 0;

                // checks every character before "!" and counts number of words before it.
                for (int j = 0; j < i + 1; j++){
                    // if it encounter's a line breaker ('.' or ',') it wil break the loop
                    if (ch[i-j] == '.' || ch[i-j] == ',' || ch[i-j] == '?'){
                        break;
                    }
                    // it encounter's a space(' ') then counts it as word.
                    else if(ch[i-j] == ' '){
                        wordsBeforeEx++;
                    }
                }// checks if the words before '!' < 2 then it decrements the num of sentence incremented just before
                if (wordsBeforeEx < 2){
                    sentences--;
                }
            }
        }
    }
    // If there is 0 sentences then there should be 1 for the algorithm to work correctly
    if (sentences == 0){
        sentences++;
    }
}