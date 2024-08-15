
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int raw = 0; raw < height; raw++) // image raw
    {
        for (int column = 0; column < width; column++) // image column
        {
            int R = image[raw][column].rgbtRed;
            int G = image[raw][column].rgbtGreen;
            int B = image[raw][column].rgbtBlue;
            int average = round((R + G + B) / 3.0);
            image[raw][column].rgbtRed = image[raw][column].rgbtGreen =
                image[raw][column].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int raw = 0; raw < height; raw++) // image raw
    {
        for (int column = 0; column < width; column++) // image column
        {
            int R = image[raw][column].rgbtRed;
            int G = image[raw][column].rgbtGreen;
            int B = image[raw][column].rgbtBlue;
            int sepiared = round((0.393 * R) + (0.769 * G) + (0.189 * B));
            if (sepiared > 255)
            {
                sepiared = 255;
            }
            int sepiagreen = round((0.349 * R) + (0.686 * G) + (0.168 * B));
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            int sepiablue = round((0.272 * R) + (0.534 * G) + (0.131 * B));
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }
            image[raw][column].rgbtRed = sepiared;
            image[raw][column].rgbtGreen = sepiagreen;
            image[raw][column].rgbtBlue = sepiablue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int raw = 0; raw < height; raw++)
    {
        if (width % 2 == 0)
        {
            for (int column = 0; column < width / 2; column++)
            {
                RGBTRIPLE temp[height][width];
                temp[raw][column] = image[raw][column];
                image[raw][column] = image[raw][width - (column + 1)];
                image[raw][width - (column + 1)] = temp[raw][column];
            }
        }
        else if (width % 2 != 0)
        {
            for (int column = 0; column < (width - 1) / 2; column++)
            {
                RGBTRIPLE temp[height][width];
                temp[raw][column] = image[raw][column];
                image[raw][column] = image[raw][width - (column + 1)];
                image[raw][width - (column + 1)] = temp[raw][column];
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // looping on every pixel
    for (int raw = 0; raw < height; raw++)
    {
        for (int column = 0; column < width; column++)
        {
            // intiate variables to use it as contener
            int totalred = 0;
            int totalgreen = 0;
            int totalblue = 0;
            float counter = 0.00;

            // every pixel surrounded by 3*3 array
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    int currenti = raw + i;
                    int currentj = column + j;

                    // check if pixel in any edge or corner
                    if (currenti < 0 || currenti > (height - 1) || currentj < 0 ||
                        currentj > (width - 1))
                    {
                        continue;
                    }

                    totalred += image[currenti][currentj].rgbtRed;
                    totalgreen += image[currenti][currentj].rgbtGreen;
                    totalblue += image[currenti][currentj].rgbtBlue;
                    counter++;
                }
            }

            // averge for each color channel
            copy[raw][column].rgbtRed = round(totalred / counter);
            copy[raw][column].rgbtGreen = round(totalgreen / counter);
            copy[raw][column].rgbtBlue = round(totalblue / counter);
            // putting all the past in copy array
        }
    }

    // looping on copy array and assign all the pixels one by one to the main image array
    for (int raw = 0; raw < height; raw++)
    {
        for (int column = 0; column < width; column++)
        {
            image[raw][column].rgbtRed = copy[raw][column].rgbtRed;
            image[raw][column].rgbtGreen = copy[raw][column].rgbtGreen;
            image[raw][column].rgbtBlue = copy[raw][column].rgbtBlue;
        }
    }
    return;
}

/*
    RGBTRIPLE copy[height][width];
    for (int raw = 0; raw < height; raw++)
    {
        for (int column = 0; column < width; column++)
        {
            int newr, newg, newb;
            copy[raw][column] = image[raw][column];
            newr = round((copy[raw - 1][column - 1].rgbtRed + copy[raw - 1][column].rgbtRed +
   copy[raw - 1][column + 1].rgbtRed + copy[raw][column - 1].rgbtRed + copy[raw][column].rgbtRed +
   copy[raw][column + 1].rgbtRed + copy[raw + 1][column - 1].rgbtRed + copy[raw + 1][column].rgbtRed
   + copy[raw + 1][column + 1].rgbtRed) / 9.0); newg = round((copy[raw - 1][column - 1].rgbtGreen +
   copy[raw - 1][column].rgbtGreen + copy[raw - 1][column + 1].rgbtGreen + copy[raw][column -
   1].rgbtGreen + copy[raw][column].rgbtGreen + copy[raw][column + 1].rgbtGreen + copy[raw +
   1][column - 1].rgbtGreen + copy[raw + 1][column].rgbtGreen + copy[raw + 1][column + 1].rgbtGreen)
   / 9.0); newb = round((copy[raw - 1][column - 1].rgbtBlue + copy[raw - 1][column].rgbtBlue +
   copy[raw - 1][column + 1].rgbtBlue + copy[raw][column - 1].rgbtBlue + copy[raw][column].rgbtBlue
   + copy[raw][column + 1].rgbtBlue + copy[raw + 1][column - 1].rgbtBlue + copy[raw +
   1][column].rgbtBlue + copy[raw + 1][column + 1].rgbtBlue) / 9.0); image[raw][column].rgbtRed =
   newr; image[raw][column].rgbtGreen = newg; image[raw][column].rgbtBlue = newb;
        }
    }
*/

// leh el blur dh ma nf3sh fe el check m3 eno tl3 el output
// leh lazm el counter float
// leh el style 0.99 but it looks good
