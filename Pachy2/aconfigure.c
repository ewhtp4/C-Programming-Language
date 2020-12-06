#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pachy.h"

char *oslinux[7] = {"SUSE", "openSuse","Red", "CentOS", "Linux", "Debian", "Ubuntu"};
char *active[2] = {"active", "failed"};
static void (*configs[7])() = {confSuseBased, 
                               confSuseBased, 
                               confRedHat, 
                               confCentOS, 
                               confDebianBased,
                               confDebianBased,
                               confDebianBased};
int apacheConfigureCheck();
void apacheConfigs(regex_t *pexp, char *sz, int i);
void aConfigure() {
    FILE *checkconf = ((void*)0);
    char buffer[1024];
	regex_t exp;
    for (int i = 0; i < 7 ; i++)
    {
        int rv;
        rv = regcomp(&exp, active[i], REG_EXTENDED);
        if (!(checkconf = popen("systemctl status apache2 | sed -n 5p | awk '{print $2}'", "r"))) {
        perror("popen");
        break;
        }
        if(fgets(buffer, sizeof(buffer), checkconf)) {
            if(checkconf = "active") {
                apacheConfigureCheck();
            }
        }
        else {
            printf(".\n");
        }            
    }
    pclose(checkconf);
	regfree(&exp);
}
int apacheConfigureCheck() {
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
            apacheConfigs(&exp, buffer, i);    
        }
        else {
            printf("This Distribution is not suported yest sorry.\n");
        }            
    }
    pclose(distro);
	regfree(&exp);
}
void apacheConfigs(regex_t *pexp, char *sz, int i) {  

	regmatch_t matches[1]; 
	if (regexec(pexp, sz, 1, matches, 0) == 0) {
		configs[i]();
    }    
}
void confDebianBased() {
    char *domain = malloc(30 * sizeof(char));
    system("ufw allow 'Apache'");
    system("sudo allow 80/tcp");
    system("firefox http://localhost");
    printf("Please state a domain name(requiered form - domain_name.com): ");
    scanf("%s", domain);
    char command1[50];
    char command2[50];
    char command3[50];
    char command4[200];
    char command5[250];
    char command6[30];
    char command7[30];
    sprintf(command1,"sudo mkdir -p /var/www/%s/html",domain);
    system(command1);
    sprintf(command2,"sudo chown -R $USER:$USER /var/www/%s/html",domain);
    system(command2);
    sprintf(command3,"sudo chmod -R 755 /var/www/%s",domain);
    system(command3);
    sprintf(command4,"sudo echo <html>\n<head>\n<title>Welcome to the page %s!</title>\n</head>\n<body><h1>Your %s server block is up and running!</h1>\n</body>\n</html> >> /var/www/%s/html/index.html",domain,domain,domain);
    system(command4);
    char *admin = malloc(30 * sizeof(char));
    printf("Please state a admin name(to skip press enter): ");
    sprintf(command5,"sudo echo <VirtualHost *:80>\n\tServerAdmin %s\n\tServerName %s\n\tServerAlias www.%s\n\tDocumentRoot /var/www/%s/html\n\tErrorLog ${APACHE_LOG_DIR}/error.log\n\tCustomLog ${APACHE_LOG_DIR}/access.log combined\n</VirtualHost> >> /etc/apache2/sites-available/%s.conf",admin,domain,domain,domain,domain);
    system(command5);
    sprintf(command6,"sudo a2ensite %s.conf",domain);
    system(command6);
    system("sudo a2dissite 000-default.conf");
    system(" sudo systemctl restart apache2");
    system("sudo apache2ctl configtest");
    sprintf(command7,"firefox http://%s",domain);
    system(command7);
    system("sudo netstat -pnltu | grep apache >> /home/ewhtp4/Desktop/test.log");
}
void confSuseBased () {

}
void confRedHat () {

}					
void confCentOS () {

}