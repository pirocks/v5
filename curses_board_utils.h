#ifndef curses_board_displayD
#define curses_board_displayD
#include "state.h"
#include <stdarg.h>

// char * string_append(char * base,char * to_append)
// {
// 	char * out = strcat(base,to_append);
// 	return out;
// }

void append_with_format_string(char * current_row,char* format,...)
{
	va_list argptr;
	va_start(argptr,format);
	// printf("testng format:");
	// vprintf(format,argptr);
	vsprintf(current_row + strlen(current_row)*sizeof(char),format,argptr);
	va_end(argptr);
}

char ** create_colored_board(board board_in)
{
	char ** out  = malloc(8*sizeof(char *));
	char * current_row;
	int out_i = 0;
	int piece;
	#ifdef maxdebug
	for (int index1 = 0; index1 < 8; index1++)
		{
			current_row = malloc(100*sizeof(char));
			for (int index2 = 0; index2 < 8; index2++)
			{
				piece = board_in[index1][index2];
				append_with_format_string(current_row,"%d,",piece);
			}
			out[out_i] = current_row;
			out_i++;
		}
	#endif
	#ifndef maxdebug
	const char *color_string;
	const char *background;
	for (int index1 = 0; index1 < 8; index1++)
	{
		current_row = malloc(500*sizeof(char));
		append_with_format_string(current_row,"|");
		for (int index2 = 0; index2 < 8; index2++)
		{
			append_with_format_string(current_row,"%s",RESET);
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
				background = "\x1b[47m";
			else
				background = "\x1b[40m";
			if(is_white(piece))
				append_with_format_string(current_row,"%s%s%s  ",background,BLUE,color_string);
			else if(is_black(piece))
				append_with_format_string(current_row,"%s%s%s  ",background,RED,color_string);
			else
				append_with_format_string(current_row,"%s%s  ",background,color_string);
			append_with_format_string(current_row,"%s%s",background,RESET);
		}
		append_with_format_string(current_row,"%s|",RESET);
		append_with_format_string(current_row,"\n");
		append_with_format_string(current_row,"|");
		for(int index2 = 0; index2 < 8; index2++)
		{
			if((index1 + index2) % 2 == 0)
				background = "\x1b[47m";
			else
				background = "\x1b[40m";
			append_with_format_string(current_row,"%s    ",background);
		}
		append_with_format_string(current_row,"%s|",RESET);
		out[out_i] = current_row;
		out_i++;
	}
	#endif
	return out;
}

#ifdef testing_files

	void print_board_test(board board_in)
	{
		char ** to_print = create_colored_board(board_in);
		for(int i = 0;i < 8;i++)
		{
			printf("%s\n",to_print[i]);
			free(to_print[i]);
		}
		free(to_print);
	}
	void append_format_test(int int1, float float1, int  int2)
	{
		printf("testing append:\n");
		char * base = malloc(1000*sizeof(char));
		memcpy(base,"this is the base",sizeof(char)*strlen("this is the base"));
		printf("base:%s\n",base);
		append_with_format_string(base,"	(int: %d float: %f int: %d )\n",int1,float1,int2);
		printf("result:%s\n",base);
	}
	#include "board_display.c"
	int main()
	{
		append_format_test(1,0.677,34);
		board to_test = {
	    {brook,bknight,bbishop,bqueen,bking,bbishop,bknight,brook},
	    {bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn},
	    {blank,blank,blank,blank,blank,blank,blank,blank},
	    {blank,blank,blank,blank,blank,blank,blank,blank},
	    {blank,blank,blank,blank,blank,blank,blank,blank},
	    {blank,blank,blank,blank,blank,blank,blank,blank},
	    {wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn},
	    {wrook,wknight,wbishop,wqueen,wking,wbishop,wknight,wrook},
	    };
	    printf("actual");
	    printcolored_board(to_test);
	    printf("testing..");
	    print_board_test(to_test);

	}
#endif

#endif


