#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
typedef struct
{
    char *fist;
    char *second;
    char *third;
    char *fourth;
    char *fifth;
} install_instructio;    
char *oslinux[7] = {"SUSE", "openSuse","Debian", "CentOS", "Linux", "Red", "Ubuntu"};
char *installs[7] = {"./apachesh/apache2SUSE.sh",
                     "./apachesh/apache2OpenSUSE.sh",
                     "./apachesh/apache2Debian.sh",
                     "./apachesh/apache2CentOS.sh",
                     "./apachesh/apache2linuxMint.sh",
                     "./apachesh/apache2redhat.sh",
                     "./apachesh/apache2ubuntu.sh"};             

/*===================================================================================================================== 
|  Apache install Function
*====================================================================================================================*/  
void apachinstall(regex_t *pexp, char *sz, int i);

int apache2v2() {
    int		win_x; //Max Win X
	int		win_y; //Max Win Y
	int		option = 1; //Current Selected Option
	int		c_x; //Center X of screen
	int		c_y; //Center Y of screen
	int		titleboxlen; //Strlen of titlebox
	titleboxlen = strlen("========================================================================="); 
    initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	start_color();
    //init_pair(APACHE, COLOR_YELLOW, COLOR_BLACK);
    getmaxyx(stdscr, win_y, win_x); 
	WINDOW *win_apache = newwin(win_y, win_x, 0, 0);
    refresh();
    wborder(win_apache, 0, 0, 0, 0, 0, 0, 0, 0);
	//keypad(win_apache, true);
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
    endwin();
	curs_set(TRUE);
	system("clear");
    return (0);
}
void apachinstall(regex_t *pexp, char *sz, int i) {  

	regmatch_t matches[1]; 
	if (regexec(pexp, sz, 1, matches, 0) == 0) {
		system(installs[i]);
	} 
}								