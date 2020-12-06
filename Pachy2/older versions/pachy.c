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
 |  Description:  Applies Grayscale,Sapia,Reflect and Blure Filter to BMP 
 |                images from the terminal.
 |        Input:  ./filter [filter option: -g,-s,-r,-b] [name of file] [name of new file]
 |               
 |       Output:  A new image file with the applied filter
 |
 |    Algorithm:  Greyscale, Sapia, Reflect, Blure
 |      
 |
 |   Required Features Not Included:  No requirmant, the program does not aplly any other filters.
 |      
 |
 |   Known Bugs:  N/A
 |      
 |
 *====================================================================================================================*/
#include <sys/utsname.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

int main(int argc, char **argv)
{
    FILE *shellpipe = ((void*)0);
    int i;
    char buffer[1024];
    
   // printf("test");
    if (!(shellpipe = popen("apache2 -version", "r"))) {
        perror("popen");
        return 1;
    }
    fgets(buffer, sizeof(buffer), shellpipe);
        char *apache = "Server version: Apache/2.4.29 (Ubuntu)\n";
        if(strcmp(apache, buffer) == 0){
            printf("You have a Apache2.\n-----------------------------------------------------------\n");
        }
        else
        {
            printf("No Apache server found, need to be installed.\n-----------------------------------------------------------\n");
        }
    if (!(shellpipe = popen("named -v", "r"))) {
        perror("popen");
        return 1;
    }
    fgets(buffer, sizeof(buffer), shellpipe);
        char *bind = "BIND 9.11.3-1ubuntu1.11-Ubuntu (Extended Support Version) <id:a375815>\n";
        if(strcmp(bind, buffer) == 0){
            printf("You have a Bind.\n-----------------------------------------------------------\n");
        }
        else
        {
            printf("Bind needs to be installed.\n-----------------------------------------------------------\n");
        }

    pclose(shellpipe); 
    return 0;
}
