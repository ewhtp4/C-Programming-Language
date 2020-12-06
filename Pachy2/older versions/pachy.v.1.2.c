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
#include <ncurses.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define NUMBER_CHECKS 5
#define MAX_STRING_SIZE 40
#define MAX_MATCHES 1 
void match(regex_t *pexp, char *sz, int i);
int apache2();
void apachinstall(regex_t *pexp, char *sz, int i);
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
const char *oslinux[7] = {"SUSE", "openSuse","Debian", "CentOS", "Linux", "Red", "1Ubuntu"};                                       
const char *installs[7] = {"sudo zypper update ; sudo zypper install apache2 ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; systemctl status apache2",
                        "sudo zypper update ; sudo zypper install apache2 ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; systemctl status apache2",
                        "sudo apt update -y ; sudo apt install apache2 -y ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; sudo systemctl status apache2",
                        "sudo yum update ; sudo yum install httpd ; sudo systemctl start httpd ; sudo systemctl enable httpd ;sudo systemctl status httpd",
                        "sudo apt update -y ; sudo apt install apache2 -y ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; sudo systemctl status apache2",
                        "yum install httpd ; chkconfig httpd on ; system-config-services ; service httpd start",
                        "sudo apt-get update ; sudo apt-get install apache2 ; sudo systemctl start apache2.service"};                            
  typedef struct
{
    char *name;
    char *install;
    char *configure;
    bool present;
    bool upgradable;
}
elemant;
elemant elemants[5] = {{"apache2", "sudo apt-get install apache2", "", false, false},
                           {"bind", "", "", false, false},
                           {"mysql", "", "", false, false},
                           {"php", "", "", false, false},
                           {"perl", "", "", false, false}};

int found = 0;
int main(int argc, char **argv) {
/*===================================================================================================================== 
| Banner
*====================================================================================================================*/
    system("clear");
    printf("\033[0;33m");
    printf("██████╗   █████╗   ██████╗ ██╗  ██╗ ██╗   ██╗\n");
    printf("██╔══██╗ ██╔══██╗ ██╔════╝ ██║  ██║ ╚██╗ ██╔╝\n");
    printf("██████╔╝ ███████║ ██║      ███████║  ╚████╔╝\n");
    printf("██╔═══╝  ██╔══██║ ██║      ██╔══██║   ╚██╔╝\n");
    printf("██║      ██║  ██║ ╚██████╗ ██║  ██║    ██║ \n");
    printf("╚═╝      ╚═╝  ╚═╝  ╚═════╝ ╚═╝  ╚═╝    ╚═╝\n");
    printf("v 1.2\n\n"); 
    printf("Detected:\n");
    system("hostnamectl |sed -n 6p");
    printf("\033[0m");
    printf("\n\n");  
/*===================================================================================================================== 
| Cheking for installed software
*====================================================================================================================*/  
    int rv;
    int rv2;
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
    char *choice;
    printf("\033[0;33m");
    printf("╔═════════════════════════════════════════════════════════╗\n");
    printf("║                         Menu                            ║\n");
    printf("╚═════════════════════════════════════════════════════════╝\n");
    printf("╔═════════════════════════════════════════════════════════╗\n");
    printf("║                   [F]Full Instal                        ║\n");
    printf("║                   [C]Custom Install                     ║\n");
    printf("║                   [M]Install Missing                    ║\n");
    printf("║                   [U]Upgrade                            ║\n");
    printf("║                   [O]Optimize                           ║\n");
    printf("║                   [Q]Quit                               ║\n");
    printf("╚═════════════════════════════════════════════════════════╝\n");
    printf("\033[0m");
    scanf("%s", choice);
    while(choice != "Q" || choice != "QUIT") {
        if(choice = "F") {
            apache2();
        }
        if(choice = "C") {
            printf("What would you like to install?: ");
            printf("1 - Apache2, 2 - Bind, 3 - MySQL, 4 - PHP, 5 - Perl");
        }    
        if(choice = "M") {
            for (int i = 0; i < NUMBER_CHECKS; i++) {
                if(elemants[i].present = false) {
                    system(elemants[i].install);
                }
            }    
        }
        if(choice = "U") {
            for (int i = 0; i < NUMBER_CHECKS; i++) {
                if(elemants[i].upgradable = true) {
                    system(elemants[i].install);
                }
            }
        }
        if(choice = "O") {
        }
    }
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
/*===================================================================================================================== 
|  Apache install Function
*====================================================================================================================*/  
int apache2() {
    int rv;
    
    FILE *distro = ((void*)0);
    char buffer[1024];
	regex_t exp;
    for (int i = 0; i < 7 ; i++)
    {
        rv = regcomp(&exp, oslinux[i], REG_EXTENDED);
        if (!(distro = popen("hostnamectl |sed -n 6p | awk '{print $3}'", "r"))) {
        perror("popen");
        break;
        }
        if(fgets(buffer, sizeof(buffer), distro)) {
            apachinstall(&exp, buffer, i);    
        }
        else {
            printf("This Distribution is not suported yest sorry.\n");
        }            
    }
    pclose(distro);
	regfree(&exp);
}
void apachinstall(regex_t *pexp, char *sz, int i) {  

	regmatch_t matches[1]; 
	if (regexec(pexp, sz, 1, matches, 0) == 0) {
		system(installs[i]);
	} 
}   