#ifndef dot_recordD
#define dot_recordD 
#include "state.h"

FILE *fp;

char current_node[10];
//int fputs( const char *s, FILE *fp );

void init_dot()
{
	fp = fopen("out.dot", "w");
	fputs("digraph mygraph {",fp);
}

void close_dot()
{
	fputs("}",fp);
	fclose(fp);
}

void board_to_string(board board_in, FILE * file_in)
{
	int piece;
	for (int index1 = 0; index1 < 8; index1++)
		{
			for (int index2 = 0; index2 < 8; index2++)
			{
				piece = board_in[index1][index2];
				fprintf(file_in,"%d,",piece);
			}
			fprintf(file_in,"\n");
		}
	fprintf(file_in,"\n");
	const char *color_string;
	for (int index1 = 0; index1 < 8; index1++)
	{
		fprintf(file_in,"|");
		for (int index2 = 0; index2 < 8; index2++)
		{
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
			if(is_white(piece))
				fprintf(file_in,"%s  ",color_string);
			else if(is_black(piece))
				fprintf(file_in,"%s  ",color_string);
			else
				fprintf(file_in,"%s  ",color_string);
		}
		fprintf(file_in,"|\n|");
		for(int index2 = 0; index2 < 8; index2++)
		{
			fprintf(file_in,"    ");
		}
		fprintf(file_in,"|\n");
	}
	fprintf(file_in,"\n");
}

int label_node(board board_in, int value_in)
{
	board_c++;
	fprintf(fp,"a%d [label=\"",board_c);
	board_to_string(board_in,fp);
	fprintf(fp,"\n value: %d\n node:a%d\"] [fontname = \"Courier\"];\n",value_in,board_c);
	return board_c;
}

void link_nodes(int node1_c,int node2_c)
{
	fprintf(fp,"a%d -> a%d;\n",node1_c,node2_c);
}

#endif
