#include "chessDisplay.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>

//y coord, top right of board square
#define ROW_1 30 //0-30
#define ROW_2 60
#define ROW_3 90
#define ROW_4 120
#define ROW_5 150
#define ROW_6 180
#define ROW_7 210
#define ROW_8 240 //210-240
//x coord
#define COL_1 30
#define COL_2 60
#define COL_3 90
#define COL_4 120
#define COL_5 150
#define COL_6 180
#define COL_7 210
#define COL_8 240 //210-240


#define HALF_SQUARE_DIM SQUARE_DIM / 2

void chessDisplay_drawBoard(){
    
}

//30x40 pixel for each square to have and 8x8 grid on a 240x320 display screen

void chessDisplay_computeRegionNumber(uint8_t *row, uint8_t *column){
    int16_t x, y;
    uint8_t z;

    display_getTouchedPoint(&x, &y, &z);
    //determine what square (row, col) is being touched
    // assign col number
    if (x < COL_1) {
        *column = COL_1;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_2) {
        *column = COL_2;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_3) {
        *column = COL_3;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_4) {
        *column = COL_4;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_5) {
        *column = COL_5;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_6) {
        *column = COL_6;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_7) {
        *column = COL_7;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    } else if (x < COL_8) {
       *column = COL_8;
        //assign row number
        if (y < ROW_1) {
            *row = ROW_1;
        } else if (y < ROW_2) {
            *row = ROW_2;
        } else if (y < ROW_3) {
            *row = ROW_3;
        } else if (y < ROW_4) {
            *row = ROW_4;
        } else if (y < ROW_5) {
            *row = ROW_5;
        } else if (y < ROW_6) {
            *row = ROW_6;
        } else if (y < ROW_7) {
            *row = ROW_7;
        } else if (y < ROW_8) {
            *row = ROW_8;
        }
    }
}


void displayPawn(uint8_t row, uint8_t column, bool erase){ 
    int16_t display_color = DISPLAY_WHITE;
    int16_t x_coord;
    int16_t y_coord;
    //if erase is true redraw the piece in black, otherwise use white
    if (erase){
        display_color = DISPLAY_BLACK;
    } 
    //determine coords of circle's center depending on row 
    if (row == FIRST_ROW) {
        x_coord = HALF_SQUARE_DIM;
    } else if (row == SECOND_ROW) {
        x_coord = ROW_2 - HALF_SQUARE_DIM;
    } else if (row == THIRD_ROW) {
        x_coord = ROW_3 - HALF_SQUARE_DIM;
    } else if (row == FOURTH_ROW) {
        x_coord = ROW_4 - HALF_SQUARE_DIM;
    } else if (row == FIFTH_ROW) {
        x_coord = ROW_5 - HALF_SQUARE_DIM;
    } else if (row == SIXTH_ROW) {
        x_coord = ROW_6 - HALF_SQUARE_DIM;
    } else if (row == SEVENTH_ROW) {
        x_coord = ROW_7 - HALF_SQUARE_DIM;
    } else if (row == EIGHTH_ROW) {
        x_coord = ROW_8 - HALF_SQUARE_DIM;
    }
    //determine coords of circle's center depending on col
    if (col == FIRST_COL) {
        y_coord = HALF_SQUARE_DIM;
    } else if (col == SECOND_COL) {
        y_coord = COL_2 - HALF_SQUARE_DIM;
    } else if (col == THIRD_COL) {
        y_coord = COL_3 - HALF_SQUARE_DIM;
    } else if (col == FOURTH_COL) {
        y_coord = COL_4 - HALF_SQUARE_DIM;
    } else if (col == FIFTH_COL) {
        y_coord = COL_5 - HALF_SQUARE_DIM;
    } else if (col == SIXTH_COL) {
        y_coord = COL_6 - HALF_SQUARE_DIM;
    } else if (col == SEVENTH_COL) {
        y_coord = COL_7 - HALF_SQUARE_DIM;
    } else if (col == EIGHTH_COL) {
        y_coord = COL_8 - HALF_SQUARE_DIM;
    }

    display_fillCircle(x_coord, y_coord, HALF_SQUARE_DIM, display_color);
}

void displayRook(uint8_t row, uint8_t column, bool erase){
    int16_t display_color = DISPLAY_WHITE;
    //if erase is true redraw the piece in black, otherwise use white
    if (erase){
        display_color = DISPLAY_BLACK;
    } 

    

  //  display_fillRect();
}

void displayKnight(uint8_t row, uint8_t column, bool erase){
    int16_t display_color = DISPLAY_WHITE;
    //if erase is true redraw the piece in black, otherwise use white
    if (erase){
        display_color = DISPLAY_BLACK;
    } 
  //  display_fillTriangle();
}

void displayBishop(uint8_t row, uint8_t column, bool erase){
    int16_t display_color = DISPLAY_WHITE;
    //if erase is true redraw the piece in black, otherwise use white
    if (erase){
        display_color = DISPLAY_BLACK;
    } 
  //  display_drawChar(); //letter B
}

void displayKing(uint8_t row, uint8_t column, bool erase){
    int16_t display_color = DISPLAY_WHITE;
    //if erase is true redraw the piece in black, otherwise use white
    if (erase){
        display_color = DISPLAY_BLACK;
    } 
   // display_drawChar();  //letter K
}


void displayQueen(uint8_t row, uint8_t column, bool erase){
    int16_t display_color = DISPLAY_WHITE;
    //if erase is true redraw the piece in black, otherwise use white
    if (erase){
        display_color = DISPLAY_BLACK;
    } 
  //  display_drawChar(); //letter Q
}   


void displayPiece(int8_t piece_type, uint8_t row, uint8_t column, bool erase){
    if (piece_type == PIECE_TYPE_PAWN) {
       displayPawn(row, column, erase);
    } else if (piece_type == PIECE_TYPE_ROOK) {
       displayRook(row, column, erase);
    } else if (piece_type == PIECE_TYPE_KNIGHT) {
       displayKnight(row, column, erase);
    } else if (piece_type == PIECE_TYPE_BISHOP) {
       displayBishop(row, column, erase);
    } else if (piece_type == PIECE_TYPE_QUEEN) {
       displayQueen(row, column, erase);
    } else if (piece_type == PIECE_TYPE_KING) {
       displayKing(row, column, erase);
    }
}


void chessDisplay_possibleMoves(){
   // display_drawCircle(DISPLAY_GREEN);
}
