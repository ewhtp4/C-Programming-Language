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
/*===================================================================================================================== 
| Constants Pool
 *====================================================================================================================*/
const char *vcommand[NUMBER_CHECKS] = { "apache2 -version | awk '{print $3}'",
                                        "named -v",
                                        "mysql -V",
                                        "php --version",
                                        "perl -v"
                                        };
const char *pmessage[NUMBER_CHECKS] = { "Apache2 Installed\n",
                                        "Bind Installed\n",
                                        "MySQL Installed\n",
                                        "PHP Installed\n",
                                        "Pirl Installed\n"};                                               
const char *nmessage[NUMBER_CHECKS] = { "Apache2 Missing\n",
                                        "Bind Missing\n",
                                        "MySQL Missing\n",
                                        "PHP Missing\n",
                                        "Pirl Missing\n"};
const char *testtext[NUMBER_CHECKS] = { "Server version: Apache/2.4.29 (Ubuntu)\n",
                                        "BIND 9.11.3-1ubuntu1.11-Ubuntu (Extended Support Version) <id:a375815>\n",
                                        "mysql  Ver 14.14 Distrib 5.7.29, for Linux (x86_64) using  EditLine wrapper\n",
                                        "PHP 7.2.24-0ubuntu0.18.04.3 (cli) (built: Feb 11 2020 15:55:52) ( NTS )\n",
                                        "Something"};

int main(int argc, char **argv)
{
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
            printf("\n\n");
    pclose(figlet);
/*===================================================================================================================== 
| Cheking for installed software
*====================================================================================================================*/  
    FILE *shellpipe = ((void*)0);
    int i;
    char buffer[1024];
   
    for (int i = 0; i < NUMBER_CHECKS; i++)
    {
        
        if (!(shellpipe = popen(vcommand[i], "r"))) {
        perror("popen");
        return 1;
        }
        fgets(buffer, sizeof(buffer), shellpipe);
            if(strcmp(testtext[i], buffer) == 0){
                printf("\033[0;32m");
                printf("%s", pmessage[i]);
                printf("\033[0m");
                printf("-----------------------------------------------------------\n");
            }
            else 
            {
                printf("\033[1;31m");
                printf("%s", nmessage[i]);
                printf("\033[0m");
                printf("-----------------------------------------------------------\n");
            }
       
    }
    pclose(shellpipe); 
    return 0;
}

