/**
 * Name: substitution.c
 * --Monoalphabetic Cipher Program
 * Course name: CS50
 * Year: 2020
 * By: Slavko Mihajlovic
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

//Declaring Encrypt function
static string Encrypt(string plainText, string key);
//Checking for a valid key function 
bool is_valid_key(string key)
{
    //For loop checking if there is any characters duplication
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
        //Checking if all characters are alphabetic and if thre is 26 of them
        if (!isalpha(key[i]) || strlen(key) != 26)
        {
            return false;
        }
    }
    return true;
}
int main(int argc, string args[])
{
    string key = args[1];
    //Checking if there is a key and is it valid
    if (argc != 2 || !is_valid_key(args[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Prompt the user for text
    string plainText = get_string("plaintext: ");
    //Declaring the ciphered text varible by calling the Encrypt function
    string cipherText = Encrypt(plainText, key);
    //Printing the ciphered text
    printf("ciphertext: %s", cipherText);
    printf("\n");
    return 0;
}
//Encryting function
static string Encrypt(string plainText, string key)
{
    //Declaring and allocating memory for a cypherd variable
    char *cyphred = malloc(strlen(plainText) * sizeof(*cyphred));
    for (int i = 0; i < strlen(plainText); i++)
    {
        //In case of upper case characters 
        if (isupper(plainText[i]))
        {
            int index = plainText[i] - 65;
            cyphred[i] = putchar(toupper(key[index]));//Must make sure to cast the key in to upper case 
        }
        //In case of lower case characters 
        if (islower(plainText[i]))
        {
            int index = plainText[i] - 97;
            cyphred[i] = putchar(tolower(key[index]));;//Must make sure to cast the key in to lower case 
        }
        //In case of non-alphabetic characters
        if (!isalpha(plainText[i]))
        {
            cyphred[i] = plainText[i];
        }
    }
    return cyphred;
}



