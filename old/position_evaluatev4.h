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
typedef int evals_in[
8*4 + // pawns
2*(8+8-1) + //rooks
2*(8+8) + //bishops not sure this is correct
2*(4*2) + //knights
1*(8) + //king
1*(8+8+8+8)//queen
];
typedef int (*evals_inp)[
8*4 + // pawns
2*(8+8-1) + //rooks
2*(8+8) + //bishops not sure this is correct
2*(4*2) + //knights
1*(8) + //king
1*(8+8+8+8)//queen
];

//moves list only covers the distances moved

void call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);

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
    return 1*count;
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
    return 1*count;
}

boardp copy(board board_in)
{
    boardp board_out = malloc(sizeof(board));
    memcpy(board_out,board_in,sizeof(board));
    return board_out;
}

int min_max(evals_in list_in,int length, bool white_to_moveq, bool debug);
void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);


void position_evaluate(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug)
{
    
    if(depth == 0)
    {
	(*list_in)[(*list_in_index)] = (white_count(board_in,debug) - black_count(board_in,debug));
	(*list_in_index)++;
    }
    else
    {
	evals_inp list = malloc(sizeof(evals_in));
	int *list_index = malloc(sizeof(int));
	(*list_index) = 0;
	if(white_to_moveq)
	{
	    call_white(list,list_index,board_in, depth, white_to_moveq, debug);
	    (*list_in)[*list_in_index] = min_max(*list,*list_index,white_to_moveq,debug);
	    (*list_in_index)++;
	}
	else if(!white_to_moveq)
	{
	    call_black(list,list_index,board_in, depth, white_to_moveq, debug);
	    (*list_in)[*list_in_index] = min_max(*list,*list_index,white_to_moveq,debug);
	    (*list_in_index)++;
	}
	else
	{
	    assert(false);
	}
    }
}

int max(evals_in list_in,int length, bool debug) // move_value_list = list of int
{
    if (length == 0)
	return special;
    int current = list_in[0];
    for(int index = 0; index < length; index++)
    {
	if(current == special)
	{
	    current = list_in[index];
	}
	else if((list_in[index]) > current && list_in[index] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

int min(evals_in list_in,int length, bool debug)
{
    if (length == 0)
	return special;
    int current = list_in[0];
    for(int index = 0; index < length; index++)
    {
	if(current == special)
	{
	    current = list_in[index];
	}
	else if((list_in[index]) < current && list_in[index] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

int min_max(evals_in list_in,int length, bool white_to_moveq, bool debug)
{
    if(!white_to_moveq)
	return max(list_in,length, debug);
    else
	return min(list_in,length, debug);
}

void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug)
{
    int piece = blank;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case wpawn:
		    call_pawn(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wknight:
		    call_knight(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wking:
		    call_king(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wbishop:
		    call_bishop(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wrook:
		    call_rook(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wqueen:
		    call_queen(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
	    }
	}
}

void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug)
{
    int piece = blank;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case bpawn:
		    call_pawn(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bknight:
		    call_knight(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bking:
		    call_king(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bbishop:
		    call_bishop(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case brook:
		    call_rook(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bqueen:
		    call_queen(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
	    }
	}
}

typedef int moves_list[][2];
typedef int a_move[2];
/*
{change_x, change_y}
    int pawn_moves_white[4][2] = {
    {0,-1 },
    {1,-1 },
    {-1,-1},
    {0,-2}};
    int pawn_moves_black[4][2] = {
    {0,1 },
    {1,1 },
    {-1,1},
    {0,2}};*/

void call(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq, moves_list moves, int moves_list_length, bool debug)
{
    boardp ptr;
    for(int index = 0; index < moves_list_length; index++)
    {
	assert(valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]));
	ptr  = copy(board_in);
	position_evaluate(list_in,list_in_index,*move(ptr,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1],false),depth - 1,!white_to_moveq,debug);
	free(ptr);
    }
}

int random_global = 0;

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

void   call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 0;
    if(is_white(board_in[y_in][x_in]))
    {
	a_move white_moves_final[4];
	for(int index = 0; index < 4;index++)
	    if(valid(board_in,x_in,y_in,x_in + white_moves[index][0],y_in + white_moves[index][1]))
	    {
		white_moves_final[moves_list_length][0] = white_moves[index][0];
		white_moves_final[moves_list_length][1] = white_moves[index][1];
	    }
	call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, white_moves_final, moves_list_length,debug);
    }
    else if(is_black(board_in[y_in][x_in]))
    {
	a_move black_moves_final[4];
	for(int index = 0; index < 4;index++)
	    if(valid(board_in,x_in,y_in,x_in + black_moves[index][0],y_in + black_moves[index][1]))
	    {
		black_moves_final[moves_list_length][0] = black_moves[index][0];
		black_moves_final[moves_list_length][1] = black_moves[index][1];
	    }
	call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, black_moves_final, moves_list_length,debug);
    }
    //assert(false);
    //return 0;
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

void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 8;
    a_move final_knight_moves[8];
    int final_index = 0;
    for(int index = 0; index < moves_list_length;index++)
    {
	if(valid(board_in,x_in,y_in,x_in + knight_moves[index][0],y_in + knight_moves[index][1]))
	{
	    final_knight_moves[final_index][0] = x_in + knight_moves[index][0];
	    final_knight_moves[final_index][1] = y_in + knight_moves[index][1];
	    final_index++;
	}
    }
    call(list_in, list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_knight_moves, final_index,debug);
}

void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    a_move bishop_moves[8+8];
    int moves_list_length = 0;
    for(int x = 1, y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x++,y++)
    {
        a_move current = {x,y};
	//printf("bishop x: %d, y:%d\n",current[0],current[1]);
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1,y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x--,y++)
    {
        a_move current = {x,y};
	//printf("bishop x: %d, y:%d\n",current[0],current[1]);
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = 1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--,x++)
    {
        a_move current = {x,y};
	//printf("bishop x: %d, y:%d\n",current[0],current[1]);
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--,x--)
    {
        a_move current = {x,y};
	//printf("bishop x: %d, y:%d\n",current[0],current[1]);
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, bishop_moves, moves_list_length,debug);
}

void call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    call_rook(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq,debug);
    call_bishop(list_in,list_in_index,board_in,x_in,y_in,depth,white_to_moveq,debug);
    //return(min_max(list ,2,white_to_moveq,debug));
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

void call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 9;
    a_move final_king_moves[9];
    int final_index = 0;
    for(int index = 0; index < moves_list_length;index++)
    {
	if(valid(board_in,x_in,y_in,x_in + king_moves[index][0],y_in + king_moves[index][1]))
	{
	    final_king_moves[final_index][0] = king_moves[index][0];
	    final_king_moves[final_index][1] = king_moves[index][1];
	    final_index++;
	}
    }
    call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_king_moves, final_index,debug);
}

void call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    a_move rook_moves[8+8-2];
    int moves_list_length = 0;
    int x = 0;
    int y = 0;
    for(x = 1; valid(board_in,x_in,y_in,x_in + x,y_in);x++)
    {
	a_move current = {x,0};
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    y = 0;
    for(x = -1; valid(board_in,x_in,y_in,x_in + x,y_in);x--)
    {
	a_move current = {x,0};
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    x = 0;
    for(y = 1; valid(board_in,x_in,y_in,x_in,y_in + y);y++)
    {
	a_move current = {0,y};;
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    x = 0;
    for(y = -1; valid(board_in,x_in,y_in,x_in,y_in + y);y--)
    {
	a_move current = {0,y};;
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, rook_moves, moves_list_length,debug);
}

move_to_dop last_max(move_to_dop list_in[],int length, bool debug) // move_value_list = pointer to a list of int
{
    move_to_dop special_list = malloc(sizeof(move_to_do));
    move_to_do special_move = {special,-1,-1,-1,-1};
    memcpy(special_list,&special_move,sizeof(move_to_do));//sets up special list for return
    if (length == 0)
	return special_list;
    move_to_dop current = (list_in)[0];
    for(int index = 0; index < length; index++)
    {
	//move_to_dop answer = current;
	//printf("eval: %d x_in: %d y_in: %d x_end: %d y_end: %d\n",(*answer)[0],(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4]);
	if((*current)[0] == special)
	{
	    current = list_in[index];
	}
	else if((*(list_in[index]))[0] > (*current)[0] && (*(list_in[index]))[0] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

move_to_dop last_min(move_to_dop list_in[],int length, bool debug)
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
	    current = list_in[index];
	}
	else if((*(list_in[index]))[0] < (*current)[0] && (*(list_in[index]))[0] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

move_to_dop last_min_max(move_to_dop list_in[],int length, bool white_to_moveq, bool debug)
{
    if(!white_to_moveq)
	return last_max(list_in,length,debug);
    else
	return last_min(list_in,length,debug);
}

typedef move_to_dop moves_in[
    8*4 + // pawns
    2*(8+8-1) + //rooks
    2*(8+8) + //bishops not sure this is correct
    2*(4*2) + //knights
    1*(8) + //king
    1*(8+8+8+8)//queen
];
typedef moves_in *moves_inp;

void last_call_black(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void last_call_queen(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);
void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug);

move_to_dop get_move(board board_in, int depth,bool white_to_moveq, bool debug)
{
    moves_inp list = malloc(sizeof(moves_in));
    int *list_index = malloc(sizeof(int));
    *list_index = 0;
    if(white_to_moveq)
    {
	last_call_white(list,list_index,board_in, depth, white_to_moveq, debug);
	return last_min_max(*list,*list_index,white_to_moveq,debug);
    }
    else if(!white_to_moveq)
    {
	last_call_black(list,list_index,board_in, depth, white_to_moveq, debug);
	return last_min_max(*list,*list_index,white_to_moveq,debug);
    }
    else
    {
	assert(false);
    }
}

void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug)
{
    //white_to_moveq
    //list_in
    int piece = blank;
    //list_in_index
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case wpawn:
		    last_call_pawn(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wknight:
		    last_call_knight(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wking:
		    last_call_king(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wbishop:
		    last_call_bishop(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wrook:
		    last_call_rook(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case wqueen:
		    last_call_queen(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
	    }
	}
    //return(min_max(value_list,current_index,white_to_moveq,debug));
}

void last_call_black(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug)
{
    // use ! white_to_moveq// actually don't see comment on last_call_pawn min max
    //move_value_list value_list;
    int piece = blank;
    //int current_index = 0;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case bpawn:
		    last_call_pawn(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bknight:
		    last_call_knight(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bking:
		    last_call_king(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bbishop:
		    last_call_bishop(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case brook:
		    last_call_rook(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
		case bqueen:
		    last_call_queen(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,debug);
		break;
	    }
	}
    //return(min_max(value_list,current_index,white_to_moveq,debug));
}

typedef int move_array[
	8*4 +       //pawns
	2*(8+8-1) + //rooks
	2*(8+8) +   //bishops not sure this is correct
	2*(4*2) +   //knights
	1*(8) +     //king
	1*(8+8+8+8) //queen
	][4];
typedef int (*move_arrayp)[
	8*4 +       //pawns
	2*(8+8-1) + //rooks
	2*(8+8) +   //bishops not sure this is correct
	2*(4*2) +   //knights
	1*(8) +     //king
	1*(8+8+8+8) //queen
	][4];

boardp         boards_tofree  [8*4 + /*pawns*/ 2*(8+8-1) + /*rooks*/ 2*(8+8) + /*bishops not sure this is correct*/ 2*(4*2) + /*knights*/ 1*(8) + /*king*/ 1*(8+8+8+8)/*queen*/];
evals_inp      evals_tofree   [8*4 + /*pawns*/ 2*(8+8-1) + /*rooks*/ 2*(8+8) + /*bishops not sure this is correct*/ 2*(4*2) + /*knights*/ 1*(8) + /*king*/ 1*(8+8+8+8)/*queen*/];
move_arrayp move_arrays_tofree[8*4 + /*pawns*/ 2*(8+8-1) + /*rooks*/ 2*(8+8) + /*bishops not sure this is correct*/ 2*(4*2) + /*knights*/ 1*(8) + /*king*/ 1*(8+8+8+8)/*queen*/];


void last_call(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq, moves_list moves, int moves_list_length, bool debug)
{
    boardp ptr;
    evals_inp list_in_foreval = malloc(sizeof(evals_in));//memory leak
    //move_arrayp moves = malloc(sizeof(move_array));//memory leak
    move_to_dop current_move;//memory leak
    int *list_in_index_foreval = malloc(sizeof(int));
    (*list_in_index_foreval) = 0;
    for(int index = 0; index < moves_list_length; index++)
    {
		current_move = malloc(sizeof(move_to_do));
		assert(valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]));
		ptr  = copy(board_in);
		position_evaluate(list_in_foreval,list_in_index_foreval,*move(ptr,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1],false),depth - 1,!white_to_moveq,debug);
		assert((*list_in_foreval)[0] != special);
		move_to_do current_forcopy = {(*list_in_foreval)[0],x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]};
		memcpy(current_move,&current_forcopy,sizeof(move_to_do));
		(*list_in)[*list_in_index] = current_move;
		(*list_in_index)++;
		free(ptr);
    }
}

void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 0;
    if(is_white(board_in[y_in][x_in]))
    {
	a_move white_moves_final[4];
	for(int index = 0; index < 4;index++)
	    if(valid(board_in,x_in,y_in,x_in + white_moves[index][0],y_in + white_moves[index][1]))
	    {
		white_moves_final[moves_list_length][0] = white_moves[index][0];
		white_moves_final[moves_list_length][1] = white_moves[index][1];
	    }
	last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, white_moves_final, moves_list_length,debug);
    }
    else if(is_black(board_in[y_in][x_in]))
    {
	a_move black_moves_final[4];
	for(int index = 0; index < 4;index++)
	    if(valid(board_in,x_in,y_in,x_in + black_moves[index][0],y_in + black_moves[index][1]))
	    {
		black_moves_final[moves_list_length][0] = black_moves[index][0];
		black_moves_final[moves_list_length][1] = black_moves[index][1];
	    }
	last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, black_moves_final, moves_list_length,debug);
    }
    //return 0;
}

void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 8;
    a_move final_knight_moves[8];
    int final_index = 0;
    for(int index = 0; index < moves_list_length;index++)
    {
	if(valid(board_in,x_in,y_in,x_in + knight_moves[index][0],y_in + knight_moves[index][1]))
	{
	    final_knight_moves[final_index][0] = x_in + knight_moves[index][0];
	    final_knight_moves[final_index][1] = y_in + knight_moves[index][1];
	    final_index++;
	}
    }
    last_call(list_in, list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_knight_moves, final_index,debug);
}

void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    a_move bishop_moves[8+8];
    int moves_list_length = 0;
    for(int x = 1, y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x++,y++)
    {
        a_move current = {x,y};
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1,y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x--,y++)
    {
        a_move current = {x,y};
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = 1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x++,y--)
    {
        a_move current = {x,y};
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x--,y--)
    {
        a_move current = {x,y};
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, bishop_moves, moves_list_length,debug);
}

void last_call_queen(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    last_call_rook(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq,debug);
    last_call_bishop(list_in,list_in_index,board_in,x_in,y_in,depth,white_to_moveq,debug);
    //return(min_max(list ,2,white_to_moveq,debug));
}

void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    int moves_list_length = 9;
    a_move final_king_moves[9];
    int final_index = 0;
    for(int index = 0; index < moves_list_length;index++)
    {
	if(valid(board_in,x_in,y_in,x_in + king_moves[index][0],y_in + king_moves[index][1]))
	{
	    final_king_moves[final_index][0] = king_moves[index][0];
	    final_king_moves[final_index][1] = king_moves[index][1];
	    final_index++;
	}
    }
    last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_king_moves, final_index,debug);
}

void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    a_move rook_moves[8+8-2];
    int moves_list_length = 0;
    int x = 0;
    int y = 0;
    for(x = 1; valid(board_in,x_in,y_in,x_in + x,y_in);x++)
    {
	a_move current = {x,0};
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    y = 0;
    for(x = -1; valid(board_in,x_in,y_in,x_in + x,y_in);x--)
    {
	a_move current = {x,0};
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    x = 0;
    for(y = 1; valid(board_in,x_in,y_in,x_in,y_in + y);y++)
    {
	a_move current = {0,y};;
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    x = 0;
    for(y = -1; valid(board_in,x_in,y_in,x_in,y_in + y);y--)
    {
	a_move current = {0,y};;
	//printf("x: %d, y:%d\n",current[0],current[1]);
	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
	moves_list_length++;
    }
    last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, rook_moves, moves_list_length,debug);
}
