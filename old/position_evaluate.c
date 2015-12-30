#include <pthread.h>
#include <string.h>
#include "move.c"
#define special 20000000

//                         {blank,wking  ,wqueen,wrook,wbishop,wknight,wpawn,bking   ,bqueen,brook ,bbishop,bknight,bpawn };
int list_for_count[] =     {0    ,1000000,90000 ,50000,30000  ,30000  ,10000,-1000000,-90000,-50000,-30000 ,-30000 ,-10000};

int point_determine(int piece_in)
{
    return(list_for_count[piece_in]);
}

int carry_determine(board board_in,int x_in,int y_in, int x_end, int y_end, int carry, int white_to_moveq)
{
    //print_board(board_in);
    //printf("carry: %d board_in[y_end][x_end]: %d Y_in %d x_in %d y_end %d x_end %d\n",carry,board_in[y_end][x_end],y_in,x_in,y_end,x_end);
    return(carry - point_determine(board_in[y_end][x_end]));
}

int white_count(board board_in){
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

int black_count(board board_in){
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

int board_count(board board_in)
{
    int count = 0;
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
	{
            int item = board_in[y][x];
	    count += (list_for_count[item] /*- abs((x-4)*(y-4)))*/);
	}
    return count;
}

boardp copy(board board_in)
{
    boardp board_out = malloc(sizeof(board));
    memcpy(board_out,board_in,sizeof(board));
    return board_out;
}

int min(int list_in[],int length)
{
    int current = special;
    for(int index = 0; index < length; index++)
    {
	if(current == special)
	{
	    current = list_in[index];
	}
	else if(list_in[index] > current  && list_in[index] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}

int max(int list_in[],int length)
{
    int current = special;
    for(int index = 0; index < length; index++)
    {
	if(current == special)
	{
	    current = list_in[index];
	}
	else if(list_in[index] > current && list_in[index] != special)
	{
	    current = list_in[index];
	}
    }
    return current;
}


int min_max(int list[],int current_index,bool white_to_moveq)
{
    ////printf("[");
    //for (int index = 0;index < current_index; index++)
    //{
	////printf("%f,",list[index]);
	//if(list[index] > special.0)
	//{
	    ////printf("\ncurrent index: %d",current_index);
	    //assert(current_index < 60);
	    //assert(list[index] < 2001.0);
	//}
    //}
    if (white_to_moveq)
    {
	//printf("] --list - answer: %f -current index: %d\n max",max(list,current_index),current_index);
	return(max(list,current_index));
    }
    else
    {
	//printf("] --list - answer: %f -current index: %d\n min",min(list,current_index),current_index);
	return(min(list,current_index));
    }
}

int position_evaluate(board board_in, int depth, bool white_to_moveq,int carry);

int call_pawn_white(board board_in, int x_in, int y_in, int depth, bool white_to_moveq,int carry)
{
    //printf("\ncalled 3\n");	
    int list[4];
    int current_index = 0;
    boardp ptr;
    if (w_pawn(board_in, x_in, y_in, x_in + 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move(ptr, x_in, y_in, x_in + 1, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_pawn(board_in, x_in, y_in, x_in - 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_pawn(board_in, x_in, y_in, x_in, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_pawn(board_in, x_in, y_in, x_in, y_in - 2))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 2,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in - 2, carry, white_to_moveq));
	//if (x_in == 3)
	    //printf("position eval:%d\n",list[current_index]);
	current_index++;
	free(ptr);
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_pawn_black(board board_in, int x_in, int y_in, int depth, bool white_to_moveq,int carry)
{
    assert(!white_to_moveq);
    int list[4];
    int current_index = 0;
    boardp ptr;
    if (b_pawn(board_in, x_in, y_in, x_in + 1, y_in + 1))
    {
	ptr = copy(board_in);
	//printf("\n\neval: %f\n\n",position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq));
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_pawn(board_in, x_in, y_in, x_in - 1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_pawn(board_in, x_in, y_in, x_in, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_pawn(board_in, x_in, y_in, x_in, y_in + 2))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 2,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in + 2, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_knight(board board_in, int x_in, int y_in, int depth, bool white_to_moveq, bool whiteq,int carry)
{
    int list[8];
    int current_index = 0;
    boardp ptr;
    if (knight(board_in, x_in, y_in, x_in + 1, y_in + 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 2,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in + 2, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 1, y_in + 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 2,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in + 2, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in + 1, y_in - 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in - 2,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in - 2, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 1, y_in - 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 2,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in - 2, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in + 2, y_in + 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 2, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 2, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 2, y_in + 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 2, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 2, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in + 2, y_in - 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 2, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 2, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 2, y_in - 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 2, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 2, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_king_white(board board_in, int x_in, int y_in, int depth, bool white_to_moveq,int carry)
{
    int list[8];
    int current_index = 0;
    boardp ptr;
    if (w_king(board_in, x_in, y_in, x_in + 1, y_in))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in - 1, y_in))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in + 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in - 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in +  1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in - 1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_king_black(board board_in, int x_in, int y_in, int depth, bool white_to_moveq,int carry)
{
    int list[8];
    int current_index = 0;
    boardp ptr;
    if (b_king(board_in, x_in, y_in, x_in + 1, y_in))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in - 1, y_in))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in + 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in - 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in, y_in - 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in +  1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in + 1, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    if (b_king(board_in, x_in, y_in, x_in - 1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 1,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, x_in - 1, y_in + 1, carry, white_to_moveq));
	current_index++;
	free(ptr);
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_rook(board board_in, int x_in, int y_in, int depth, bool white_to_moveq, bool whiteq,int carry)
{
    int list[16 - 1];
    int current_index = 0;
    int currentx = x_in;
    int currenty = y_in;
    boardp ptr;
    while (true)
    {
	currentx++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currentx--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currenty++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currenty = y_in;
    while (true)
    {
	currenty--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_bishop(board board_in, int x_in, int y_in, int depth, bool white_to_moveq, bool whiteq,int carry)
{
    int list[16 - 1];
    int current_index = 0;
    int currentx = x_in;
    int currenty = y_in;
    boardp ptr;
    while (true)
    {
	currentx++;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx++;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    return(min_max(list,current_index,white_to_moveq));
}

int call_queen(board board_in, int x_in, int y_in, int depth, bool white_to_moveq, bool whiteq,int carry)
{
    int list[2*16 - 1];
    int current_index = 0;
    int currentx = x_in;
    int currenty = y_in;
    boardp ptr;
    while (true)
    {
	currentx++;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx++;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty--;
	if (queen(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    //rook
    while (true)
    {
	currentx++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currentx--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currenty++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currenty = y_in;
    while (true)
    {
	currenty--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,carry_determine(board_in,x_in,y_in, currentx, currenty, carry, white_to_moveq));
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    return(min_max(list,current_index,white_to_moveq));
}

int position_evaluate(board board_in, int depth, bool white_to_moveq,int carry)
{
    //assert(carry == board_count(board_in));
    if (depth == 0)
    {
	//printf("%f\n",white_count(board_in) - black_count(board_in));
	//return (white_count(board_in) - black_count(board_in));
	//if(board_count(board_in) != carry)
	//{
	    //print_board(board_in);
	    //printf("\nboard_count: %d carry: %d\n",board_count(board_in),carry);
	//}
	//printf("\n%d\n",board_count(board_in));
	//assert(board_count(board_in) == carry);
	if(white_count(board_in) - black_count(board_in) == -30000)
	{
	    //printf("white_to_move:%d depth: %d",white_to_moveq,depth);
	    //displayboard(board_in);
	    //print_board(board_in);
	    //SDL_Delay(2000);
	}
	if(same_boardq(board_in,global_board_debug))printf("here\n");
	return (white_count(board_in) - black_count(board_in));
    }
    else 
    {
	int value_list[(8 + 2 + 2 + 2 + 1 + 1)];//pawns, rooks,bishops,knights, queen, king
	int current_index = 0;
	int piece;
	for (int yindex = 0; yindex < 8; yindex++)
	{
	    for (int xindex = 0; xindex < 8; xindex++)
	    {
		if (board_in[yindex][xindex] != blank  )
		{
		    piece = board_in[yindex][xindex];
		    if (is_white(piece) && white_to_moveq)
		    {
			switch(piece)
			{
			    case wpawn:
				//printf("\ncall pawn white :%f\n",call_pawn_white(board_in, xindex, yindex, depth, white_to_moveq));
				value_list[current_index] = call_pawn_white(board_in, xindex, yindex, depth, white_to_moveq,carry);
				current_index++;
				break;
			    case wknight:
				value_list[current_index] = call_knight(board_in, xindex, yindex, depth, white_to_moveq, true,carry);
				current_index++;
				break;
			    case wking:
				value_list[current_index] = call_king_white(board_in, xindex, yindex, depth, white_to_moveq,carry);
				current_index++;
				break;
			    case wrook:
				value_list[current_index] = call_rook(board_in, xindex, yindex, depth, white_to_moveq, true,carry);
				current_index++;
				break;
			    case wbishop:
				value_list[current_index] = call_bishop(board_in, xindex, yindex, depth, white_to_moveq, true,carry);
				current_index++;
				break;
			    case wqueen:
				value_list[current_index] = call_queen(board_in, xindex, yindex, depth, white_to_moveq, true,carry);
				current_index++;
				break;
			}
		    }
		    else if (is_black(piece) && (!white_to_moveq))
		    {
			switch(piece)
			{
			    case bpawn:
				//printf("\ncall pawn black :%f\n",call_pawn_black(board_in, xindex, yindex, depth, white_to_moveq));
				value_list[current_index] = call_pawn_black(board_in, xindex, yindex, depth, white_to_moveq,carry);
				current_index++;
				break;
			    case bknight:
				value_list[current_index] = call_knight(board_in, xindex, yindex, depth, white_to_moveq, false,carry);
				current_index++;
				break;
			    case bking:
				value_list[current_index] = call_king_black(board_in, xindex, yindex, depth, white_to_moveq,carry);
				current_index++;
				break;
			    case brook:
				value_list[current_index] = call_rook(board_in, xindex, yindex, depth, white_to_moveq, false,carry);
				current_index++;
				break;
			    case bbishop:
				value_list[current_index] = call_bishop(board_in, xindex, yindex, depth, white_to_moveq, false,carry);
				current_index++;
				break;
			    case bqueen:
				//printf("queen x: %d y: %d\n",xindex,yindex);
				value_list[current_index] = call_queen(board_in, xindex, yindex, depth, white_to_moveq, false,carry);
				current_index++;
				break;
			}
		    }
		    else
		    {
			//printf("wtf");
			//printf("white?: %d  white to move: %d piece: %d\n",is_white(piece),white_to_moveq,piece);
			//all pieces that don't move
		    }
		}
		else
		{
		    //
		    //blank   piece
		    //
		}
	    }
	}
	return(min_max(value_list,current_index,white_to_moveq));
    }
    return(2000000000);
}

typedef int move_to_do[5];
typedef int (*move_to_dop)[5];

typedef struct
{
    board board_in;
    int x_in;
    int y_in;
    int depth;
    bool white_to_moveq;
    bool whiteq;
    int value_list_index;
} arg_data ;

typedef arg_data *arg_datap;

void print_move(move_to_do move_in)
{
    printf("eval: %d x_in: %d y_in: %d x_end: %d y_end: %d\n",(move_in)[0],(move_in)[1],(move_in)[2],(move_in)[3],(move_in)[4]);
}

move_to_do value_list[(8 + 2 + 2 + 2 + 1 + 1)];/*pawns, rooks,bishops,knights, queen, king*/

move_to_dop last_min(move_to_dop list_in[],int length,bool debugin)
{
    printf("min");
    /*if(debugin)printf("min");
    if (current_index == 0)
    {
	move_to_do copy_in = {special,-1,-1,-1,-1};
	move_to_dop two_thousand = malloc(sizeof(move_to_do));
	memcpy(two_thousand,&copy_in,sizeof(move_to_do));
	return(two_thousand);
    }
    move_to_dop min = malloc(sizeof(move_to_do));
    memcpy(min,list[0],sizeof(move_to_do));
    for(int index = 0;index < (current_index); index++ )
    {
	if((*min)[0] == -special || (*min)[0] == special)
	{
	    if(index < current_index - 1)
		index++;
	    else
	    {
		move_to_do copy_in = {special,-1,-1,-1,-1};
		memcpy(min,&copy_in,sizeof(move_to_do));
		return min;
	    }
	}
	if (list[index][0] < (*min)[0])
	    if (list[index][0] != special && list[index][0] != -special)
		memcpy(min,list[index],sizeof(move_to_do));
	if(debugin)printf("%d,",(*min)[0]);
    }
    if(debugin)printf("result:%d",(*min)[0]);
    return min;*/
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

move_to_dop last_max(move_to_dop list_in[],int length,bool debugin)
{
    printf("max");
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

move_to_dop last_min_max(move_to_do list[],int current_index,bool white_to_moveq,bool debugin)
{
    move_to_dop list_in[32];
    move_to_dop current;
    for(int index = 0; index < current_index; index++)
    {
	print_move(list[index]);
	current = malloc(sizeof(move_to_do));
	memcpy(current,&(list[index]),sizeof(move_to_do));
	memcpy(&(list_in[index]),&current,sizeof(move_to_dop));
	print_move(*(list_in[index]));
    }
    if (white_to_moveq)
    {
	return(last_max(list_in,current_index,debugin));
    }
    else
    {
	return(last_min(list_in,current_index,debugin));
    }
}

//move_to_dop last_call_pawn_white(board board_in, int x_in, int y_in, int depth, bool white_to_moveq)
void *last_call_pawn_white(void *arg)
{
    printf("\ncalled 2\n");
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    //int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[4];
    int current_index = 0;
    boardp ptr;
    if (w_pawn(board_in, x_in, y_in, x_in + 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move(ptr, x_in, y_in, x_in + 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (w_pawn(board_in, x_in, y_in, x_in - 1, y_in - 1))
    {
	ptr = copy(board_in);
	//printf("called1 %f\n",position_evaluate((*move(ptr, x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr)));
	list[current_index][0] = position_evaluate((*move(ptr, x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (w_pawn(board_in, x_in, y_in, x_in, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    printf("\ncalled 1\n");
    if (w_pawn(board_in, x_in, y_in, x_in, y_in - 2))
    {
	printf("\ncalled final\n");
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 2,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in - 2;
	current_index++;
	free(ptr);
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

void *last_call_pawn_black(void *arg)
{
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,&(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    //int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[4];
    int current_index = 0;
    boardp ptr;
    if (b_pawn(board_in, x_in, y_in, x_in + 1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (b_pawn(board_in, x_in, y_in, x_in - 1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (b_pawn(board_in, x_in, y_in, x_in, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (b_pawn(board_in, x_in, y_in, x_in, y_in + 2))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 2,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in + 2;
	current_index++;
	free(ptr);
    }
    move_to_dop ptr2;
    //print_board(board_in);
    //print_board(global_board_debug);
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

void *last_call_knight(void *arg)
{
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[8];
    int current_index = 0;
    boardp ptr;
    if (knight(board_in, x_in, y_in, x_in + 1, y_in + 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 2,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in + 2;
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 1, y_in + 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 2,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in + 2;
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in + 1, y_in - 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in - 2,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in - 2;
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 1, y_in - 2,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 2,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in - 2;
	current_index++;
	free(ptr);
    }
    //printf("knight %d\n",(knight(board_in, x_in, y_in, x_in + 2, y_in + 1,whiteq)));
    //print_board(board_in);
    if (knight(board_in, x_in, y_in, x_in + 2, y_in + 1,whiteq))
    {
	ptr = copy(board_in);
	debug = true;
	//printf("\n\nin position eval: %f\n\n",position_evaluate((*move((ptr), x_in, y_in, x_in + 2, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr)));
	debug = false;
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 2, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 2;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 2, y_in + 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 2, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 2;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in + 2, y_in - 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 2, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 2;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (knight(board_in, x_in, y_in, x_in - 2, y_in - 1,whiteq))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 2, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 2;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

void *last_call_king_white(void *arg)
{
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    //int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[8];
    int current_index = 0;
    boardp ptr;
    if (w_king(board_in, x_in, y_in, x_in + 1, y_in))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in - 1, y_in))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in + 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in - 1, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in, y_in - 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in +  1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (w_king(board_in, x_in, y_in, x_in - 1, y_in + 1))
    {
	ptr = copy(board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

void displayboard(board board_in);

void *last_call_king_black(void *arg)
{
    arg_datap args = (arg_datap)arg;
    boardp board_in;
    board_in = &((*args).board_in);
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    //int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
 //   printf("\n\nx_in:%d y_in:%d depth:%d\n\n",x_in,y_in,depth);
    //print_board(*board_in);
    //displayboard(*board_in);
    //assert(false);
    move_to_do list[8];
    int current_index = 0;
    boardp ptr;
    if (b_king(*board_in, x_in, y_in, x_in + 1, y_in))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in - 1, y_in))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in + 1, y_in - 1))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in - 1, y_in - 1))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in, y_in + 1))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in, y_in - 1))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in, y_in - 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in;
	list[current_index][4] = y_in - 1;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in +  1, y_in + 1))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in + 1, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in + 1;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    if (b_king(*board_in, x_in, y_in, x_in - 1, y_in + 1))
    {
	ptr = copy(*board_in);
	list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, x_in - 1, y_in + 1,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	list[current_index][1] = x_in;
	list[current_index][2] = y_in;
	list[current_index][3] = x_in - 1;
	list[current_index][4] = y_in + 1;
	current_index++;
	free(ptr);
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

void *last_call_rook(void *arg)
{
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[16 - 1];
    int current_index = 0;
    int currentx = x_in;
    int currenty = y_in;
    boardp ptr;
    while (true)
    {
	currentx++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currentx--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currenty++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currenty = y_in;
    while (true)
    {
	currenty--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    pthread_exit(NULL);
    return NULL;
}

void *last_call_bishop(void *arg)
{
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[16 - 1];
    int current_index = 0;
    int currentx = x_in;
    int currenty = y_in;
    boardp ptr;
    while (true)
    {
	currentx++;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx++;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

void *last_call_queen(void *arg)
{
    arg_datap args = (arg_datap)arg;
    board board_in;
    memcpy(board_in,(*args).board_in,sizeof(board));
    int x_in = (*args).x_in;
    int y_in = (*args).y_in;
    int depth = (*args).depth;
    int white_to_moveq = (*args).white_to_moveq;
    int whiteq = (*args).whiteq;//delete later
    int value_list_index = (*args).value_list_index;
    move_to_do list[2*16 - 1];
    int current_index = 0;
    int currentx = x_in;
    int currenty = y_in;
    boardp ptr;
    while (true)
    {
	currentx++;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {	
	currentx--;
	currenty++;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
	currentx--;
	currenty++;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx++;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    while (true)
    {
	currentx--;
	currenty--;
	if (bishop(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    currenty = y_in;
    //rook
    while (true)
    {
	currentx++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currentx--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currentx = x_in;
    while (true)
    {
	currenty++;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    currenty = y_in;
    while (true)
    {
	currenty--;
	if (rook(board_in,x_in,y_in,currentx,currenty,whiteq))
	{
	    ptr = copy(board_in);
	    list[current_index][0] = position_evaluate((*move((ptr), x_in, y_in, currentx,currenty,false)), depth - 1, !white_to_moveq,board_count(*ptr));
	    list[current_index][1] = x_in;
	    list[current_index][2] = y_in;
	    list[current_index][3] = currentx;
	    list[current_index][4] = currenty;
	    current_index++;
	    free(ptr);
	}
	else
	    break;
    }
    move_to_dop ptr2;
    ptr2 = last_min_max(list,current_index,white_to_moveq,false);
    memcpy(&(value_list[value_list_index]),ptr2,sizeof(move_to_do));
    free(ptr2);
    free(args);
    pthread_exit(NULL);
    return NULL;
}

arg_datap copy_args(arg_data in)
{
    arg_datap out = malloc(sizeof(arg_data));
    *out = in;
    return out;
}

int *copy_int(int in)
{
    int *out = malloc(sizeof(int));
    *out = in;
    return out;
}

pthread_t threads[16];

int thread_index = 0;

move_to_dop get_move(board board_in, int depth, bool white_to_moveq)
{
    arg_datap ptr2;
    arg_data args;
    thread_index = 0;
    int current_index = 0;
    int piece;
    for (int yindex = 0; yindex < 8; yindex++)
    {
	for (int xindex = 0; xindex < 8; xindex++)
	{
	    if (board_in[yindex][xindex] != blank  )
	    {
		piece = board_in[yindex][xindex];
		if (is_white(piece) && white_to_moveq)
		{
		    memcpy(&(args.board_in),board_in,sizeof(board));
		    args.x_in = xindex;
		    args.y_in = yindex;
		    args.depth = depth;
		    args.white_to_moveq = white_to_moveq;
		    args.value_list_index = *copy_int(current_index);
		    args.whiteq = true;
		    switch(piece)
		    {
			case wpawn:
			    printf("wpawn");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_pawn_white,ptr2);
			    //last_call_pawn_white(ptr2);
			    break;
			case wknight:
			    printf("wknight");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_knight,ptr2);
			    //last_call_knight(ptr2);
			    break;
			case wking:
			    printf("wking");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_king_white,ptr2);
			    //last_call_king_white(ptr2);
			    break;
			case wrook:
			    printf("wrook");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_rook,ptr2);
			    //last_call_rook(ptr2);
			    break;
			case wbishop:
			    printf("wbishop");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_bishop,ptr2);
			    //last_call_bishop(ptr2);
			    break;
			case wqueen:
			    printf("wqueen");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_queen,ptr2);
			    //last_call_queen(ptr2);
			    break;
		    }
		    current_index++;
		    thread_index++;
		}
		else if ((!white_to_moveq) && is_black(piece))
		{
		    memcpy(&(args.board_in),board_in,sizeof(board));
		    args.x_in = xindex;
		    args.y_in = yindex;
		    args.depth = depth;
		    args.white_to_moveq = white_to_moveq;
		    args.value_list_index = *copy_int(current_index);
		    args.whiteq = false;
		    switch(piece)
		    {
			case bpawn:
			    printf("bpawn");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_pawn_black,ptr2);
			    //last_call_pawn_black(ptr2);
			    break;
			case bknight:
			    printf("bknight");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_knight,ptr2);
			    //last_call_knight(ptr2);
			    break;
			case bking:
			    printf("bking");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_king_black,ptr2);
			    //last_call_king_black(ptr2);
			    break;
			case brook:
			    printf("brook");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_rook,ptr2);
			    //last_call_rook(ptr2);
			    break;
			case bbishop:
			    printf("bbishop");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_bishop,ptr2);
			    //last_call_bishop(ptr2);
			    break;
			case bqueen:
			    printf("bqueen");
			    ptr2 = copy_args(args);
			    pthread_create(&(threads[thread_index]),NULL,last_call_queen,ptr2);
			    //last_call_queen(ptr2);
			    break;
		    }
		    current_index++;
		    thread_index++;
		}
		else
		{}
	    }
	    else
	    {}
	}
    }
    for(int index =0; index < thread_index; index++)
    {
	//printf("\nexit: %d index: %d thread_index: %d\n",threads[index],index, thread_index);
	pthread_join(threads[index],NULL);
    }
    return last_min_max(value_list,current_index,white_to_moveq,false);
}
