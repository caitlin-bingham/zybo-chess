#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

/* theoretical maximum number of possible moves in any board position */
#define BOARD_MAX_MOVES 220

/* piece type; fits into 3 lowest bits */
enum {
	PIECE_TYPE_NULL,
	PIECE_TYPE_PAWN,
	PIECE_TYPE_KNIGHT,
	PIECE_TYPE_BISHOP,
	PIECE_TYPE_ROOK,
	PIECE_TYPE_QUEEN,
	PIECE_TYPE_KING
};

/* piece color; fits into 4th lowest bit */
enum {
	PIECE_COLOR_WHITE = 0,
	PIECE_COLOR_BLACK = 8
};

#define PIECE_TYPE_MASK 0x07
#define PIECE_COLOR_MASK 0x08

typedef uint8_t piece_type_t;
typedef uint8_t piece_color_t;
typedef int16_t board_mat_value_t;
typedef uint8_t piece_t;
typedef uint8_t tinybool;
/* chess move; note that pawn promotion piece choices are indicated by moving the pawn past the edge of the board */
typedef struct
{
	int8_t start_row;
	int8_t start_col;
	int8_t end_row;
	int8_t end_col;
} board_move_t;

typedef struct {
	board_move_t moves[BOARD_MAX_MOVES];
	int length;
} board_move_list_t;

typedef struct {
	piece_t pieces[8][8];
	board_move_t last_move; //TODO: change?
	board_mat_value_t rel_mat_value_w_b;
	tinybool last_player_is_white;
	uint8_t flags;
} board_t;

static inline piece_type_t piece_type(piece_t piece) {
	return piece & PIECE_TYPE_MASK;
}

static inline piece_color_t piece_color(piece_t piece) {
	return piece & PIECE_COLOR_MASK;
}

/* call this to get the actual coordinates from the move, discarding pawn promotion information */
static inline board_move_t board_simplify_move(board_move_t move) {
	if (move.end_row < 0) move.end_row = 0;
	if (move.end_row > 7) move.end_row = 7;
	return move;
}

board_t board_create_init();

/* apply a move to a board */
void board_apply_move(board_t *board, board_move_t move);

/* get all possible moves, potentially including some illegal moves */
// board_move_list_t board_get_possible_moves(const board_t *board);
void board_get_possible_moves(const board_t *board, board_move_list_t *move_list);

#endif
