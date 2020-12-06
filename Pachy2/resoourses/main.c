

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int		menu(void)
{
	int		win_x; //Max Win X
	int		win_y; //Max Win Y
	int		option = 1; //Current Selected Option
	int		c_x; //Center X of screen
	int		c_y; //Center Y of screen
	int		titleboxlen; //Strlen of titlebox
	titleboxlen = strlen("=========================================================================="); //Get Title Box Length To Center It

	char *o_full = "Full Install"; //Just The Option Names, You Can Change Em
	char *o_custom = "Custom Install";
	char *o_missing = "Install Missing";
	char *o_upgrade = "Upgrade";
	char *o_optimize = "Optimize";
	char *o_quit = "Quit";


	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	
	getmaxyx(stdscr, win_y, win_x); 
	WINDOW*win_menu = newwin(win_y, win_x, 0, 0);

	keypad(win_menu, true);

	while (1)
	{
		wclear(win_menu);
		getmaxyx(win_menu, win_y, win_x);
		c_x = win_x / 2; //Find Middle of X
		c_y = win_y / 2; //Find Middle of Y
		
		//Render Fancy Boxes ETC
		//The Text centering takes half the screen, then further subtracts half the strlen to center it perfectly. Just for you mister OCD
		mvwprintw(win_menu, c_y - 10, c_x - (titleboxlen / 2), "==========================================================================");
		mvwprintw(win_menu, c_y - 9, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y - 8, c_x - (titleboxlen / 2), "||                                 Menu                                 ||");
		mvwprintw(win_menu, c_y - 7, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y - 6, c_x - (titleboxlen / 2), "==========================================================================");
		mvwprintw(win_menu, c_y - 5, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y - 4, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y - 3, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y - 2, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y - 1, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 1, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 2, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 3, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 4, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 5, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 6, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 7, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 8, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 9, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 10, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 11, c_x - (titleboxlen / 2), "||                                                                      ||");
		mvwprintw(win_menu, c_y + 12, c_x - (titleboxlen / 2), "==========================================================================");

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
			wattron(win_menu, COLOR_PAIR(1));
			mvwprintw(win_menu, c_y + 7, c_x - (strlen(o_quit) / 2), o_quit);
			wattroff(win_menu, COLOR_PAIR(1));
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
					//Do One Player Stuff
				}
				
				if (option == 2)
				{
					//Do Two Player Stuff
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
					//Quit The Game
					endwin();
					curs_set(TRUE);
					system("clear");
					return (0);
				}
				break;
		}
	}
}
