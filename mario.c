#import <stdio.h>
#import <unistd.h>
#import <cs50.h>

int promtforheight();
void makeblocks();

int main(void){
    makeblocks();
}

void makeblocks(){
    int h = promtforheight();
    if (h > 8 || h < 1){
        printf("\033[1;31m");
        printf("!!! Please enter Number between (1 to 8) !!!\n");
        printf("\033[0m");
        sleep(1);
        makeblocks();
    }else{
        for(int i = 0; i < h; i++){
            // make first pyramid
            for(int j = h; j > i+1; j--){
                printf(" ");
            }
            for(int j = 0; j <= i; j++){
                printf("#");
            }

            // Add space b/w pyramids
            printf("  ");

            // make second pyramid
            for(int j = 0; j <= i; j++){
                printf("#");
            }
            printf("\n");
        }
    }
}

int promtforheight(){
    int height = get_int("What will be the height of blocks? (B/W 1 to 8)\n");
    return height;
}