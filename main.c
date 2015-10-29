/*
 * main.c
 *
 * Copyright 2015  <pi@raspberrypi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if !, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
#include "X11/Xlib.h"
#include "SDL/SDL_thread.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
//#include "position_evaluate.c"
#include "position_evaluatev5.h"
#include <time.h>
#include "command_line.h"
bool debug_warp = 0;

SDL_Surface *screen;
SDL_Surface *boardimage;
SDL_Surface *brook_image;
SDL_Surface *bknight_image;
SDL_Surface *bbishop_image;
SDL_Surface *bqueen_image;
SDL_Surface *bking_image;
SDL_Surface *bpawn_image;
SDL_Surface *wrook_image;
SDL_Surface *wknight_image;
SDL_Surface *wbishop_image;
SDL_Surface *wqueen_image;
SDL_Surface *wking_image;
SDL_Surface *wpawn_image;
SDL_Surface *transparency;
SDL_Event event;

//board appocalypitic_malloc_thing[1000000];

bool highlight[8][8];

/*
board global_board = {
    {blank  ,blank  ,blank  ,blank  ,blank  ,brook  ,bking  ,bknight},
    {blank  ,blank  ,blank  ,bbishop,blank  ,blank  ,blank  ,bpawn  },
    {bpawn  ,bqueen ,blank  ,bpawn  ,bpawn  ,wpawn  ,bpawn  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,blank  ,wpawn  ,bknight,blank  },
    {blank  ,wpawn  ,blank  ,wqueen ,blank  ,blank  ,blank  ,blank  },
    {wpawn  ,blank  ,blank  ,blank  ,wknight,blank  ,wpawn  ,wpawn  },
    {blank  ,blank  ,blank  ,wrook  ,wrook  ,blank  ,blank  ,wking  },
    };*/

/*board global_board = {
    {bpawn  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,bknight},
    {blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  },
    {blank  ,blank  ,bking  ,blank  ,blank  ,blank  ,blank  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,wknight,wpawn  ,blank  ,blank  },
    {blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  ,blank  },
    };

*/
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

/*board global_board = {
    {blank,blank,bbishop,bqueen,bking,bbishop,bknight,brook},
    {blank,blank,blank,bpawn,bpawn,bpawn,bpawn,bpawn},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,wpawn,wpawn,wpawn,wpawn,wpawn},
    {wrook,wknight,wbishop,wqueen,wking,wbishop,wknight,wrook},
    };*/

board global_boarda = {
    {brook,bknight,bbishop,bqueen,bking,bbishop,bknight,brook},
    {bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn},
    {wrook,wknight,wbishop,wqueen,wking,wbishop,wknight,wrook},
    };

board global_boardb = {
    {brook,bknight,bbishop,bqueen,bking,bbishop,bknight,brook},
    {bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn,bpawn},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn,wpawn},
    {wrook,wknight,wbishop,wqueen,wking,wbishop,wknight,wrook},
    };

/*board global_board = {
    {blank,bknight,blank,blank,bking,blank,blank,blank},
    {blank,blank,blank,blank,bpawn,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,blank,blank,blank,blank,blank},
    {blank,blank,blank,wpawn,blank,blank,blank,blank},
    {blank,blank,blank,blank,wpawn,blank,blank,blank},
    {blank,blank,blank,blank,wking,blank,blank,blank},
    };*/

/*//board global_board = {
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //{bl,bl,bl,bl,bl,bl,bl,bl},
    //};*/

SDL_Surface *optimize (SDL_Surface *surf)
{
	SDL_Surface *opt = SDL_DisplayFormat(surf);
	if (opt)
	{
		SDL_FreeSurface(surf);
		return opt;
	}
	return surf;
}

void displayboard(board board_in);

void init()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	boardimage = optimize(IMG_Load("board.jpg"));
	brook_image = optimize(IMG_Load("pics/brook.png"));
	bknight_image = optimize(IMG_Load("pics/bknight.png"));
	bbishop_image = optimize(IMG_Load("pics/bbishop.png"));
	bqueen_image = optimize(IMG_Load("pics/bqueen.png"));
	bking_image = optimize(IMG_Load("pics/bking.png"));
	bpawn_image = optimize(IMG_Load("pics/bpawn.png"));
	wrook_image = optimize(IMG_Load("pics/wrook.png"));
	wknight_image = optimize(IMG_Load("wknight.png"));
	wbishop_image = optimize(IMG_Load("pics/wbishop.png"));
	wqueen_image = optimize(IMG_Load("pics/wqueen.png"));
	wking_image = optimize(IMG_Load("pics/wking.png"));
	wpawn_image = optimize(IMG_Load("pics/wpawn.png"));
	transparency = optimize(IMG_Load("pics/transparency.png"));
	screen = SDL_SetVideoMode( 1000, 1000, 8, SDL_SWSURFACE );
	SDL_WM_SetCaption( "Chess", NULL );
	SDL_BlitSurface( boardimage, NULL, screen, NULL );
	SDL_Flip( screen );
	displayboard(global_board);
}

void displayboard(board board_in)
{
    SDL_BlitSurface( boardimage, NULL, screen, NULL );
    SDL_Rect location;
    int current_piece = 0;
    bool transparent = false;
    for (int yindex = 0; yindex < 8; yindex++)
    {
	for (int xindex = 0; xindex < 8; xindex++)
	{
	    transparent = highlight[yindex][xindex];
	    current_piece = board_in[yindex][xindex];
	    location.x = 125*xindex;
	    location.y = 125*yindex;
	    switch (current_piece)
	    {
		case blank:
			break;
		case bpawn:
			SDL_BlitSurface(bpawn_image,NULL,screen,&location);
			break;
		case wpawn:
			SDL_BlitSurface(wpawn_image,NULL,screen,&location);
			break;
		case brook:
			SDL_BlitSurface(brook_image,NULL,screen,&location);
			break;
		case wrook:
			SDL_BlitSurface(wrook_image,NULL,screen,&location);
			break;
		case bknight:
			SDL_BlitSurface(bknight_image,NULL,screen,&location);
			break;
		case wknight:
			SDL_BlitSurface(wknight_image,NULL,screen,&location);
			break;
		case bbishop:
			SDL_BlitSurface(bbishop_image,NULL,screen,&location);
			break;
		case wbishop:
			SDL_BlitSurface(wbishop_image,NULL,screen,&location);
			break;
		case bking:
			SDL_BlitSurface(bking_image,NULL,screen,&location);
			break;
		case wking:
			SDL_BlitSurface(wking_image,NULL,screen,&location);
			break;
		case bqueen:
			SDL_BlitSurface(bqueen_image,NULL,screen,&location);
			break;
		case wqueen:
			SDL_BlitSurface(wqueen_image,NULL,screen,&location);
			break;
	    }
	    if (transparent)
	    {
		printf("highlight");
		SDL_BlitSurface(transparency,NULL,screen,&location);
	    }
	}
    }
    SDL_Flip( screen );
}

void displayboard_norefresh(board board_in)
{
    //SDL_BlitSurface( boardimage, NULL, screen, NULL );
    SDL_Rect location;
    int current_piece = 0;
    bool transparent = false;
    for (int yindex = 0; yindex < 8; yindex++)
    {
	for (int xindex = 0; xindex < 8; xindex++)
	{
	    transparent = highlight[yindex][xindex];
	    current_piece = board_in[yindex][xindex];
	    location.x = 125*xindex;
	    location.y = 125*yindex;
	    switch (current_piece)
	    {
		case blank:
			break;
		case bpawn:
			SDL_BlitSurface(bpawn_image,NULL,screen,&location);
			break;
		case wpawn:
			SDL_BlitSurface(wpawn_image,NULL,screen,&location);
			break;
		case brook:
			SDL_BlitSurface(brook_image,NULL,screen,&location);
			break;
		case wrook:
			SDL_BlitSurface(wrook_image,NULL,screen,&location);
			break;
		case bknight:
			SDL_BlitSurface(bknight_image,NULL,screen,&location);
			break;
		case wknight:
			SDL_BlitSurface(wknight_image,NULL,screen,&location);
			break;
		case bbishop:
			SDL_BlitSurface(bbishop_image,NULL,screen,&location);
			break;
		case wbishop:
			SDL_BlitSurface(wbishop_image,NULL,screen,&location);
			break;
		case bking:
			SDL_BlitSurface(bking_image,NULL,screen,&location);
			break;
		case wking:
			SDL_BlitSurface(wking_image,NULL,screen,&location);
			break;
		case bqueen:
			SDL_BlitSurface(bqueen_image,NULL,screen,&location);
			break;
		case wqueen:
			SDL_BlitSurface(wqueen_image,NULL,screen,&location);
			break;
	    }
	    if (transparent)
	    {
		printf("highlight");
		SDL_BlitSurface(transparency,NULL,screen,&location);
	    }
	}
    }
    SDL_Flip( screen );
}

void mouse(unsigned int (* position)[2])
{
	while( SDL_WaitEvent( &event ) && event.type != SDL_QUIT)
	{
		if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
		{
			(*position)[0] = event.button.x;
			(*position)[1] = event.button.y;
			return;
		}
	}
	exit(1);
}

void ask_for_move_white(int x_in,int y_in);
void ask_for_move_black(int x_in,int y_in);
void ask_for_piece_black();

void ask_for_piece_white()
{
	for(int x = 0; x < 8; x++ )
		for(int y = 0; y < 8; y++)
			highlight[y][x] = false;
	printf("Pick a white piece\n");
	unsigned int position[2];
	mouse(&position);
	printf("x %u y %u\n", (position[0])/125, position[1]/125);
	highlight[(position[1])/125][(position[0])/125] = true;
	displayboard(global_board);
	ask_for_move_white(position[0]/125,position[1]/125);
}

void ask_for_move_white(int x_in,int y_in)
{
	printf("Pick a destination\n");
	unsigned int position[2];
	mouse(&position);
	printf("x %u y %u\n", (position[0])/125, position[1]/125);
	if (white(global_board,x_in,y_in,position[0]/125,position[1]/125))
	{
		printf("valid\n");
		move(&global_board,x_in,y_in,position[0]/125,position[1]/125,false);
		for(int x = 0; x < 8; x++ )
		    for(int y = 0; y < 8; y++)
			highlight[y][x] = false;
		displayboard(global_board);
		print_board(global_board);
		printf("calculating ...\n");
		ask_for_piece_black();
	}
	else
	{
		printf("! valid\n");
		ask_for_piece_white();
	}
}

void ask_for_piece_black()
{
	if (true)
	{
		move_to_dop answer;
		debug--;
		answer = get_move(global_board,3,false,false);
		printf("\n got to here\n");
		valid_move(&global_board,(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4],false);
		print_board(global_board);
		displayboard(global_board);
		printf("eval: %d x_in: %d y_in: %d x_end: %d y_end: %d\n",(*answer)[0],(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4]);
		ask_for_piece_white();
	}
	else
	{
		printf("Pick a black piece\n");
		unsigned int position[2];
		mouse(&position);
		printf("x %u y %u\n", (position[0])/125, position[1]/125);
		ask_for_move_black(position[0]/125,position[1]/125);
	}
}

void ask_for_move_black(int x_in, int y_in)
{
	printf("Pick a destination\n");
	unsigned int position[2];
	mouse(&position);
	printf("x %u y %u\n", (position[0])/125, position[1]/125);
	if (black(global_board,x_in,y_in,position[0]/125,position[1]/125))
	{
		printf("valid\n");
		move(&global_board,x_in,y_in,position[0]/125,position[1]/125,false);
		displayboard(global_board);
		ask_for_piece_white();
	}
	else
	{
		printf("! valid\n");
		ask_for_piece_black();
	}
}

/*int main()
{
	init();
	displayboard(global_board);
	move_to_dop answer;
	int count = 0;
	while (count < 1000)
	{
		SDL_Delay(1000);
		answer = get_move(global_board,5,true);
		move(&global_board,(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4],false);
		displayboard(global_board);
		printf("eval: %f x_in: %f y_in: %f x_end: %f y_end: %f\n",(*answer)[0],(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4]);
		SDL_Delay(1000);
		answer = get_move(global_board,5,false);
		move(&global_board,(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4],false);
		displayboard(global_board);
		printf("eval: %f x_in: %f y_in: %f x_end: %f y_end: %f\n",(*answer)[0],(*answer)[1],(*answer)[2],(*answer)[3],(*answer)[4]);
		count++;
	}
	ask_for_piece_white();
	return 0;
}*/


/*int main()
{
	init();
	displayboard(global_board);
	int num = 5;
	while (true)
	{
		printf("eval: %f\n",(*get_move(global_board,5,true))[0]);
		num++;
		break;
	}
}*/

int main()
{
    init();
    //console_ask_for_piece_white(true);
    ask_for_piece_white(true);
}
