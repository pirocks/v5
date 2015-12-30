#include "state.h"
#include <curses.h>
#include "curses_board_utils.h"

int[][] highlights;

char * message_string;
char ** board_strings;

void free_board_string()
{
    for(int i = 0 ; i < 8; i++)
        free(board_strings[i]);
    free(board_strings);
}

void update_board_string(board board_in)
{
    free_board_string();
    board_strings = create_colored_board(board_in);
}

void convert_todynamically_allocated(char * in)
{
    char * out =  malloc(1000*sizeof(char));
    memcpy(out,in,sizeof(char)*strlen(in));
    return out;
}

void update_message_string(char * in);
{
    //in must be dynamically allocated
    free(message_string);
    message_string = convert_todynamically_allocated(in);
}

void cleanup(int state);
void init()
{
    signal(SIGINT, cleanup);      /* arrange interrupts to terminate */

    initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    nonl();         /* tell curses not to do NL->CR/NL on output.  that means no new lines*/
    cbreak();       /* take input chars one at a time, no wait for \n aka raw mode */
    
    echo();
    if (has_colors())
    {
        start_color();

        /*
         * Simple color assignment, often all we need.  Color pair 0 cannot
         * be redefined.  This example uses the same value for the color
         * pair as for the foreground color, though of course that is not
         * necessary:
         */
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }
    #if 0
    	for (;;)
	    {
	        int c = getch();
	        attrset(COLOR_PAIR(num % 8));
	        num++;
	    }
    #endif
}

void cleanup(int state)
{
	endwin();
    /* do your non-curses wrapup here */
    free_board_string();
    exit(state);
}