#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"

typedef enum {
    MINIMAX_UNDECIDED,
    MINIMAX_CHECKMATE_WHITE,
    MINIMAX_CHECKMATE_BLACK,
    MINIMAX_DRAW
} minimax_state_t;

board_t minimax_makemove(board_t *board);
minimax_state_t minimax_get_board_state(const board_t *board);
void minimax_remove_illegal_moves(const board_t *board, board_move_list_t *move_list);

#endif