#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "pachy.h"
/*===================================================================================================================== 
| Menu Function
 *====================================================================================================================*/
int	menu(void)
{
    
	int		win_x; //Max Win X
	int		win_y; //Max Win Y
	int		option = 1; //Current Selected Option
	int		c_x; //Center X of screen
	int		c_y; //Center Y of screen
	int		titleboxlen; //Strlen of titlebox
	titleboxlen = strlen("========================================================================="); 

	char *o_full = "Full Install"; 
	char *o_custom = "Custom Install";
	char *o_missing = "Install Missing";
	char *o_upgrade = "Upgrade";
	char *o_optimize = "Optimize";
	char *o_quit = "Quit";
    #define OTION_PAIR 1
    #define PACHY_PAIR 2
    #define BOX_PAIR 3
    #define MOUNTAIN_PAIR 4
    #define QUIT_PAIR 5
	#define APACHE_PAIR 6

	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	start_color();
    init_pair(OTION_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PACHY_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BOX_PAIR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(QUIT_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(APACHE_PAIR, COLOR_BLUE,COLOR_BLACK);

	WINDOW *win;
	WINDOW *apache;
	getmaxyx(stdscr, win_y, win_x); 
	WINDOW*win_menu = newwin(win_y, win_x, 0, 0);
    refresh();
    wborder(win_menu, 0, 0, 0, 0, 0, 0, 0, 0);
	keypad(win_menu, true);
    
	while (1)
	{
		wclear(win_menu);
        wborder(win_menu, 0, 0, 0, 0, 0, 0, 0, 0);
        wborder(win_menu, 0, 0, 0, 0, 0, 0, 0, 0);
        printw(""); addch(ACS_CKBOARD);
		getmaxyx(win_menu, win_y, win_x);
		c_x = win_x / 2; //Find Middle of X
		c_y = win_y / 2; //Find Middle of Y
        wattron(win_menu, COLOR_PAIR(PACHY_PAIR));
        mvwprintw(win_menu, c_y - 15, c_x - (titleboxlen / 2) + 9, "::::::::::. :::.       .,-:::::   ::   .:.-:.     ::-.");
        mvwprintw(win_menu, c_y - 14, c_x - (titleboxlen / 2) + 9, " `;;;```.;;;;;`;;    ,;;;'````'  ,;;   ;;,';;.   ;;;;'");
        mvwprintw(win_menu, c_y - 13, c_x - (titleboxlen / 2) + 9, "  `]]nnn]]',[[ '[[,  [[[        ,[[[,,,[[[  '[[,[[['  ");
        mvwprintw(win_menu, c_y - 12, c_x - (titleboxlen / 2) + 9, "   $$$''   c$$$cc$$$c $$$        '$$$'''$$$    c$$'    ");
        mvwprintw(win_menu, c_y - 11, c_x - (titleboxlen / 2) + 9, "   888o    888   888,`88bo,__,o, 888   '88o ,8P'`    ");
        mvwprintw(win_menu, c_y - 10, c_x - (titleboxlen / 2) + 9, "   YMMMb   YMM   ''`   'YUMMMMMP'MMM    YMMmM'  ");
        wattroff(win_menu, COLOR_PAIR(PACHY_PAIR));
        mvwprintw(win_menu, c_y - 7, c_x - (titleboxlen / 2) + 34, "Menu");
        wattron(win_menu, COLOR_PAIR(BOX_PAIR));
        mvwhline(win_menu, c_y - 8, c_x - (titleboxlen / 2), ACS_ULCORNER, 1);
        mvwhline(win_menu, c_y - 8, c_x - (titleboxlen / 2) + 71, ACS_URCORNER, 1);
        mvwhline(win_menu, c_y - 8, c_x - (titleboxlen / 2) + 1, ACS_HLINE, 70);
        mvwhline(win_menu, c_y - 6, c_x - (titleboxlen / 2) + 1, ACS_HLINE, 70);
        mvwhline(win_menu, c_y + 12, c_x - (titleboxlen / 2) + 1, ACS_HLINE, 70);
        mvwvline(win_menu, c_y - 7, c_x - (titleboxlen / 2), ACS_VLINE, 19);
        mvwvline(win_menu, c_y - 7, c_x - (titleboxlen / 2) + 71, ACS_VLINE, 19);
        mvwvline(win_menu, c_y + 12, c_x - (titleboxlen / 2), ACS_LLCORNER, 1);
        mvwvline(win_menu, c_y + 12, c_x - (titleboxlen / 2) + 71, ACS_LRCORNER, 1);
        mvwhline(win_menu, c_y - 6, c_x - (titleboxlen / 2), ACS_LTEE, 1);
        mvwhline(win_menu, c_y - 6, c_x - (titleboxlen / 2) + 71, ACS_RTEE, 1);
        wattroff(win_menu, COLOR_PAIR(BOX_PAIR));
        wrefresh(win_menu);
		//Render Out Buttons, Inverse Video Of Selected
		if (option == 1)
		{
			wattron(win_menu, COLOR_PAIR(1));
			mvwprintw(win_menu, c_y - 1, c_x - (strlen(o_full) / 2), o_full);
			wattroff(win_menu, COLOR_PAIR(1));
		}
		else
			mvwprintw(win_menu, c_y - 1, c_x - (strlen(o_full) / 2), o_full);

		if (option == 2)
		{
			wattron(win_menu, COLOR_PAIR(1));
			mvwprintw(win_menu, c_y + 1, c_x - (strlen(o_custom) / 2), o_custom);
			wattroff(win_menu, COLOR_PAIR(1));
		}
		else
			mvwprintw(win_menu, c_y + 1, c_x - (strlen(o_custom) / 2), o_custom);

		if (option == 3)
		{
			wattron(win_menu, COLOR_PAIR(1));
			mvwprintw(win_menu, c_y + 3, c_x - (strlen(o_missing) / 2), o_missing);
			wattroff(win_menu, COLOR_PAIR(1));
		}
		else
			mvwprintw(win_menu, c_y + 3, c_x - (strlen(o_missing) / 2), o_missing);

		if (option == 4)
		{
			wattron(win_menu, COLOR_PAIR(1));
			mvwprintw(win_menu, c_y + 5, c_x - (strlen(o_upgrade) / 2), o_upgrade);
			wattroff(win_menu, COLOR_PAIR(1));
		}
		else
			mvwprintw(win_menu, c_y + 5, c_x - (strlen(o_upgrade) / 2), o_upgrade);

		if (option == 5)
		{
			wattron(win_menu, COLOR_PAIR(QUIT_PAIR));
			mvwprintw(win_menu, c_y + 7, c_x - (strlen(o_quit) / 2), o_quit);
			wattroff(win_menu, COLOR_PAIR(QUIT_PAIR));
		}
		else
			mvwprintw(win_menu, c_y + 7, c_x - (strlen(o_quit) / 2), o_quit);

		//Update Screen
		wrefresh(win_menu);

		//Key Hooks
		switch(wgetch(win_menu))
		{
			case KEY_UP:
				if (option == 1)
					option = 5;
				else
					option -= 1;
				break;
			case KEY_DOWN:
				if (option == 5)
					option = 1;
				else
					option += 1;
				break;
			case 10: //10 Being Enter Key
				if (option == 1)
				{	
					initscr();
					cbreak();
					noecho();
					curs_set(FALSE);
					apache = newwin(0,0,0,0);
					wrefresh(apache);
					wattron(apache, COLOR_PAIR(PACHY_PAIR));
					mvwhline(apache, c_y - 18, c_x - (titleboxlen / 2), ACS_ULCORNER, 1);
        			mvwhline(apache, c_y - 18, c_x - (titleboxlen / 2) + 71, ACS_URCORNER, 1);
					mvwhline(apache, c_y - 18, c_x - (titleboxlen / 2) + 1, ACS_HLINE, 70);
  					mvwhline(apache, c_y - 16, c_x - (titleboxlen / 2) + 1, ACS_HLINE, 70);
					mvwhline(apache, c_y + 17, c_x - (titleboxlen / 2) + 1, ACS_HLINE, 70);
					mvwvline(apache, c_y - 17, c_x - (titleboxlen / 2), ACS_VLINE, 34);
        			mvwvline(apache, c_y - 17, c_x - (titleboxlen / 2) + 71, ACS_VLINE, 34);
					mvwvline(apache, c_y + 17, c_x - (titleboxlen / 2), ACS_LLCORNER, 1);
        			mvwvline(apache, c_y + 17, c_x - (titleboxlen / 2) + 71, ACS_LRCORNER, 1);
					mvwhline(apache, c_y - 16, c_x - (titleboxlen / 2), ACS_LTEE, 1);
        			mvwhline(apache, c_y - 16, c_x - (titleboxlen / 2) + 71, ACS_RTEE, 1);
					wattroff(apache, COLOR_PAIR(PACHY_PAIR));
					mvwprintw(apache, c_y - 17, c_x - (titleboxlen / 2) + 11, "               INSTALLING APACHE2             ");
					wattron(apache, COLOR_PAIR(APACHE_PAIR));
					mvwprintw(apache, c_y - 15, c_x - (titleboxlen / 2) + 11, "                                   #*          ");
					mvwprintw(apache, c_y - 14, c_x - (titleboxlen / 2) + 11, "                                #######,       ");
					mvwprintw(apache, c_y - 13, c_x - (titleboxlen / 2) + 11, "                              ##########       ");
					mvwprintw(apache, c_y - 12, c_x - (titleboxlen / 2) + 11, "                           ,(###########       ");
					mvwprintw(apache, c_y - 11, c_x - (titleboxlen / 2) + 11, "                          (((((######(((       ");
					mvwprintw(apache, c_y - 10, c_x - (titleboxlen / 2) + 11, "                        (((((((((((((((,       ");
					mvwprintw(apache, c_y - 9, c_x - (titleboxlen / 2) + 11, "                      //////((((((((((         ");
					mvwprintw(apache, c_y - 8, c_x - (titleboxlen / 2) + 11, "                    ////////////(((((          ");
					mvwprintw(apache, c_y - 7, c_x - (titleboxlen / 2) + 11, "                   *///// //////////           ");
					mvwprintw(apache, c_y - 6, c_x - (titleboxlen / 2) + 11, "                 ,*****///////////             ");
					mvwprintw(apache, c_y - 5, c_x - (titleboxlen / 2) + 11, "                ***********///****             ");
					mvwprintw(apache, c_y - 4, c_x - (titleboxlen / 2) + 11, "               ****** ***********              ");
					mvwprintw(apache, c_y - 3, c_x - (titleboxlen / 2) + 11, "             ******* ***********               ");
					mvwprintw(apache, c_y - 2, c_x - (titleboxlen / 2) + 11, "            ******* ******** **                ");
					mvwprintw(apache, c_y - 1, c_x - (titleboxlen / 2) + 11, "           ******* **********                  ");
					mvwprintw(apache, c_y - 0, c_x - (titleboxlen / 2) + 11, "          *******,**********,                  ");
					mvwprintw(apache, c_y + 1, c_x - (titleboxlen / 2) + 11, "         *******************                   ");
					mvwprintw(apache, c_y + 2, c_x - (titleboxlen / 2) + 11, "        ******************,                    ");
					mvwprintw(apache, c_y + 3, c_x - (titleboxlen / 2) + 11, "        *****************                      ");
					mvwprintw(apache, c_y + 4, c_x - (titleboxlen / 2) + 11, "       ****************                        ");
					mvwprintw(apache, c_y + 5, c_x - (titleboxlen / 2) + 11, "       ,,************                          ");
					mvwprintw(apache, c_y + 6, c_x - (titleboxlen / 2) + 11, "    ,,.,,,*.*****   ,.                         ");
					mvwprintw(apache, c_y + 7, c_x - (titleboxlen / 2) + 11, "     ,,,,, ,,,,,,,,.                           ");
					mvwprintw(apache, c_y + 8, c_x - (titleboxlen / 2) + 11, "      ,,, ,,,,,,,,,                            ");
					mvwprintw(apache, c_y + 9, c_x - (titleboxlen / 2) + 11, "    ,,,, ,,,,,,                                ");
					mvwprintw(apache, c_y + 10, c_x - (titleboxlen / 2) + 11, "      ,  ,                                     ");
					mvwprintw(apache, c_y + 11, c_x - (titleboxlen / 2) + 11, "     ,                                          ");
					mvwprintw(apache, c_y + 12, c_x - (titleboxlen / 2) + 11, "   ,                                          ");
					mvwprintw(apache, c_y + 13, c_x - (titleboxlen / 2) + 11, "   .     ");
					mvwprintw(apache, c_y + 14, c_x - (titleboxlen / 2) + 11, "   ,   ");
					mvwprintw(apache, c_y + 15, c_x - (titleboxlen / 2) + 11, "  .   ");
					mvwprintw(apache, c_y + 16, c_x - (titleboxlen / 2) + 11, " .");
					wrefresh(apache);
					apache2();
					char key;
					printf("Do you want to configure now? [Y/N]?:");
					scanf("%c", &key);
					while( key != 'N' || key != 'n')
						if(key == 'Y' || key == 'y') {
							//aConfigure();
						}
						else continue;
					curs_set(TRUE);
					system("clear");
					getch();
					endwin();
				}
				
				if (option == 2)
				{

					apache2();
				}

				if (option == 3)
				{
					//Help Stuff
				}

				if (option == 4)
				{
					//Credits Stuff
				}

				if (option == 5)
				{
					//Quit The Menu
					endwin();
					curs_set(TRUE);
					system("clear");
					return (0);
				}
				break;
		}
	}
}
