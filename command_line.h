#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
//#include "valid.h"
//#include "position_evaluatev5.h"
extern board global_board;


void console_ask_for_piece_white(bool ai);
void console_ask_for_piece_black(bool ai);
void console_ask_for_move_white(bool ai, int x_in, int y_in);
void console_ask_for_move_black(bool ai, int x_in, int y_in);

void console_ask_for_piece_white(bool ai)
{
    printcolored_board(global_board);
	int x_in = -1;
	int y_in = -1;
    printf("enter the x coordinate of the white piece you want to move:\n");
	scanf("%d",&x_in);
    printf("enter the y coordinate of the white piece you want to move:\n");
	scanf("%d",&y_in);
	console_ask_for_move_white(ai,x_in,y_in);
}

void console_ask_for_piece_black(bool ai)
{
	if(ai)
	{
		move_to_dop answer = get_move(global_board,5,false,false);
		move(&global_board,(*answer)[0],(*answer)[1],(*answer)[2],(*answer)[3],false);
        print_move(answer);
		console_ask_for_piece_white(ai);
	}
	else
	{
		int x_in = -1;
		int y_in = -1;
        printf("enter the x coordinate of the black piece you want to move:\n");
		scanf("%d",&x_in);
        printf("enter the y coordinate of the black piece you want to move:\n");
		scanf("%d",&y_in);
		console_ask_for_move_black(ai,x_in,y_in);
	}
}

void console_ask_for_move_white(bool ai, int x_in, int y_in)
{
	int x_end = -1;
	int y_end = -1;
    printf("enter the x coordinate of where you want to move your white piece:\n");
	scanf("%d",&x_end);
	printf("enter the y coordinate of where you want to move your white piece:\n");
    scanf("%d",&y_end);
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
    printf("enter the x coordinate of where you want to move your black piece:\n");
	scanf("%d",&x_end);
    printf("enter the y coordinate of where you want to move your black piece:\n");
	scanf("%d",&y_end);
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
