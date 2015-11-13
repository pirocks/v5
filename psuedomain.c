#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "position_evaluatev5.h"
//#include "move.c"
//#include "valid.h"
//#include "board_display.h"
//#include "debug.h"
#include "command_line.h"

board global_board = {
    {brook,bknight,bbishop,bqueen,bking,bbishop,bknight,brook},
    {bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn},
    {wrook,wknight,wbishop,wqueen,wking,wbishop,wknight,wrook},
    };


int main()
{
	printcolored_board(global_board);
	console_ask_for_piece_white(true);
}
