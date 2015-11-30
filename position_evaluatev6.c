#ifndef position_evaluatev6D
#define position_evaluatev6D
#include "state.h"

//		      0     1     2      3     4       5       6     7     8      9     10      11      12
//                    blank,wking,wqueen,wrook,wbishop,wknight,wpawn,bking,bqueen,brook,bbishop,bknight,bpawn
int piece_values[] = {0    ,100  ,9     ,5    ,3      ,3       ,1   ,-100 ,-9    ,-5   ,-3     ,-3     ,-1};

int board_c = 0;

/*typedef int evals_in[
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
];*/

int carry_determine(board board_in, int x_end, int y_end, int carry,bool white_to_moveq)
{
    int piece_being_taken = board_in[y_end][x_end];
    return (carry - 10000*piece_values[piece_being_taken]);
}

void displayboard_norefresh(board board_in);

//moves list only covers the distances moved
//that last comment was important

int white_count(board board_in, int debug)
{
    (void)debug;
    int count = 0;
    int item;
    for (int index = 0; index < 8; index++){
        for (int index2 = 0; index2 < 8; index2++){
            item = board_in[index][index2];
            switch(item){
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
		default:
		    break;
            }
        }
    }
    return 10000*count;
}

int black_count(board board_in, int debug)
{
    (void)debug;
    int count = 0;
    int item;
    for (int index = 0; index < 8; index++){
        for (int index2 = 0; index2 < 8; index2++){
            item = board_in[index][index2];
            switch(item){
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
		default:
		    break;
            }
        }
    }
    return 10000*count;
}

int fast_board_count(board board_in)
{
    int count = 0;
    int item;
    for (int index = 0; index < 8; index++)
    {
        for (int index2 = 0; index2 < 8; index2++)
	{
            item = board_in[index][index2];
            count += piece_values[item];
        }
    }
    return 10000*count;
}

boardp copy(board board_in)
{
    ////assert(check_board(board_in));
    boardp board_out = malloc(sizeof(board));
    //guard copy_for_guard = {10,10,10,10,10,10,10,10};
    //memcpy(board_out + sizeof(board),&copy_for_guard,sizeof(guard));
    if(board_out == NULL)
    {
	printf("out of ram???\n");
	//assert(false);
    }
    memcpy(board_out,board_in,sizeof(board));
    //assert(check_board(*board_out));
    return board_out;
}

int position_evaluate(board board_in, int depth, bool white_to_moveq, int carry, int debug)
{
    assert(fast_board_count(board_in) == carry);
    #ifdef dotout
    int val = create_node_incomplete_final(depth);
    link_nodes(debug,val,depth);
    #endif
    (void)white_to_moveq;
    #ifdef memdebug
    assert(check_board(board_in));
    #endif
    if(depth == 0)
    {
	#ifdef dotout
	char * extra = malloc(sizeof(char[100]));
	sprintf(extra,"\nno min/max was taken\n just returned stuff\n white_to_moveq: %d\n",white_to_moveq);
	create_node_id(board_in,(white_count(board_in,debug) - black_count(board_in,debug)),val,extra,depth);
	free(extra);
	#endif
	#ifdef maxdebug
	assert(fast_board_count(board_in) == (white_count(board_in,debug) - black_count(board_in,debug))); 
	#endif
	if(fast_board_count(board_in) != carry)
	{
	    printcolored_board(board_in);
	    printf("\n%d\n",(white_count(board_in,debug) - black_count(board_in,debug)));
	    assert(false);
	}
	return (carry);
    }
    else
    {
    	evals_in list;
	    memset(&list,0,sizeof(evals_in));
    	int list_index = 0;
    	if(white_to_moveq)
    	    call_white(&list,&list_index,board_in, depth, white_to_moveq,carry, board_c);
    	else if(!white_to_moveq)
    	    call_black(&list,&list_index,board_in, depth, white_to_moveq,carry, board_c);
    	else
    	    assert(false);
	int other_out = min_max(list,list_index,white_to_moveq,debug,depth);
	#ifdef dotout
	char * extra = malloc(sizeof(char[100]));
	sprintf(extra,"\nmax(0/1): %d white_to_moveq: %d\n",white_to_moveq,white_to_moveq);
	create_node_id(board_in,other_out,val,extra,depth);
	free(extra);
	#endif
	return other_out;
    }
}

int max(evals_in list_in,int length)
{
    if (length == 0)
	return special;
    int current = list_in[0];
    for(int index = 0; index < length; index++)
    {
        if(current == special)
            current = list_in[index];
        else if((list_in[index]) > current && list_in[index] != special)
            current = list_in[index];
    }
    return current;
}

int min(evals_in list_in,int length)
{
    if (length == 0)
	return special;
    int current = list_in[0];
    for(int index = 1; index < length; index++)
    {
    	if(current == special)
    	    current = list_in[index];
    	else if((list_in[index]) < current && list_in[index] != special)
    	    current = list_in[index];
    }
    return current;
}

int min_max(evals_in list_in,int length, bool white_to_moveq, int debug,int depth)
{
    (void) depth;
    (void) white_to_moveq;
    (void)debug;
    if(white_to_moveq)
    	return max(list_in,length);
    else
    	return min(list_in,length);
}

void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq,int carry, int debug)
{
    ////assert(check_board(board_in));
    int piece = blank;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case wpawn:
		    call_pawn(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case wknight:
		    call_knight(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case wking:
		    call_king(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case wbishop:
		    call_bishop(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case wrook:
		    call_rook(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case wqueen:
		    call_queen(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
	    }
	}
}

void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq,int carry, int debug)
{
    ////assert(check_board(board_in));
    int piece = blank;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8; x++)
	{
	    piece = board_in[y][x];
	    switch(piece)
	    {
		case bpawn:
		    call_pawn(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case bknight:
		    call_knight(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case bking:
		    call_king(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case bbishop:
		    call_bishop(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case brook:
		    call_rook(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
		case bqueen:
		    call_queen(list_in,list_in_index,board_in, x, y, depth, white_to_moveq,carry,debug);
		break;
	    }
	}
}

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

void call(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq, moves_list moves, int moves_list_length,int carry, int debug)
{
    int x_end;
    int y_end;
    boardp ptr;
    for(int index = 0; index < moves_list_length; index++)
    {
        if(moves[index][0] != 0 || moves[index][1] != 0)
        {
	    #ifdef maxdebug
            assert(valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]));
	    #endif
	    x_end = x_in + moves[index][0];
	    y_end = y_in + moves[index][1];
            ptr  = copy(board_in);
	    ptr = move(ptr,x_in,y_in,x_end,y_end,false);
	    if(fast_board_count(*ptr) != carry_determine(board_in,x_end,y_end,carry,white_to_moveq))
	    {
		printf("carry:%d fast_board_count:%d\n",carry_determine(board_in,x_end,y_end,carry,white_to_moveq),fast_board_count(*ptr));
		printcolored_board(board_in);
		assert(false);
	    }
            (*list_in)[*list_in_index] = position_evaluate(*ptr,depth - 1,!white_to_moveq,carry_determine(board_in,x_end,y_end,carry,white_to_moveq),debug);
            (*list_in_index)++;
            free(ptr);
        }
        else{}
    }
}

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
a_move white_moves_pawn[4] = {
    {0,-1},
    {-1,-1},
    {1,-1},
    {0,-2},
};
a_move black_moves_pawn[4] = {
    {0,1},
    {-1,1},
    {1,1},
    {0,2},
};

int move_list_generate(board board_in, int x_in, int y_in,a_move (*final_moves)[], moves_list moves,int length,int debug)
{
    int count = 0;
    (void)debug;
    for(int index = 0; index < length; index++)
    {
	//if(debug)
	  //printf("move: x_in,y_in: %d,%d x,y: %d,%d, valid:%d\n",x_in,y_in,moves[index][0],moves[index][1],valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]));
	if(valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]))
	{
	    (*final_moves)[count][0] = moves[index][0];
	    (*final_moves)[count][1] = moves[index][1];
	    count++;
	}
    }
    return count;
}

void call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int carry, int debug)
{
    if(is_white(board_in[y_in][x_in]))
    {
    	a_move white_moves_final[4];
	int moves_list_length = move_list_generate(board_in,x_in,y_in,&white_moves_final,white_moves_pawn,4,debug);
    	call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, white_moves_final, moves_list_length,carry,debug);
    }
    else if(is_black(board_in[y_in][x_in]))
    {
    	a_move black_moves_final[4];
	int moves_list_length = move_list_generate(board_in,x_in,y_in,&black_moves_final,black_moves_pawn,4,debug);
	call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, black_moves_final, moves_list_length,carry,debug);
    }
}

a_move knight_moves[8] = {
    {1,2},
    {1,-2},
    {-1,2},
    {-1,-2},
    {2,1},
    {2,-1},
    {-2,1},
    {-2,-1},
};

void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int carry,int debug)
{
    #ifdef memdebug
    assert(check_board(board_in));
    #endif
    a_move final_knight_moves[8];
    int moves_list_length = move_list_generate(board_in,x_in,y_in,&final_knight_moves,knight_moves,8,debug);
    call(list_in, list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_knight_moves, moves_list_length,carry,debug);
}

void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int carry,int debug)
{
    #ifdef memdebug
    assert(check_board(board_in));
    #endif
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
    for(int x = 1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--,x++)
    {
        a_move current = {x,y};
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    for(int x = -1, y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--,x--)
    {
        a_move current = {x,y};
        memcpy(&(bishop_moves[moves_list_length]),&(current),sizeof(a_move));
        moves_list_length++;
    }
    call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, bishop_moves, moves_list_length,carry,debug);
}

void call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int carry,int debug)
{
    #ifdef memdebug
    assert(check_board(board_in));
    #endif
    call_rook(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq,carry,debug);
    call_bishop(list_in,list_in_index,board_in,x_in,y_in,depth,white_to_moveq,carry,debug);
}

a_move king_moves[8] = {
    {0,1},
    {0,-1},
    {1,1},
    {1,-1},
    {1,0},
    {-1,1},
    {-1,0},
    {-1,-1},
};

void call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int carry,int debug)
{
    #ifdef memdebug
    assert(check_board(board_in));
    #endif
    a_move final_king_moves[8];
    int moves_list_length = move_list_generate(board_in,x_in,y_in,&final_king_moves,king_moves,8,debug);
    call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_king_moves, moves_list_length,carry,debug);
}

void call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int carry,int debug)
{
    #ifdef memdebug
    assert(check_board(board_in));
    #endif
    a_move rook_moves[8+8-2];
    int moves_list_length = 0;
    int x = 0;
    int y = 0;
    for(x = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x++)
    {
    	a_move current = {x,y};
    	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
    	moves_list_length++;
    }
    y = 0;
    for(x = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);x--)
    {
    	a_move current = {x,y};
    	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
    	moves_list_length++;
    }
    x = 0;
    for(y = 1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y++)
    {
    	a_move current = {x,y};
    	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
    	moves_list_length++;
    }
    x = 0;
    for(y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--)
    {
    	a_move current = {x,y};
    	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
    	moves_list_length++;
    }
    call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, rook_moves, moves_list_length,carry,debug);
}

/*int slow_max(evals_in list_in,int length, int debug)
{
    (void) debug;
    evals_in clean;
    int len = 0;
    bool clean_inited = false;
    for(int i = 0; i < length;i++)
    {
	if(list_in[i] != special)
	{
	    clean[len] = list_in[i];
	    len++;
	    clean_inited = true;
	}
    }
    if(!clean_inited)
	return special;
    int max = clean[0];
    for(int i = 1;i < len;i++)
    {
	if(max < clean[i])
	    max = clean[i];
    }
    return max;
}

int slow_min(evals_in list_in,int length, int debug)
{
    (void) debug;
    evals_in clean;
    int len = 0;
    bool clean_inited = false;
    for(int i = 0; i < length;i++)
    {
	if(list_in[i] != special)
	{
	    //printf("added : %d\n",list_in[i]);
	    clean[len] = list_in[i];
	    len++;
	    clean_inited = true;
	}
    }
    if(!clean_inited)
	return special;
    int min = clean[0];
    for(int i = 1;i < len;i++)
    {
	if(min > clean[i])
	    min = clean[i];
    }
    return min;
}*/
#endif
