#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define special 20000000
typedef int a_move[2];
typedef int board[8][8];
typedef int (*boardp)[8][8];
extern a_move white_moves[4];
extern a_move black_moves[4];
extern a_move white_moves_final[4];
extern a_move black_moves_final[4];
extern a_move knight_moves[8];
extern a_move king_moves[8];

extern a_move white_moves[4];
extern a_move black_moves[4];
extern a_move white_moves_final[4];
extern a_move black_moves_final[4];
extern a_move knight_moves[8];
extern a_move king_moves[8];

extern a_move white_moves_pawn[4];
extern a_move black_moves_pawn[4];

enum
{
  blank  ,
  wking,
  wqueen,
  wrook,
  wbishop,
  wknight,
  wpawn,
  bking,
  bqueen,
  brook,
  bbishop,
  bknight,
  bpawn
};

#define  bl 0
#define  wk 1
#define  wq 2
#define  wr 3
#define  wb 4
#define  wn 5
#define  wp 6
#define  bk 7
#define  bq 8
#define  br 9
#define  bb 10
#define  bn 11
#define  bp 12

typedef int move_to_do[5];
typedef int (*move_to_dop)[5];
typedef int moves_list[][2];
typedef int a_move[2];
typedef int evals_in[
8*4 + // pawns
2*(8+8-1) + //rooks
2*(8+8) + //bishops not sure this is correct
2*(4*2) + //knights
1*(8) + //king
1*(8+8+8+8)//queen
];
typedef int (*evals_inp)[
8*4 + // pawns
2*(8+8-1) + //rooks
2*(8+8) + //bishops not sure this is correct
2*(4*2) + //knights
1*(8) + //king
1*(8+8+8+8)//queen
];
typedef int moves_list[][2];
typedef int a_move[2];
typedef move_to_dop moves_in[
    8*4 + // pawns
    2*(8+8-1) + //rooks
    2*(8+8) + //bishops not sure this is correct
    2*(4*2) + //knights
    1*(8) + //king
    1*(8+8+8+8)//queen
];
typedef moves_in *moves_inp;


void displayboard_norefresh(board board_in);

boardp move(boardp board_in,int x_in, int y_in, int x_end, int y_end, bool castlingq);

void   call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void  call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void   call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void   call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);

int slow_max(evals_in list_in,int length, bool debug);
int slow_min(evals_in list_in,int length, bool debug);
int min_max(evals_in list_in,int length, bool white_to_moveq, bool debug,int depth);
void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);


void last_call_black(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_queen(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);


void last_call_black(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_queen(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);



void call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);
void call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,bool debug);

int slow_max(evals_in list_in,int length, bool debug);
int slow_min(evals_in list_in,int length, bool debug);
int min_max(evals_in list_in,int length, bool white_to_moveq, bool debug,int depth);
void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);
void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, bool debug);


bool is_white(int piece_in);
bool is_black(int piece_in);
