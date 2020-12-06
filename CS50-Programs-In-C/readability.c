/**
 * Program name: Readability
 * Purpose: Checks the readibility grade of the given text
 * Author: Slavko Mihajlovic
 * Year: 2020
 * Course name: CS50
 * */

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Please input your text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;
    int length = strlen(text);

    if (isalnum(text[0]))
    {
        words = 1;
    }

    for (int i = 0; i < length; i++)
    {
        //Counting letters
        if (isalpha(text[i]))
        {
            letters++;
        }
        //Counting words
        else if (isspace(text[i]))
        {
            words++;
        }
        //Counting sentences
        else if (text[i] == '.' || text[i] == ',' || text[i] == ';' || text[i] == '!' || text[i] == '?' )
        {
            sentences++;
        }
        //Coleman-Lien Index
        float l = letters / words * 100;
        float s = sentences / words * 100;
        float index = 0.0588 * l - 0.296 * s - 15.8;
        int grade = round(index);

        //Grading
        if (grade >= 1 || grade <= 16)
        {
            printf("Grade %i\n", grade);
        }
        else if (grade <)
        {
            printf("Before Grade 1.\n");
        }
        else 
        {
            printf("Before 16+\n");
        }
    }
}
