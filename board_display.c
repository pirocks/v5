#ifndef board_displayD
#define board_displayD
#include "state.h"

void printcolored_board(board board_in)
{
	int piece;
	#ifdef maxdebug
	for (int index1 = 0; index1 < 8; index1++)
		{
			for (int index2 = 0; index2 < 8; index2++)
			{
				piece = board_in[index1][index2];
				printf("%d,",piece);
			}
			printf("\n");
		}
	printf("\n");
	#endif
	const char *color_string;
	const char *background;
	for (int index1 = 0; index1 < 8; index1++)
	{
		printf("|");
		for (int index2 = 0; index2 < 8; index2++)
		{
			printf("%s",RESET);
			piece = board_in[index1][index2];
			switch(piece)
			{
				case 1:
					color_string = "WK";
					break;
				case 2:
					color_string = "WQ";
					break;
				case 3:
					color_string = "WR";
					break;
				case 4:
					color_string = "WB";
					break;
				case 5:
					color_string = "WN";
					break;
				case 6:
					color_string = "WP";
					break;
				case 7:
					color_string = "BK";
					break;
				case 8:
					color_string = "BQ";
					break;
				case 9:
					color_string = "BR";
					break;
				case 10:
					color_string = "BB";
					break;
				case 11:
					color_string = "BN";
					break;
				case 12:
					color_string = "BP";
					break;
				case 0:
					color_string = "  ";
					break;
				default:
					assert(false);
					break;
			}
			if((index1 + index2) % 2 == 0)
			{
				//background = "\x1b[1;47m";
				background = "\x1b[47m";
			}
			else
			{
				//background = "\x1b[1;40m";
				background = "\x1b[40m";
			}
			if(is_white(piece))
				printf("%s%s%s  ",background,BLUE,color_string);
			else if(is_black(piece))
				printf("%s%s%s  ",background,RED,color_string);
			else
				printf("%s%s  ",background,color_string);
			printf("%s%s",background,RESET);
		}
		printf("%s|\n|",RESET);
		for(int index2 = 0; index2 < 8; index2++)
		{
			if((index1 + index2) % 2 == 0)
			{
				//background = "\x1b[1;47m";
				background = "\x1b[47m";
			}
			else
			{
				//background = "\x1b[1;40m";
				background = "\x1b[40m";
			}
			printf("%s    ",background);
		}
		printf("%s|\n",RESET);
	}
	printf("\n");
}
#endif
