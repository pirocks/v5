#ifndef CHESS_STATE_H_
#define CHESS_STATE_H_



//#define blackcolor "blue"
//#define whitecolor "red"



extern void print_board(board board_in);
extern bool on_board(int x_end,int y_end);
extern bool emptyq(board board_in, int x_in, int y_in);
extern bool is_white(int piece_in);
extern bool is_black(int piece_in);
extern bool w_pawn(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool w_rook(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool w_knight(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool w_bishop(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool w_queen(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool w_king(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool b_pawn(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool b_rook(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool b_knight(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool b_bishop(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool b_queen(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool b_king(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool white(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool black(board board_in, int x_in, int y_in, int x_end, int y_end);
extern bool valid(board board_in, int x_in, int y_in, int x_end, int y_end);


#endif /* ifndef CHESS_STATE_H_ */
