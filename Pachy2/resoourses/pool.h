#ifndef DICTIONARY_H  //File guards begining
#define DICTIONARY_H // File guards protect the body of the heder file
                     //From being included more then once

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
const char *oslinux[7] = {"SUSE", "openSuse","Debian", "CentOS", "Linux", "Red", "Ubuntu"};                                       
const char *installs[7] = {"sudo zypper update ; sudo zypper install apache2 ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; systemctl status apache2",
                        "sudo zypper update ; sudo zypper install apache2 ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; systemctl status apache2",
                        "sudo apt update -y ; sudo apt install apache2 -y ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; sudo systemctl status apache2",
                        "sudo yum update ; sudo yum install httpd ; sudo systemctl start httpd ; sudo systemctl enable httpd ;sudo systemctl status httpd",
                        "sudo apt update -y ; sudo apt install apache2 -y ; sudo systemctl start apache2 ; sudo systemctl enable apache2 ; sudo systemctl status apache2",
                        "yum install httpd ; chkconfig httpd on ; system-config-services ; service httpd start",
                        "gnome-terminal -e 'sh -c \"apt-get update ; apt-get install apache2 ; systemctl start apache2.service\"'"};                            


elemant elemants[5] = {{"apache2", "sudo apt-get install apache2", "", false, false},
                           {"bind", "", "", false, false},
                           {"mysql", "", "", false, false},
                           {"php", "", "", false, false},
                           {"perl", "", "", false, false}};
    
#endif                        