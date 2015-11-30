#ifndef moveD
#define moveD
#include "state.h"

void displayboard(board board_in);

boardp move(boardp board_in,int x_in, int y_in, int x_end, int y_end, bool castlingq)
{
	#ifdef memdebug
	assert(check_board(*board_in));
	#endif
	if (! castlingq)
	{
		int piece = (*board_in)[y_in][x_in];
		(*board_in)[y_end][x_end] = piece;
		(*board_in)[y_in][x_in] = blank  ;
		//displayboard(*board_in);
		//print_board(*board_in);
		#ifdef memdebug
		assert(check_board(*board_in));
		#endif
		return board_in;
	}
	else
	{
		assert(false);
		return NULL;
	}
}

bool valid_move(boardp board_in,int x_in, int y_in, int x_end, int y_end, bool castlingq)
{
	if (valid((*board_in),x_in,y_in,x_end,y_end))
	{
		move(board_in,x_in,y_in,x_end,y_end,castlingq);
		return true;
	}
	else
		return false;
}

#endif
