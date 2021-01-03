#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("Blue:%i-Green:%i-Red:%i\n",image[i][j].rgbtBlue ,image[i][j].rgbtGreen, image[i][j].rgbtRed);
            int sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int average = sum /3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    printf("\033[0;32mDone!\n\033[0m");
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue);
            int sepiaGreen = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue);
            int sepiaBlue = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue);
            (sepiaRed > 255) && (sepiaRed = 255); (sepiaRed < 0) && (sepiaRed = 0);
            (sepiaGreen > 255) && (sepiaGreen = 255); (sepiaGreen < 0) && (sepiaGreen = 0);
            (sepiaBlue > 255) && (sepiaBlue = 255); (sepiaBlue < 0) && (sepiaBlue = 0);
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    printf("\033[0;32mDone!\n\033[0m");
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int substract = 1;
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tempPixel;

            tempPixel.rgbtBlue = image[i][j].rgbtBlue;
            tempPixel.rgbtGreen = image[i][j].rgbtGreen;
            tempPixel.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - substract].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - substract].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - substract].rgbtRed;

            image[i][width - substract].rgbtBlue = tempPixel.rgbtBlue;
            image[i][width - substract].rgbtGreen = tempPixel.rgbtGreen;
            image[i][width - substract].rgbtRed = tempPixel.rgbtRed;
            substract++;
        }
    }
    printf("\033[0;32mDone!\n\033[0m");
    return;
}

// mirror effect
void mirror(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int substract = 1;
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE tempPixel;

            tempPixel.rgbtBlue = image[i][j].rgbtBlue;
            tempPixel.rgbtGreen = image[i][j].rgbtGreen;
            tempPixel.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - substract].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - substract].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - substract].rgbtRed;
            substract++;
        }
    }
    printf("\033[0;32mDone!\n\033[0m");
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int ammount;
    printf("Ammount: ");
    scanf("%i",&ammount);
    int delay = height / 10;

    for (int i = 0; i < height; i++)
    {
        int hI = i;
        delay++;
        if (delay >= height / 10)
        {
            int todivide = height / 100;
            int percent = i / todivide;
            printf("\033[1;32mPercent Completed: %i\033[0m\n",percent);
            delay = 0;
        }

        for (int j = 0; j < width; j++)
        {
            int wI = j;

            int sum[3] = {0,0,0};
            int quantity = 0;
            for (int h = hI - ammount; h <= hI + ammount; h++)
            {
                if (h >= 0 && h < height)
                {
                    for (int w = wI - ammount; w <= wI + ammount; w++)
                    {
                        if (w >= 0 && w < width)
                        {
                            sum[0] += image[h][w].rgbtBlue;
                            sum[1] += image[h][w].rgbtGreen;
                            sum[2] += image[h][w].rgbtRed;
                            quantity++;
                        }
                    }
                }
            }
            image[i][j].rgbtBlue = sum[0] / quantity;
            image[i][j].rgbtGreen = sum[1] / quantity;
            image[i][j].rgbtRed = sum[2] / quantity;
        }
    }
    printf("\033[0;32mDone!\n\033[0m");
  return;
}


// Detect edges
int GxValue(int colorValue,int Gr,int Gc);
int GyValue(int colorValue,int Gr,int Gc);
int sumAdder(int sum1,int sum2);
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageDupli[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageDupli[i][j].rgbtRed = image[i][j].rgbtRed;
            imageDupli[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageDupli[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        int hI = i;
        for (int j = 0; j < width; j++)
        {
            int wI = j;

            int sumRedGx = 0,sumBlueGx = 0,sumGreenGx = 0;
            int sumRedGy = 0,sumBlueGy = 0,sumGreenGy = 0;
            int finalValue;

            int Gc = 0;
            for (int h = hI - 1; h <= hI + 1; h++)
            {
                int Gr = 0;
                if (h >= 0 && h < height)
                {
                    for (int w = wI - 1; w <= wI + 1; w++)
                    {
                        if (w >= 0 && w < width)
                        {
                            sumRedGx += GxValue(imageDupli[h][w].rgbtRed,Gr,Gc);
                            sumRedGy += GyValue(imageDupli[h][w].rgbtRed,Gr,Gc);

                            sumBlueGx += GxValue(imageDupli[h][w].rgbtBlue,Gr,Gc);
                            sumBlueGy += GyValue(imageDupli[h][w].rgbtBlue,Gr,Gc);

                            sumGreenGx += GxValue(imageDupli[h][w].rgbtGreen,Gr,Gc);
                            sumGreenGy += GyValue(imageDupli[h][w].rgbtGreen,Gr,Gc);
                        }
                        Gr++;
                    }
                }
                Gc++;
            }
            finalValue = sumAdder(sumRedGy,sumRedGx);
            image[hI][wI].rgbtRed = finalValue;

            finalValue = sumAdder(sumGreenGy,sumGreenGx);
            image[hI][wI].rgbtGreen = finalValue;

            finalValue = sumAdder(sumBlueGy,sumBlueGx);
            image[hI][wI].rgbtBlue = finalValue;
        }
    }
    printf("\033[0;32mDone!\n\033[0m");
    return;
}

int GxValue(int colorValue,int Gr,int Gc)
{
    int Gx[3][3];
    Gx[0][0] = -1; Gx[0][1] = 0; Gx[0][2] = 1;
    Gx[1][0] = -2; Gx[1][1] = 0; Gx[1][2] = 2;
    Gx[2][0] = -1; Gx[2][1] = 0; Gx[2][2] = 1;

    colorValue = colorValue * Gx[Gc][Gr];
    return colorValue;
}
int GyValue(int colorValue,int Gr,int Gc)
{
    int Gy[3][3];
    Gy[0][0] = -1; Gy[0][1] = -2; Gy[0][2] = -1;
    Gy[1][0] = 0; Gy[1][1] = 0; Gy[1][2] = 0;
    Gy[2][0] = 1; Gy[2][1] = 2; Gy[2][2] = 1;

    colorValue = colorValue * Gy[Gc][Gr];
    return colorValue;
}

int sumAdder(int sum1,int sum2)
{
    sum1 = sum1*sum1;
    sum2 = sum2*sum2;
    int sumAdded = sum1 + sum2;
    sumAdded = sqrt(sumAdded);

    if (sumAdded > 255)
    {
        sumAdded = 255;
    }
    else if (sumAdded < 0)
    {
        sumAdded = 0;
    }
    return sumAdded;
}




