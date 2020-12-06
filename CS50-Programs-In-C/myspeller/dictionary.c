/*====================================================================================================================
 |   Assignment:  Problem Set 5 - Speller -Hash
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
 |  Description:  Implements a dictionary's functionality
 |
 |        Input:  (example)./speller texts/lalaland.txt
 |               
 |       Output:  A terminal output stateing the number of misspelled words in the gven text
 |
 |    Algorithm:  N/A
 |      
 |
 |   Required Features Not Included:  No requirmant.
 |      
 |
 |   Known Bugs:  N/A
 |      
 |
 *====================================================================================================================*/

#include <stdio.h>
#include <stdbool.h>
#include "cs50.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 1985

//Sets up pointer for linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Hash prototype
unsigned long hash(char *str);

//Set pointer to hash table
node *hashtable[HASHTABLE_SIZE];

//Counter for the words in size function
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Convert word to lowercase
    int n = strlen(word);
    char copy[n + 1];

    //Add null terminator to end of the lower case word
    copy[n] = '\0';

    for (int i = 0; i < n; i++)
    {
        copy[i] = tolower(word[i]);
    }

    //Pass lower case word to hash function to get index
    int index = hash(copy) % HASHTABLE_SIZE;

    //Set to the head of the linked list
    node *head = hashtable[index];

    if (head != NULL)
    {
        //Points the cursor to the same location
        node *cursor = head;

        //Traverse the linked list
        while (cursor != NULL)
        {
            if (strcmp(copy, cursor->word) == 0)
            {
                //Return true if word matches the word in our dictionary
                return true;
            }

            //Else move cursor to the next linked list
            cursor = cursor->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    //Open dictionary to read only
    FILE *file = fopen(dictionary, "r");

    //Check to seee if dictionary is empty
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", dictionary);
        return false;
    }

    // set a buffer to store an output word
    char buffer[LENGTH + 1];

    int n = LENGTH + 2;

    // loop through the dictionary until a null character
    while (fgets(buffer, n, file) != NULL)
    {

        // add null terminator to the end of the word
        buffer[strlen(buffer) - 1] = '\0';
        //hash the word
        int index = hash(buffer) % HASHTABLE_SIZE;
        // create a temporary node
        node *temp = malloc(sizeof(node));
        //Test to see if node is null
        if (temp == NULL)
        {
            fclose(file);
            return false;
        }    
        //Move to the next node in the list
        strcpy(temp -> word, buffer);
        temp -> next = hashtable[index];

        hashtable[index] = temp;
        word_count++;
    }


    // close the file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // for each node in the hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // check the table for a node at that index
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            // create a temporary node
            node *temp = cursor;
            cursor = cursor -> next;

            // free the current node
            free(temp);
        }
    }
    return true;
}
//Hash table that I got from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}


