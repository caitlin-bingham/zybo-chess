#include <stdbool.h>
#include <stdint.h>

#define PIECE_TYPE_PAWN 0x00
#define PIECE_TYPE_ROOK 0x01
#define PIECE_TYPE_KNIGHT 0x02
#define PIECE_TYPE_BISHOP 0x03
#define PIECE_TYPE_QUEEN 0x04
#define PIECE_TYPE_KING 0x05

#define FIRST_ROW 1
#define SECOND_ROW 2
#define THIRD_ROW 3
#define FOURTH_ROW 4
#define FIFTH_ROW 5
#define SIXTH_ROW 6
#define SEVENTH_ROW 7
#define EIGHTH_ROW 8

#define FIRST_COL 1
#define SECOND_COL 2
#define THIRD_COL 3
#define FOURTH_COL 4
#define FIFTH_COL 5
#define SIXTH_COL 6
#define SEVENTH_COL 7
#define EIGHTH_COL 8

#define SQUARE_DIM 30

//reads in touch and computes what square was touched (its row and column)
void chessDisplay_touchScreencomputeBoardRowColumn(uint8_t *row, uint8_t *column);

//draws piece corrseponding w/ offset when erase is false
//erases piece if erase is true
void chessDisplay_displayPiece(int8_t piece_type, uint8_t row, uint8_t column, bool erase);

//draw checkerboard 
void chessDisplay_drawBoard();
