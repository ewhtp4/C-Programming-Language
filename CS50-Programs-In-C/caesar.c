/**
 * name: caesar.c
 * Course name: CS50
 * Year: 2020
 * By: Slavko Mihajlovic
 * */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    // Counts the number of arguements in the command line
    if (argc == 2)
    {
        // Converts index 1 of argv to an int
        int k = atoi(argv[1]);
        // Stores a boolean to use as an off switch if we dectect a bad input
        bool isKeyValid = true;
        // Stores the length of the the string in index 1 of the argv array
        int len = strlen(argv[1]);    
        // Loop that checks each digit to see if it's a number
        for (int i = 0; i < len; i++)
        {
            // If isdigit detects a non-digit it'll set our stored bool to false and end the loop
            if (isdigit(argv[1][i]) == false)
            {
                isKeyValid = false;
                i = len;
            }
        }
        // If the loop successfully finishes and the isKeyValid bool stays true then we have a valid key and can proceed
        if (isKeyValid)
        {   
            string code = get_string("plaintext: ");
            printf("ciphertext: ");
            for (int i = 0; i < strlen(code); i++)
            {
                for (int c = 0, n = strlen(code); c < n; c++)
                {
                    //check if the letter is uppercase or lowercase then convert
                    if islower(code[c])
                    {
                        printf("%c", (((code[c] + k) - 97) % 26) + 97);
                    }    
                    else if isupper(code[c])
                    {
                        printf("%c", (((code[c] + k) - 65) % 26) + 65);
                    }
                    //if neither then just print whatever it is
                    else
                    {
                        printf("%c", code[c]);
                    }    
                }
                printf("\n");
                return 0;
            }                        
        }
            
        // If we detected an unusable key we ask for a proper key
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        
    }
    // If too many arguements were entered then we ask for a proper key
    else if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }

}