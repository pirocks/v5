#ifndef command_lineD
#define command_lineD
#include "state.h"
//#include "valid.h"
//#include "position_evaluatev5.h"

void console_ask_for_piece_white(bool ai)
{
    printcolored_board(global_board);
	int x_in = -1;
	int y_in = -1;
    int error = 0;
    while(error != 1)
    {
        printf("enter the x coordinate of the white piece you want to move:\n");
	    error = scanf("%d",&x_in);
    }
    error = 0;
    while(error != 1)
    {
        printf("enter the y coordinate of the white piece you want to move:\n");
	    error = scanf("%d",&y_in);
    }
	console_ask_for_move_white(ai,x_in,y_in);
}

void console_ask_for_piece_black(bool ai)
{
	if(ai)
	{
	    init_dot();
	    int val = create_node(global_board,white_count(global_board,0)-black_count(global_board,0));
	    move_to_dop answer = get_move(global_board,4,false,val);
	    close_dot();
	    assert(valid(global_board,(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4]));
	    move(&global_board,(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4],false);
	    printf("\n");
	    print_move(answer);
	    console_ask_for_piece_white(ai);
	}
	else
	{
		int x_in = -1;
		int y_in = -1;
		int error = 0;
		while (error != 1)
        {
            printf("enter the x coordinate of the black piece you want to move:\n");
		    error = scanf("%d",&x_in);
        }
        error = 0;
        while (error != 1)
        {
            printf("enter the y coordinate of the black piece you want to move:\n");
	    	error = scanf("%d",&y_in);
        }
		console_ask_for_move_black(ai,x_in,y_in);
	}
}

void console_ask_for_move_white(bool ai, int x_in, int y_in)
{
	int x_end = -1;
	int y_end = -1;
	int error = 0;
	while(error != 1)
	{
        printf("enter the x coordinate of where you want to move your white piece:\n");
	    error = scanf("%d",&x_end);
	}
	error = 0;
	while (error != 1)
    {
    	printf("enter the y coordinate of where you want to move your white piece:\n");
        error = scanf("%d",&y_end);
    }
	if(valid(global_board,x_in,y_in,x_end,y_end))
	{
		move(&global_board,x_in,y_in,x_end,y_end,false);
        console_ask_for_piece_black(ai);
	}
	else
	{
		printf("not valid\n");
		console_ask_for_piece_white(ai);
	}
}

void console_ask_for_move_black(bool ai, int x_in, int y_in)
{
	int x_end = -1;
	int y_end = -1;
	int error = 0;
	while(error != 1)
	{
        printf("enter the x coordinate of where you want to move your black piece:\n");
	    error = scanf("%d",&x_end);
	}
	error = 0;
	while(error != 1)
	{
        printf("enter the y coordinate of where you want to move your black piece:\n");
	    error = scanf("%d",&y_end);
	}
	if(valid(global_board,x_in,y_in,x_end,y_end))
	{
		move(&global_board,x_in,y_in,x_end,y_end,false);
	}
	else
	{
		printf("not valid\n");
        console_ask_for_piece_black(ai);
	}
}
#endif
