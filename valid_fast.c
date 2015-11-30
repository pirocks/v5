#include "state.h"

#pragma poison valid
#pragma poison print_board
#pragma poison on_board
#pragma poison emptyq
#pragma poison is_white
#pragma poison is_black
#pragma poison w_pawn
#pragma poison rook
#pragma poison knight
#pragma poison bishop
#pragma poison queen
#pragma poison w_king
#pragma poison b_pawn
#pragma poison b_king
#pragma poison white
#pragma poison black


bool on_board_fast(int x_end,int y_end) 
{
	return (x_end < 8 && y_end < 8 && x_end >= 0 && y_end >= 0);
}

bool emptyq_fast(board board_in, int x_in, int y_in) 
{
	return board_in[y_in][x_in] == blank  ;
}

bool is_white_fast(int piece_in)
{
	return ((piece_in != 0) && (piece_in < 7));
}

bool is_black_fast(int piece_in)
{
	return (piece_in > 6);
}

bool w_pawn_fast(board board_in, int x_in, int y_in, int x_end, int y_end) 
{
	assert(board_in[y_in][x_in] == wpawn);
	if (on_board(x_end,y_end))
	{
		if (x_in == x_end)
		{
			if (y_in - y_end == 1)
				return emptyq(board_in,x_end,y_end);
			else if (y_in - y_end == 2)
			{
				if (y_in == 6)
					return emptyq(board_in,x_end,y_end) && emptyq(board_in,x_end,y_end + 1);
			}	
			else
				return false;
		}
		else if (abs(x_in - x_end) == 1)
		{
			if (y_in - y_end == 1)
				if (is_black(board_in[y_end][x_end]))
					return true;
				else
					return false;
			else
				return false;
		}
		else
			return false;
	}
	return false;
}

bool rook_fast(board board_in, int x_in, int y_in, int x_end, int y_end, bool whiteq) 
{
	if (on_board(x_end,y_end))
	{
		if (x_in != x_end && y_in == y_end)
		{
			int current_x = x_in;
			if ((x_end - x_in) == 0)
				return false;
			int change = (x_end - x_in)/abs(x_end - x_in);
			current_x += change;
			while (x_end != current_x)
			{
				if(emptyq(board_in, current_x,y_in))
					{}
				else{
					//printf("rook piece in the way currentx: %d\n",current_x);
					return false;}
				current_x += change;
			}
			if(whiteq)
			{
				if (emptyq(board_in, x_end,y_in) || is_black(board_in[y_end][x_end]))
					return true;
				else{
					//printf("rook piece on the end currentx: %d\n",current_x);
					return false;}
			}
			else
			{
				if (emptyq(board_in, x_end,y_in) || is_white(board_in[y_end][x_end]))
					return true;
				else{
					//printf("rook piece on the end currentx: %d\n",current_x);
					return false;}
			}
		}
		else if (y_in != y_end && x_in == x_end)
		{
			int current_y = y_in;
			if ((y_end - y_in) == 0)
				return false;
			int change = (y_end - y_in)/abs(y_end - y_in);
			current_y += change;
			while (y_end != current_y)
			{
				if(emptyq(board_in, x_in,current_y))
					{}
				else{
					//printf("rook piece in the way currenty: %d\n",current_y);
					return false;}
				current_y += change;
			}
			if(whiteq)
			{
				if (emptyq(board_in, x_in,y_end) || is_black(board_in[y_end][x_end]))
					return true;
				else{
					//printf("rook piece on the end currentx: %d\n",current_y);
					return false;}
			}
			else
			{
				if (emptyq(board_in, x_in,y_end) || is_white(board_in[y_end][x_end]))
					return true;
				else{
					//printf("rook piece on the end currentx: %d\n",current_y);
					return false;}
			}
		}
	}
	//printf("other");
	return false;
}

bool knight_fast(board board_in, int x_in, int y_in, int x_end, int y_end,bool whiteq) 
{
	if (whiteq)
	{
		if (on_board(x_end,y_end))
		{
			if (abs(y_end - y_in) == 2 && abs(x_end - x_in) == 1 && ((is_black(board_in[y_end][x_end]) || board_in[y_end][x_end] == blank  )))
				return true;
			else if (abs(y_end - y_in) == 1 && abs(x_end - x_in) == 2 && ((is_black(board_in[y_end][x_end]) || board_in[y_end][x_end] == blank  )))
				return true;
		}
	}
	else
	{
		if (on_board(x_end,y_end))
		{
			if (abs(y_end - y_in) == 2 && abs(x_end - x_in) == 1 && ((is_white(board_in[y_end][x_end]) || board_in[y_end][x_end] == blank  )))
				return true;
			else if (abs(y_end - y_in) == 1 && abs(x_end - x_in) == 2 && ((is_white(board_in[y_end][x_end]) || board_in[y_end][x_end] == blank  )))
				return true;
		}
	}
	return false;
}

bool bishop_fast(board board_in, int x_in, int y_in, int x_end, int y_end,bool whiteq) 
{
	if (on_board(x_end,y_end))
	{
		int x_distance = x_end - x_in;
		int y_distance = y_end - y_in;
		if (x_distance == 0 || y_distance == 0)
			return false;
		if (abs(x_distance) == abs(y_distance))
		{
			int current_x = x_in;
			int current_y = y_in;
			int x_change = x_distance / abs(x_distance);
			int y_change = y_distance / abs(y_distance);
			current_x += x_change;
			current_y += y_change;
			while (x_end != current_x)
			{
				if (emptyq(board_in,current_x,current_y))
					{}
				else{
					return false;}
				current_x += x_change;
				current_y += y_change;
			}
			if (whiteq)
			{
				if (emptyq(board_in, x_end,y_end) || is_black(board_in[y_end][x_end]))
					return true;
				else
					return false;
			}
			else
			{
				if (emptyq(board_in, x_end,y_end) || is_white(board_in[y_end][x_end]))
					return true;
				else
					return false;
			}
		}
	}
	return false;
}

bool queen_fast(board board_in, int x_in, int y_in, int x_end, int y_end,bool whiteq) 
{
	return (rook(board_in, x_in, y_in, x_end, y_end,whiteq) || bishop(board_in, x_in, y_in, x_end, y_end,whiteq) );
}

bool w_king_fast(board board_in, int x_in, int y_in, int x_end, int y_end) //castling ! implemented
{
	if (on_board(x_end,y_end))// was causing segfualt when in a &&
	{
		if(is_black(board_in[y_end][x_end]) || board_in[y_end][x_end] == blank)
			if(abs(y_in - y_end) == 1 || abs(x_in -x_end) == 1)
				return true;
	}
	return false;
}

bool b_pawn_fast(board board_in, int x_in, int y_in, int x_end, int y_end) 
{
	assert(board_in[y_in][x_in] == bpawn);
	if (on_board(x_end,y_end))
	{
		if (x_in == x_end)
		{
			if (y_end - y_in == 1)
				return emptyq(board_in,x_end,y_end);
			else if (y_end - y_in == 2)
			{
				if (y_in == 1)
					return emptyq(board_in,x_end,y_end) && emptyq(board_in,x_end,y_end - 1);
			}	
			else
				return false;
		}
		else if (abs(x_in - x_end) == 1)
		{
			if (y_end - y_in == 1)
				if (is_white(board_in[y_end][x_end]))
					return true;
				else
					return false;
			else
				return false;
		}
		else
			return false;
	}
	return false;
}

bool b_king_fast(board board_in, int x_in, int y_in, int x_end, int y_end) 
{
	//printf("\n%d\n",board_in[y_in][x_in]);
	assert(board_in[y_in][x_in] == bking);
	if (on_board(x_end,y_end))
		if(is_white(board_in[y_end][x_end]) || board_in[y_end][x_end] == blank)
			if(abs(y_in - y_end) == 1 || abs(x_in -x_end) == 1)
				return true;
			else
				{/*printf("distance");*/}
		else
			{/*printf("is white is blank endpiece:%d\n",board_in[y_end][x_end]);*/}
	else
		{/*printf("on board");*/}
	return false;
}

bool white_fast(board board_in, int x_in, int y_in, int x_end, int y_end,int piece)
{
	switch(piece)
	{
		case wpawn:
			return w_pawn_fast(board_in, x_in, y_in, x_end, y_end);
		case wknight:
			return knight_fast(board_in, x_in, y_in, x_end, y_end,true);
		case wrook:
			return rook_fast_optimized(board_in, x_in, y_in, x_end, y_end,true);
		case wbishop:
			return bishop_fast_optimized(board_in, x_in, y_in, x_end, y_end,true);
		case wqueen:
			return queen_fast_optimized(board_in, x_in, y_in, x_end, y_end,true);
		case wking:
			return w_king_fast(board_in, x_in, y_in, x_end, y_end);
		default:
			return false;
	}
}

bool black_fast(board board_in, int x_in, int y_in, int x_end, int y_end,int piece)
{
	switch(piece)
	{
		case bpawn:
			return b_pawn_fast(board_in, x_in, y_in, x_end, y_end);
		case bknight:
			return knight_fast(board_in, x_in, y_in, x_end, y_end,false);
		case brook:
			return rook_fast_optimized(board_in, x_in, y_in, x_end, y_end,false);
		case bbishop:
			return bishop_fast_optimized(board_in, x_in, y_in, x_end, y_end,false);
		case bqueen:
			return queen_fast_optimized(board_in, x_in, y_in, x_end, y_end,false);
		case bking:
			return b_king_fast(board_in, x_in, y_in, x_end, y_end);
		default:
			return(false);
	}
}

bool valid_fast(board board_in, int x_in, int y_in, int x_end, int y_end)
{
	int piece = board_in[y_in][x_in];
	if(is_white(piece))
		return(white_fast(board_in, x_in, y_in, x_end, y_end,piece));
	else
		return(black_fast(board_in, x_in, y_in, x_end, y_end,piece));
}





