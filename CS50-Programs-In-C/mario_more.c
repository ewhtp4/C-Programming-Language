/**
Assigment : Mario more
Course name : CS50
By: Slavko Mihajlovic
Year: 2020
**/

#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int height;
    //Input validation
    do 
    {
        height = get_int("Whats the height of the piramid?: ");
    }
    while (height < 1 || height > 8);
    //Determining rows
    for (int row = 0; row < height; row++)
    {
        //Print left hend spaces
        for (int space = 0; space < height - row - 1 ; space++)
        {
            printf(" ");
        }
        //Print left hand hash
        for (int lhash = height - row ; lhash <= height; lhash++) 
        {
            printf("#");
        }
        //Print space between
        printf("  ");
        //Print right hand hash
        for (int rhash = height - row; rhash <= height; rhash++) 
        {
            printf("#");
        }
        //New line
        printf("\n");
    }

}
