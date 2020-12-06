#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachy.h"
char *oslinux[7] = {"SUSE", "openSuse","Red", "CentOS", "Linux", "Debian", "Ubuntu"};
/*===================================================================================================================== 
|  Apache install Function
*====================================================================================================================*/  
void apacheInstall(regex_t *pexp, char *sz, int i);
void apacheCentOS();
void apacheDebianBased();
void apacheSuseBased();
void apacheRedHat();
static void (*apaches[7])() = {apacheSuseBased, 
                               apacheSuseBased, 
                               apacheRedHat, 
                               apacheCentOS, 
                               apacheDebianBased,
                               apacheDebianBased,
                               apacheDebianBased};
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
            apacheInstall(&exp, buffer, i);    
        }
        else {
            printf("This Distribution is not suported yest sorry.\n");
        }            
    }
    pclose(distro);
	regfree(&exp);
}
void apacheInstall(regex_t *pexp, char *sz, int i) {  

	regmatch_t matches[1]; 
	if (regexec(pexp, sz, 1, matches, 0) == 0) {
		apaches[i]();
        system("ufw allow 'Apache'");
    }    
}								
void apacheCentOS() { 
    system("sudo xterm -e yum update ; xterm -e yum install httpd ; xterm -e systemctl start httpd ; xterm -e systemctl enable httpd ; xterm -e systemctl status httpd");
}                                    
void apacheDebianBased() {
    system("sudo xterm -e apt update ; xterm -e  apt install apache2 -y ; xterm -e  systemctl start apache2 ; xterm -e  systemctl enable apache2 ; xterm -e systemctl status apache2");
}    
void apacheSuseBased() {
    system("sudo xterm -e zypper update ; xterm -e zypper install apache2  -y ; xterm -e systemctl start apache2 ; xterm -e systemctl enable apache2 ; xterm -e systemctl status apache2");
}
void apacheRedHat() {
    system("sudo xterm -e yum update ; xterm -e yum install httpd -y ; xterm -e chkconfig httpd on ; xterm -e system-config-services ; xterm -e service httpd start ; xterm -e systemctl status httpd");
}

