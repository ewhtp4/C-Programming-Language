/*====================================================================================================================
 |      Program:  Pachy V1.0
 |       Author:  Slavko Mihajlovic
 |     Language:  C
 |   To Compile:  Run the make file
 |
 |       
 |   
 |         Date:  April 2020
 |
 +--------------------------------------------------------------------------------------------------------------------
 |
 |  Description:  Install and brings up a complete Apache2 Server with the entire configuration done per 
                  users specifications.
 |        Input:  Follow ineterface
 |               
 |       Output:  N/A
 |
 |    Algorithm:  N/A
 |      
 |
 |   Required Features Not Included:  No requirmant
 |      
 |
 |   Known Bugs:  N/A
 |      
 |
 *====================================================================================================================*/
#include <sys/utsname.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define NUMBER_CHECKS 5
#define MAX_STRING_SIZE 40
#define MAX_MATCHES 1 
void match(regex_t *pexp, char *sz, int i);
/*===================================================================================================================== 
| Constants Pool
 *====================================================================================================================*/
const char *vcommand[NUMBER_CHECKS] = { "apache2 -version | awk '{print $3}'",
                                        "named -v",
                                        "mysql -V",
                                        "php --version",
                                        "perl -v |sed -n 2p",
                                        };
const char *pmessage[NUMBER_CHECKS] = { "Apache2 Installed",
                                        "Bind Installed",
                                        "MySQL Installed",
                                        "PHP Installed",
                                        "Pirl Installed"};                                               
const char *nmessage[NUMBER_CHECKS] = { "Apache2 Missing",
                                        "Bind Missing",
                                        "MySQL Missing",
                                        "PHP Missing",
                                        "Pirl Missing"};
const char *testtext[NUMBER_CHECKS] = { "Apache/[2-9].[0-9].[0-9][0-9]",
                                        "BIND [0-9].[0-9][0-9].[0-9]",
                                        "mysql  Ver [0-9][0-9].[0-9][0-9]",
                                        "PHP [7-9].[0-9].[0-9][0-9]",
                                        "This is perl 5,"};
const char *versiont[NUMBER_CHECKS] = { "apache2 -version |sed -n 1p | awk '{print $3}'| cut -d '/' -f2",
                                        "named -v |sed -n 1p | awk '{print $2}'| cut -d '-' -f1",
                                        "mysql -V | awk '{print $3}'",
                                        "php --version |sed -n 1p | awk '{print $2}'| cut -d '-' -f1",
                                        "perl -v |sed -n 2p | awk '{print $9}' | cut -d 'v' -f2 | cut -d ')' -f1"};
                                        
  typedef struct
{
    char *name;
    char *install;
    bool present;
    bool upgradable;
}
elemant;

int main(int argc, char **argv) {
    system("clear");
/*===================================================================================================================== 
| Banner
*====================================================================================================================*/
    char *tfiglet = "FIGlet Copyright (C) 1991-2012 Glenn Chappell, Ian Chai, John Cowan,\n";
    FILE *figlet = ((void*)0);
    char bufferf[1024];
    if (!(figlet = popen("figlet -v", "r"))) {
        perror("popen");
        return 1;
        }
        fgets(bufferf, sizeof(bufferf), figlet);
            if(strcmp(tfiglet, bufferf) != 0){
                system("sudo apt install figlet toilet");
            }
            printf("\033[0;33m");
            system("figlet -f slant 'Pachy'");
            printf("v 1.1\n\n"); 
            printf("\033[0;34m");
            printf("Detected:\n");
            system("hostnamectl |sed -n 6p");
            printf("\033[0m");
            printf("\n\n\a");
    pclose(figlet);
/*===================================================================================================================== 
| Cheking for installed software
*====================================================================================================================*/  
    int rv;
    int rv2;
	int i;
    FILE *shellpipe = ((void*)0);
    char buffer[1024];
	regex_t exp;
    for (int i = 0; i < NUMBER_CHECKS; i++)
    {
        rv = regcomp(&exp, testtext[i], REG_EXTENDED);
        if (!(shellpipe = popen(vcommand[i], "r"))) {
        perror("popen");
        return 1;
        }
        fgets(buffer, sizeof(buffer), shellpipe);
            match(&exp, buffer, i);
    }
    pclose(shellpipe);
	regfree(&exp);
/*===================================================================================================================== 
| Menu
*====================================================================================================================*/
          
    return 0;
}
/*===================================================================================================================== 
| Software Matching Function
*====================================================================================================================*/  
void match(regex_t *pexp, char *sz, int i) {    
	regmatch_t matches[MAX_MATCHES]; 
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		printf("\033[0;32m");
        printf("Version %s\n", pmessage[i]);
        system(versiont[i]);
        printf("\033[0m");
        printf("-----------------------------------------------------------\n");
	} 
    else {
		printf("\033[1;31m");
        printf("%s\n", nmessage[i]);
        printf("\033[0m");
        printf("-----------------------------------------------------------\n");
	}
}
  