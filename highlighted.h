#ifndef highlightedD
#define highlightedD

enum
{
	blank,
    valid_move,
    selected,
    current,
    not_valid
}

board highlighted = {
	{blank,blank,blank,blank,blank,blank,blank,blank},//1
	{blank,blank,blank,blank,blank,blank,blank,blank},//2
	{blank,blank,blank,blank,blank,blank,blank,blank},//3
	{blank,blank,blank,blank,blank,blank,blank,blank},//4
	{blank,blank,blank,blank,blank,blank,blank,blank},//5
	{blank,blank,blank,blank,blank,blank,blank,blank},//6
	{blank,blank,blank,blank,blank,blank,blank,blank},//7
	{blank,blank,blank,blank,blank,blank,blank,blank},//8
};

char ** create_highlighted_board(board board_in,board highlighted)
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
#endif