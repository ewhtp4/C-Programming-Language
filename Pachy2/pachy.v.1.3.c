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
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pachy.h"
#define NUMBER_CHECKS 5
#define MAX_STRING_SIZE 40
#define MAX_MATCHES 1 
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
    bool present;
    bool upgradable;
} elemant;       
elemant elemants[5] = {{false, false},
                       {false, false},
                       {false, false},
                       {false, false},
                       {false, false}};

int apache2();
int	menu(void);
void match(regex_t *pexp, char *sz, int i);
void apachinstall(regex_t *pexp, char *sz, int i);
int found = 0;
int main(int argc, char **argv) {
/*===================================================================================================================== 
| Banner
*====================================================================================================================*/
	system("chmod +x `ls /apachesh/*.sh`");
    system("clear");
    printf("\033[0;33m");
    printf("::::::::::. :::.       .,-:::::   ::   .:.-:.     ::-.\n");
	printf(" `;;;```.;;;;;`;;    ,;;;'````'  ,;;   ;;,';;.   ;;;;'\n");
	printf("  `]]nnn]]',[[ '[[,  [[[        ,[[[,,,[[[  '[[,[[['  \n");
	printf("   $$$''   c$$$cc$$$c $$$        '$$$'''$$$    c$$'    \n");
	printf("   888o    888   888,`88bo,__,o, 888   '88o ,8P'`    \n");
	printf("   YMMMb   YMM   ''`   'YUMMMMMP'MMM    YMMmM'  \n");
	printf("\n");
    printf("v 1.3\n\n"); 
    printf("Detected:\n");
    system("hostnamectl |sed -n 6p");
    printf("\033[0m");
    printf("\n\n");  
/*===================================================================================================================== 
| Cheking for installed software
*====================================================================================================================*/  
    int rv;
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
	char key[1];
	printf("Press any key to continue:");
	scanf("%c", key);
    system("id -un");
    system("mkdir /home/pachy");
    menu();
    
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
        elemants[i].present = true; 
        
	} 
    else {
		printf("\033[1;31m");
        printf("%s\n", nmessage[i]);
        printf("\033[0m");
        printf("-----------------------------------------------------------\n");
        elemants[i].present = false;
	}
}
