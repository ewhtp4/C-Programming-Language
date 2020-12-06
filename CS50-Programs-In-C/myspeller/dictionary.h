// Declares a dictionary's functionality

#ifndef DICTIONARY_H  //File guards begining
#define DICTIONARY_H // File guards protect the body of the heder file
                     //From being included more then once

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
//Hash table that I got from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(char *str);

#endif // DICTIONARY_H //end of the File guard
