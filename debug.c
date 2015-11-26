#ifndef debugD
#define debugD
#include "state.h"

bool compare_int_lists(int list1[],int list2[],int size1, int size2)
{
    if(size1 != size2)
	    return(false);
    for(int index = 0; index < size1; index++)
	    if(list1[index] != list2[index])
		return(false);
    return(true);
}

bool compare_int_lists2d(void *list1_2d, void *list2_2d, int size1, int size2, int size1a, int size2a) //size 1 and size 2 are top level
//size 1a and 2a are second level
{
    //typedef int array[size1][size1a];
    typedef int (*arrayp)[size1][size1a];
    if(size1 != size2 || size1a != size2a)
	return false;
    int (*list1)[size1][size1a] = malloc(size1*size1a*sizeof(int));
    memcpy(list1,(arrayp)list1_2d,sizeof(int [size1][size1a]));
    int (*list2)[size1][size1a] = malloc(size1*size1a*sizeof(int));
    memcpy(list2,(arrayp)list2_2d,sizeof(int [size1][size1a]));
    for(int index = 0; index < size1; index++)
	    if(!compare_int_lists((*list1)[index],(*list2)[index],size1a,size2a))
		return false;
    return true;
}

bool same_boardq(board board1, board board2)
{
    return compare_int_lists2d(board1,board2,8,8,8,8);
}

void print_board(board board_in);

bool check_board(board board_in)
{
    int piece = 0;
    for(int y = 0; y < 8; y++)
	for(int x = 0; x < 8;x++)
	{
	    piece = board_in[y][x];
	    if(!(piece < 13 && piece > -1))
	    {
		print_board(board_in);
		return(false);
	    }
	}
    return(true);
}

void print_move(move_to_dop answer)
{
    printf("eval: %d x_in: %d y_in: %d x_end: %d y_end: %d\n",(*answer)[0],(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4]);
}


void min_max_display(int in[],int length,bool debug)
{
    if(debug)
    {
	printf("\n[");
	for(int i = 0;i < length;i++ )
	{
	    printf("%d,",in[i]);
	}
	printf("]\n");
    }
}
#endif
