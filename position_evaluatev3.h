#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "valid.h"
#include "move.c"
#define special 20000000

typedef int move_to_do[5];
typedef int (*move_to_dop)[5];


int call_pawn(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
int call_knight(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
int call_bishop(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
int call_queen(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
int call_king(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
int call_rook(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);


int white_count(board board_in, bool debug){
    int count = 0;
    int item;
    for (int index = 0; index < 8; index++){
        for (int index2 = 0; index2 < 8; index2++){
            item = board_in[index][index2];
            switch(item){
		default:
		    break;
		case wpawn:
		    count += 1;
		    break;
		case wbishop:
		    count += 3;
		    break;
		case wknight:
		    count += 3;
		    break;
		case wqueen:
		    count += 9;
		    break;
		case wrook:
		    count += 5;
		    break;
		case wking:
		    count += 100;
		    break;
            }
        }
    }
    return 10000*count;
}

int black_count(board board_in, bool debug){
    int count = 0;
    int item;
    for (int index = 0; index < 8; index++){
        for (int index2 = 0; index2 < 8; index2++){
            item = board_in[index][index2];
            switch(item){
		default:
		    break;
		case bpawn:
		    count += 1;
		    break;
		case bbishop:
		    count += 3;
		    break;
		case bknight:
		    count += 3;
		    break;
		case bqueen:
		    count += 9;
		    break;
		case brook:
		    count += 5;
		    break;
		case bking:
		    count += 100;
		    break;
            }
        }
    }
    return 10000*count;
}

boardp copy(board board_in)
{
    boardp board_out = malloc(sizeof(board));
    memcpy(board_out,board_in,sizeof(board));
    return board_out;
}

typedef int move_value_list[(8 + 2 + 2 + 2 + 1 + 1)];
typedef move_value_list *move_value_listp;
typedef move_to_dop pointer_move_value_list[(8 + 2 + 2 + 2 + 1 + 1)];


int call_white(board board_in, int depth, bool white_to_moveq, bool debug);

int call_black(board board_in, int depth, bool white_to_moveq, bool debug);


int position_evaluate(board board_in, int depth, bool white_to_moveq, bool debug)
{
	if(depth == 0)
	{
	    return (white_count(board_in,debug) - black_count(board_in,debug));
	}
	else
	{
	    if(white_to_moveq)
	    {
		return call_white(board_in, depth, white_to_moveq, debug);
	    }
	    else if(!white_to_moveq)
	    {
		return call_black(board_in, depth, white_to_moveq, debug);
	    }
	    else
	    {
		assert(false);
	    }
	}
}

int max(move_value_list list_in,int length, bool white_to_moveq, bool debug) // move_value_list = pointer to a list of int
{
    //bool nullq = true;
    if (length == 0)
	return special;
    int current = list_in[0];
    //if length == 1 && list_in[0] == NULL
	//return NULL
    for(int index = 0; index < length; index++)
    {
	if(current == special)
	{
	    if (list_in[index] != special)
		current = list_in[index];
	}
	else if((list_in[index]) > current)
	{
	    current = list_in[index];
	}
    }
    return current;
}

int min(move_value_list list_in,int length, bool white_to_moveq, bool debug)
{
        //bool nullq = true;
    if (length == 0)
	return special;
    int current = list_in[0];
    //if length == 1 && list_in[0] == NULL
	//return NULL
    for(int index = 0; index < length; index++)
    {
	if(current == special)
	{
	    if (list_in[index] != special)
		current = list_in[index];
	}
	else if((list_in[index]) < current)
	{
	    current = list_in[index];
	}
    }
    return current;
}

int min_max(move_value_list list_in,int length, bool white_to_moveq, bool debug)
{
    if(white_to_moveq)
	return max(list_in,length, white_to_moveq, debug);
    else
	return min(list_in,length, white_to_moveq, debug);
}

int call_white(board board_in, int depth, bool white_to_moveq, bool debug)
{
	//white_to_moveq
    move_value_list value_list;
    int piece = blank;
    int current_index = 0;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case wpawn:
		    value_list[current_index] = call_pawn(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case wknight:
		    value_list[current_index] = call_knight(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case wking:
		    value_list[current_index] = call_king(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case wbishop:
		    value_list[current_index] = call_bishop(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case wrook:
		    value_list[current_index] = call_rook(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case wqueen:
		    value_list[current_index] = call_queen(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
	    }
	}
    return(min_max(value_list,current_index,white_to_moveq,debug));
}

int call_black(board board_in, int depth, bool white_to_moveq, bool debug)
{
	// use ! white_to_moveq// actually don't see comment on call_pawn min max
    move_value_list value_list;
    int piece = blank;
    int current_index = 0;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case bpawn:
			value_list[current_index] = call_pawn(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case bknight:
			value_list[current_index] = call_knight(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case bking:
			value_list[current_index] = call_king(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case bbishop:
			value_list[current_index] = call_bishop(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case brook:
			value_list[current_index] = call_rook(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
		case bqueen:
			value_list[current_index] = call_queen(board_in, x, y, depth, white_to_moveq,debug);
		    current_index++;
		break;
	    }
	}
    return(min_max(value_list,current_index,white_to_moveq,debug));
}

typedef int moves_list[][2];
typedef int a_move[2];

int call(board board_in,int x_in, int y_in,int depth,bool white_to_moveq, moves_list moves, int moves_list_length, bool debug)
{
	boardp ptr;
	move_value_list value_list;//a list of pointers
	int current_index = 0;
	//{change_x, change_y}
//	int pawn_moves_white[4][2] = {
//	{0,-1},
//	{1,-1},
//	{-1,-1},
//	{0,-2},
//	};
//	int pawn_moves_black[4][2] = {
//  {0,1},
//  {1,1},
//	{-1,1},
//	{0,2},
//  };
	for(int index = 0; index < moves_list_length; index++)
	{
	    if (valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]))
	    {
		    ptr  = copy(board_in);
		    value_list[current_index] = position_evaluate(*move(ptr,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1],false),depth - 1,white_to_moveq,debug);
		    current_index++;
		    free(ptr);
	    }
	}
	return(min_max(value_list,current_index,white_to_moveq,debug));//different white_moveq than other in max be careful this will screw stuff up
}


int random_global = 0;

int call_pawn(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
	int moves_list_length = 4;
	a_move white_moves[4] = {
		{0,-1},
		{-1,-1},
		{1,-1},
		{0,-2},
	};
	a_move black_moves[4] = {
		{0,1},
		{-1,1},
		{1,1},
		{0,2},
	};
	if(is_white(board_in[y_in][x_in]))
	{
		return(call(board_in,x_in, y_in,depth,white_to_moveq, white_moves, moves_list_length,debug));
	}
	else if(is_black(board_in[y_in][x_in]))
	{
		return(call(board_in,x_in, y_in,depth,white_to_moveq, black_moves, moves_list_length,debug));
	}
	assert(false);
	return 0;
}

a_move knight_moves[8] = {
            {2,3},
            {2,-3},
            {-2,3},
            {-2,-3},
            {3,2},
            {3,-2},
	    {-3,2},
	    {-3,-2},
        };

int call_knight(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
	int moves_list_length = 8;
	return(call(board_in,x_in, y_in,depth,white_to_moveq, knight_moves, moves_list_length,debug));
}

int call_bishop(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
	a_move rook_moves[8+8-2];
    int moves_list_length = 0;
    for(int x = 1, y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x++,y++)
    {
        a_move current = {x_in + x,y_in + y};
        memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1,y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x--,y++)
    {
        a_move current = {x_in + x,y_in + y};
        memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = 1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--,x++)
    {
        a_move current = {x_in + x,y_in + y};
        memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--,x--)
    {
        a_move current = {x_in + x,y_in + y};
        memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    return(call(board_in,x_in, y_in,depth,white_to_moveq, rook_moves, moves_list_length,debug));
}

int call_queen(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int (list)[2] = {call_rook(board_in,x_in, y_in,depth,white_to_moveq,debug),call_bishop(board_in,x_in,y_in,depth,white_to_moveq,debug)};
    return(min_max(list ,2,white_to_moveq,debug));
}

a_move king_moves[9] = {
    {0,1},
    {0,-1},
    {0,0},
    {1,1},
    {1,-1},
    {1,0},
    {-1,1},
    {-1,0},
    {-1,-1},
};

int call_king(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 9;
    return(call(board_in,x_in, y_in,depth,white_to_moveq, king_moves, moves_list_length,debug));
}

int call_rook(board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    a_move rook_moves[8+8-2];
    int moves_list_length = 0;
    for(int x = 1; valid(board_in,x_in,y_in,x_in + x,y_in);x++)
    {
	a_move current = {x_in + x,y_in};
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    for(int x = -1; valid(board_in,x_in,y_in,x_in + x,y_in);x--)
    {
	a_move current = {x_in + x,y_in};
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    for(int y = 1; valid(board_in,x_in,y_in,x_in,y_in + y);y++)
    {
	a_move current = {x_in,y_in + y};
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    for(int y = -1; valid(board_in,x_in,y_in,x_in,y_in + y);y--)
    {
	a_move current = {x_in,y_in + y};
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    return(call(board_in,x_in, y_in,depth,white_to_moveq, rook_moves, moves_list_length,debug));
}

move_to_dop last_max(pointer_move_value_list list_in,int length, bool white_to_moveq, bool debug) // move_value_list = pointer to a list of int
{
    move_to_dop special_list = malloc(sizeof(move_to_do));
    move_to_do special_move = {special,-1,-1,-1,-1};
    memcpy(special_list,&special_move,sizeof(move_to_do));//sets up special list for return
    if (length == 0)
	return special_list;
    move_to_dop current = (list_in)[0];
    for(int index = 0; index < length; index++)
    {
	if((*current)[0] == special)
	{
	    if ((*(list_in[index]))[0] != special)
		current = list_in[index];
	}
	else if((*(list_in[index]))[0] > (*current)[0] && (*(list_in[index]))[0] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

move_to_dop last_min(pointer_move_value_list list_in,int length, bool white_to_moveq, bool debug)
{
    move_to_dop special_list = malloc(sizeof(move_to_do));
    move_to_do special_move = {special,-1,-1,-1,-1};
    memcpy(special_list,&special_move,sizeof(move_to_do));//sets up special list for return
    if (length == 0)
	return special_list;
    move_to_dop current = (list_in)[0];
    for(int index = 0; index < length; index++)
    {
	if((*current)[0] == special)
	{
	    if ((*(list_in[index]))[0] != special)
		current = list_in[index];
	}
	else if((*(list_in[index]))[0] < (*current)[0] && (*(list_in[index]))[0] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

move_to_dop last_min_max(move_value_list list_in,int length, bool white_to_moveq, bool debug)
{
    if(white_to_moveq)
	return max(list_in,length, white_to_moveq, debug);
    else
	return min(list_in,length, white_to_moveq, debug);
}


move_to_dop get_move(board board_in, int depth,bool white_to_moveq, bool debug)
{
    
}
