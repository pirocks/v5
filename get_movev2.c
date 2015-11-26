#include "state.h"

move_to_dop last_max(move_to_dop list_in[],int length, bool debug)
{
    if(debug)printf("debug: max: length: %d",length);
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
            //assert(false);
        }
        else if((*(list_in[index]))[0] > (*current)[0] && (*(list_in[index]))[0] != special)
        {
            //free(current);
            current = list_in[index];
        }
    }
    return current;
}

move_to_dop last_min(move_to_dop list_in[],int length, bool debug)
{
    if(debug)printf("debug: max: length: %d",length);
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
	        //assert(false);
    	}
    	else if((*(list_in[index]))[0] < (*current)[0] && (*(list_in[index]))[0] != special)
    	{
            //free(current);
            current = list_in[index];
	    }
    }
    return current;
}

move_to_dop last_min_max(move_to_dop list_in[],int length, bool white_to_moveq, bool debug,int depth)
{
    (void) depth;
    return last_max(list_in,length,debug);
    /*if(white_to_moveq)
	    return last_max(list_in,length,debug);
    else
	    return last_min(list_in,length,debug);*/
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

move_to_dop get_move(board board_in, int depth,bool white_to_moveq, bool debug)
{
    ////assert(check_board(board_in));
    moves_in list;
    memset(&list,0,sizeof(moves_in));
    int list_index = 0;
    if(white_to_moveq)
	    last_call_white(&list,&list_index,board_in, depth, white_to_moveq, debug);
    else if(!white_to_moveq)
    	last_call_black(&list,&list_index,board_in, depth, white_to_moveq, debug);
    return last_min_max(list,list_index,white_to_moveq,debug,depth);
}

void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug)
{
    ////assert(check_board(board_in));
    //assert(white_to_moveq);
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
    ////assert(check_board(board_in));
    //assert(!white_to_moveq);
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

//boardp       boards_tofree  [8*4 + /*pawns*/ 2*(8+8-1) + /*rooks*/ 2*(8+8) + /*bishops not sure this is correct*/ 2*(4*2) + /*knights*/ 1*(8) + /*king*/ 1*(8+8+8+8)/*queen*/];
//evals_inp    evals_tofree   [8*4 + /*pawns*/ 2*(8+8-1) + /*rooks*/ 2*(8+8) + /*bishops not sure this is correct*/ 2*(4*2) + /*knights*/ 1*(8) + /*king*/ 1*(8+8+8+8)/*queen*/];
move_arrayp move_arrays_tofree[8*4 + /*pawns*/ 2*(8+8-1) + /*rooks*/ 2*(8+8) + /*bishops not sure this is correct*/ 2*(4*2) + /*knights*/ 1*(8) + /*king*/ 1*(8+8+8+8)/*queen*/];

/*typedef move_to_dop moves_in[
    8*4 + // pawns
    2*(8+8-1) + //rooks
    2*(8+8) + //bishops not sure this is correct
    2*(4*2) + //knights
    1*(8) + //king
    1*(8+8+8+8)//queen
];
typedef moves_in *moves_inp;*/

void last_call(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq, moves_list moves, int moves_list_length, bool debug)
{
    ////assert(check_board(board_in));
    printf("\nlast call %d\n",moves_list_length);
    boardp ptr;
    evals_in list_in_foreval;
    memset(&list_in_foreval,0,sizeof(evals_in));
    printf("length: %d\n",*list_in_index);
    printf("moves list length: %d\n", moves_list_length);
    ////assert(check_board(board_in));
    if(debug)for(int i = 0; i < *list_in_index;i++)print_move((*list_in)[i]);
    for(int index = 0; index < moves_list_length; index++)
    {
        assert(valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]));
        ////assert(check_board(board_in));
        ptr  = copy(board_in);
        ////assert(check_board(board_in));
        //assert(check_board(*ptr));
        list_in_foreval[index] = -1*position_evaluate(*move(ptr,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1],false),depth - 1,!white_to_moveq,false);
        //displayboard_norefresh(*ptr);
        //assert(check_board(*ptr));
        free(ptr);
        /*if((list_in_foreval)[index] == special)
        {
            list_in_foreval[index] = -1*position_evaluate(*move(ptr,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1],false),depth - 1,!white_to_moveq,debug);
            assert(false);
        }*/
    }
    //results recorded
    move_to_dop current_move;
    for(int index = 0; index < moves_list_length; index++)
    {
        //assert((*list_in)[*list_in_index] == NULL);
        current_move = malloc(sizeof(move_to_do));
        move_to_do current_forcopy = {list_in_foreval[index],x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]};
        memcpy(current_move,&current_forcopy,sizeof(move_to_do));
        (*list_in)[*list_in_index] = current_move;
        (*list_in_index)++;
    }
    for(int i = 0; i < *list_in_index;i++)print_move((*list_in)[i]);
    //results copied
}

/*int move_list_generate(board board_in, int x_in, int y_in,a_move (*final_moves)[], moves_list moves,int length)
{
    int count = 0;
    for(int index = 0; index < length; index++)
	if(valid(board_in,x_in,y_in,x_in + moves[index][0],y_in + moves[index][1]))
	{
	    (*final_moves)[count][0] = moves[index][0];
	    (*final_moves)[count][1] = moves[index][1];
	    count++;
	}
    return count;
}*/

void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    ////assert(check_board(board_in));
    if(is_white(board_in[y_in][x_in]))
    {
    	a_move white_moves_final[4];
	int moves_list_length = move_list_generate(board_in,x_in,y_in,&white_moves_final,white_moves_pawn,4,debug);
    	last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, white_moves_final, moves_list_length,debug);
    }
    else if(is_black(board_in[y_in][x_in]))
    {
    	a_move black_moves_final[4];
    	int moves_list_length = move_list_generate(board_in,x_in,y_in,&black_moves_final,black_moves_pawn,4,debug);
    	last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, black_moves_final, moves_list_length,debug);
    }
}

void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug)
{
    ////assert(check_board(board_in));
    printf("knight\n");
    a_move final_knight_moves[8];
    int moves_list_length = move_list_generate(board_in,x_in,y_in,&final_knight_moves,knight_moves,8,debug);
    for(int i =0; i < moves_list_length;i++)printf("x:%d, y:%d\n",final_knight_moves[i][0],final_knight_moves[i][1]);
    last_call(list_in, list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_knight_moves, moves_list_length,false);
}

void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    ////assert(check_board(board_in));
    printf("bishop");
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
    ////assert(check_board(board_in));
    printf("queen");
    last_call_rook(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq,debug);
    last_call_bishop(list_in,list_in_index,board_in,x_in,y_in,depth,white_to_moveq,debug);
}

void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    ////assert(check_board(board_in));
    printf("king");
    a_move final_king_moves[8];
    int moves_list_length = move_list_generate(board_in,x_in,y_in,&final_king_moves,king_moves,8,debug);
    last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, final_king_moves, moves_list_length,debug);
}

void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   bool debug)
{
    ////assert(check_board(board_in));
    printf("rook");
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
    	a_move current = {0,y};
    	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
    	moves_list_length++;
    }
    x = 0;
    for(y = -1; valid(board_in,x_in,y_in,x_in + x,y_in + y);y--)
    {
    	a_move current = {0,y};
    	memcpy(&(rook_moves[moves_list_length]),&(current),sizeof(a_move));
    	moves_list_length++;
    }
    last_call(list_in,list_in_index,board_in,x_in, y_in,depth,white_to_moveq, rook_moves, moves_list_length,debug);
}
