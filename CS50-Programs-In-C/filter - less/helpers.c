/*====================================================================================================================
 |   Assignment:  Problem Set 4 - Filter/Less
 |       Author:  Slavko Mihajlovic
 |     Language:  C
 |   To Compile:  Run the make file
 |
 |        Class:  CS50: Introduction to Computer Science -Harvard University 
 |   Instructor:  David J. Malan
 |     Due Date:  April 2020
 |
 +--------------------------------------------------------------------------------------------------------------------
 |
 |  Description:  Applies Grayscale,Sapia,Reflect and Blure Filter to BMP 
 |                images from the terminal.
 |        Input:  ./filter [filter option: -g,-s,-r,-b] [name of file] [name of new file]
 |               
 |       Output:  A new image file with the applied filter
 |
 |    Algorithm:  Greyscale, Sapia, Reflect, Blure
 |      
 |
 |   Required Features Not Included:  No requirmant, the program does not aplly any other filters.
 |      
 |
 |   Known Bugs:  N/A
 |      
 |
 *====================================================================================================================*/
#include "helpers.h"
#include <math.h>

/*===================================================================================================================== 
| Convert image to grayscale
 *====================================================================================================================*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            //Applying the Grayscale algorithm
            int grey = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;
        }
    }    
    return;
}

/*====================================================================================================================== 
| Convert image to sepia
 *=====================================================================================================================*/
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Applying the Sapia algorithm
            int sepiaBlue = round((0.272 * (float)image[i][j].rgbtRed)
                                  + (0.534 * (float)image[i][j].rgbtGreen)
                                  + (0.131 * (float)image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * (float)image[i][j].rgbtRed)
                                   + (0.686 * (float)image[i][j].rgbtGreen)
                                   + (0.168 * (float)image[i][j].rgbtBlue)); 
            int sepiaRed = round((0.393 * (float)image[i][j].rgbtRed)
                                 + (0.769 * (float)image[i][j].rgbtGreen)
                                 + (0.189 * (float)image[i][j].rgbtBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }                                                          
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }    
    return;
}

/*======================================================================================================================= 
| Reflect image horizontally
 *======================================================================================================================*/
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, w = round((float) width / 2); j < w; j++) 
        {
            //Applying the Reflect algorithm
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - j - 1)];
            image[i][(width - j - 1)] = temp;
        }
    }    
    return;
}

/*======================================================================================================================== 
| Blur image
 *=======================================================================================================================*/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    //Temorary array
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            //Sums up the values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            //Averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    //Copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
    return;
}

