#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through image pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE *pixel = &image[h][w];

            // average of all three
            BYTE grayscale_value = round((float) (pixel->rgbtRed + pixel->rgbtGreen + pixel->rgbtBlue) / 3);

            // Apply
            pixel->rgbtRed = grayscale_value;
            pixel->rgbtGreen = grayscale_value;
            pixel->rgbtBlue = grayscale_value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through image pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // RGBTRIPLE *pixel = &image[h][w];
            int originalRed = image[h][w].rgbtRed;
            int originalGreen = image[h][w].rgbtGreen;
            int originalBlue = image[h][w].rgbtBlue;

            // sepia BYTE values
            int sepiaRed = round((float) (.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int sepiaGreen = round((float) (.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int sepiaBlue = round((float) (.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            // capping values
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            // Apply
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through image pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            // get mirror pixel for swap
            RGBTRIPLE *mirror_pixel = &image[i][width - j - 1];

            // swap
            RGBTRIPLE temp = *mirror_pixel;
            *mirror_pixel = *pixel;
            *pixel = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image[heigh][width] into copy[height][width]
    RGBTRIPLE copy[height][width];

    // Create a deep copy of the image array
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            copy[i][y] = image[i][y];
        }
    }

    // loop through image pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int count = 0;   

            // focal point
            RGBTRIPLE *pixel = &copy[i][j];
            sumRed += pixel->rgbtRed;
            sumBlue += pixel->rgbtBlue;
            sumGreen += pixel->rgbtGreen;
            
            // nested loops to iterate through the neighboring pixels
            for (int di = -1; di < 2; di++)
            {
                for (int dj = -1; dj < 2; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        count++;
                    }
                }
            }

            // modify focal pixel
            image[i][j].rgbtBlue = round((float) sumBlue / count);
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
        }
    }
    return;
}