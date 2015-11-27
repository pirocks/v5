#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define special 20000000
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
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

extern int board_c;

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
//typedef int a_move[2];
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
//typedef int moves_list[][2];
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
boardp copy(board board_in);
void   call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void  call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void   call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void   call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);

int slow_max(evals_in list_in,int length, int debug);
int slow_min(evals_in list_in,int length, int debug);
int min_max(evals_in list_in,int length, bool white_to_moveq, int debug,int depth);
void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);

int white_count(board board_in, int debug);
int black_count(board board_in, int debug);
void last_call(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq, moves_list moves, int moves_list_length, int debug);
void last_call_black(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_queen(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);


void last_call_black(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
void last_call_white(moves_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_knight(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_bishop(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_queen(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_king(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_rook(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void last_call_pawn(moves_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,   int debug);


void call_pawn(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_knight(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_bishop(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_queen(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_king(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
void call_rook(evals_inp list_in,int *list_in_index,board board_in,int x_in, int y_in,int depth,bool white_to_moveq,int debug);
int position_evaluate(board board_in, int depth, bool white_to_moveq, int debug);
int slow_max(evals_in list_in,int length, int debug);
int slow_min(evals_in list_in,int length, int debug);
int min_max(evals_in list_in,int length, bool white_to_moveq, int debug,int depth);
void call_white(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
void call_black(evals_inp list_in,int *list_in_index,board board_in, int depth, bool white_to_moveq, int debug);
move_to_dop last_min_max(move_to_dop list_in[],int length, bool white_to_moveq, int debug,int depth);
int move_list_generate(board board_in, int x_in, int y_in,a_move (*final_moves)[], moves_list moves,int length,int debug);

bool is_white(int piece_in);
bool is_black(int piece_in);

void console_ask_for_piece_white(bool ai);
void console_ask_for_piece_black(bool ai);
void console_ask_for_move_white(bool ai, int x_in, int y_in);
void console_ask_for_move_black(bool ai, int x_in, int y_in);

bool valid(board board_in, int x_in, int y_in, int x_end, int y_end);
bool black(board board_in, int x_in, int y_in, int x_end, int y_end);
bool white(board board_in, int x_in, int y_in, int x_end, int y_end);

bool valid_move(boardp board_in,int x_in, int y_in, int x_end, int y_end, bool castlingq);
boardp move(boardp board_in,int x_in, int y_in, int x_end, int y_end, bool castlingq);


move_to_dop get_move(board board_in, int depth,bool white_to_moveq, int debug);

void print_move(move_to_dop answer);
void min_max_display(int in[],int length,int debug);

void print_board(board board_in);

void printcolored_board(board board_in);

int label_node(board board_in, int value_in);
void link_nodes(int,int);
void close_dot();
void init_dot();


extern board global_board;
