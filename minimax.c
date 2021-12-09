#include <stdint.h>
#include "board.h"
#include "minimax.h"
#include <limits.h>
#include <stdbool.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define SCORE_OVERFLOW_MAX INT_MAX
#define SCORE_OVERFLOW_MIN INT_MIN

#define SCORE_DEAD_THRESHOLD 100
#define MINIMAX_DEPTH 4

typedef int32_t minimax_score_t;

/* create a copy of a board */
//TODO: potential optimization: use memcpy()
static inline board_t copy_board(const board_t *board) {
	return *board;
}

static inline minimax_score_t score_board(const board_t *board) {
	return board->rel_mat_value_w_b;
}


static inline bool king_is_dead(minimax_score_t minimax_score) {
	return (minimax_score > SCORE_DEAD_THRESHOLD) || (minimax_score * (-1) > SCORE_DEAD_THRESHOLD);
}

static minimax_score_t alphabeta(const board_t *board, int depth, minimax_score_t alpha, minimax_score_t beta)
{
	/* determine whether we have reached the death of the king (illegal, but useful) */
	minimax_score_t current_score = score_board(board);

	if (depth == 0 || king_is_dead(current_score))
		return current_score;

	const bool maximizing = board->last_player_is_white;
	--depth;

	//TODO: convert to pointer function?
	board_move_list_t moves = board_get_possible_moves(board);

	// find best move
	int best_move_index = -1;
	minimax_score_t value = maximizing? SCORE_OVERFLOW_MIN : SCORE_OVERFLOW_MAX;

	for (int i = 0; i < moves.length; i++) {
			//TODO: convert to pointer function?
			board_t new_board = copy_board(board);
			board_apply_move(&new_board, moves.moves[i]);
			/* recurse */
			minimax_score_t new_value = alphabeta(&new_board, depth, alpha, beta);

			/* accept/reject new_value */
			if (maximizing) {
				value = MAX(value, new_value);
				alpha = MAX(alpha, value);
			} else {
				value = MIN(value, new_value);
				beta = MIN(beta, value);
			}

			/* are we done yet? */
			if (beta <= alpha)
				break;
	}
	return value;

	// if (!kingAlive())
	// 	return CHECKMATE;


	// int begin, end;
	// if (next_turn==WHITE) {
	// 	begin=17;
	// 	end=32;
	// } else {
	// 	begin=1;
	// 	end=16;
	// }

	// /* next_turn is the turn that we are currently analyzing */
	// const bool maximizing = (next_turn == BLACK);

	// /* minimax with alpha-beta pruning */
	// minimax_score_t value = (maximizing? LLONG_MIN : LLONG_MAX);

	// /* iterate through pieces */
	// /* heuristic: iterate backward because non-pawn pieces are generally more important */
	// for (int i = end; i >= begin; --i) {
	// 	const Piece& p=pieces[i];
	// 	if (!p.alive()) continue;

	// 	/* iterate through possible moves */
	// 	for (int j=p.movestart; j<p.moveend; ++j) {
	// 		/* variable for minimax value of selected move */
	// 		minimax_score_t newpos_value;

	// 		/* generate position corresponding to potential move */
	// 		if (depth > 0) {
	// 			Position newpos(*this);
	// 			newpos.makeMove(newpos.pieces[i],newpos.moves[j]);

	// 			/* lookup result in hash table */
	// 			BoardState state = newpos.toBoardState(depth);
	// 			uint32_t hash = ttable.genHash(state);
	// 			newpos_value = ttable.lookup(hash, state);
	// 			if (newpos_value == TTable::LOOKUP_FAILED) {
	// 				/* hash lookup failed, so perform look-ahead */
	// 				newpos_value = newpos.minimax_alphabeta(depth, alpha, beta);
	// 				ttable.store(hash, BoardEntry(state, newpos_value));
	// 			}
	// 		} else {
	// 			newpos_value = pseudoMakeMove(pieces[i],moves[j]);
	// 		}

	// 		/* accept/reject newpos_value */
	// 		if (maximizing) {
	// 			value = MAX(value, newpos_value);
	// 			alpha = MAX(alpha, value);
	// 		} else {
	// 			value = MIN(value, newpos_value);
	// 			beta = MIN(beta, value);
	// 		}

	// 		/* are we done yet? */
	// 		if (beta <= alpha)
	// 			break;
	// 	}
	// }

	// return value;
}

// check for check/checkmate/stalemate
minimax_state_t minimax_get_board_state(const board_t *board)
{
	// checkmate/stalemate (ambiguous)
	minimax_score_t score_forward_2 = (alphabeta(board, 1, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX));
	bool game_over = king_is_dead(score_forward_2);

	// check
	board_t null_move_board = copy_board(board);
	null_move_board.last_player_is_white = ! board->last_player_is_white;
	minimax_score_t score_forward_null = alphabeta(board, 1, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX);
	bool in_check = king_is_dead(score_forward_null);

	if (game_over) {
		return in_check? MINIMAX_CHECKMATE : MINIMAX_DRAW;
	}
	if (in_check)
		return MINIMAX_CHECK;

	return MINIMAX_NORMAL;
}

static inline minimax_score_t rate_move(const board_t *board, board_move_t move)
{
	board_t new_board = copy_board(board);
	board_apply_move(&new_board, move);
	return alphabeta(&new_board, MINIMAX_DEPTH, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX);
}

board_move_t minimax_get_best_move(const board_t *board)
{

	minimax_score_t current_score = score_board(board);
	const bool maximizing = board->last_player_is_white;

	//TODO: convert to pointer function?
	board_move_list_t move_list = board_get_possible_moves(board);

	// find best move
	int best_move_index = -1;
	minimax_score_t best_move_value = maximizing? SCORE_OVERFLOW_MIN : SCORE_OVERFLOW_MAX;

	for (int i = 0; i < move_list.length; i++) {
		minimax_score_t new_value = rate_move(board, move_list.moves[i]);
		if (maximizing) {
			if (new_value > best_move_value) {
				best_move_index = i;
				new_value = best_move_value;
			}
		} else {
			if (new_value < best_move_value) {
				best_move_index = i;
				new_value = best_move_value;
			}
		}
	}
	return move_list.moves[best_move_index];
}

void minimax_remove_illegal_moves(const board_t *board, board_move_list_t *move_list)
{
	int i = 0;
	while (i < move_list->length) {
		board_t new_board = copy_board(board);
		board_move_t move = move_list->moves[i];
		board_apply_move(&new_board, move);

		/* prevent moving into check */
		minimax_score_t score_forward_1 = (alphabeta(&new_board, 1, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX));
		bool in_check = king_is_dead(score_forward_1);
		if (in_check) {
			int last_i = move_list->length - 1;
			/* decrease size to remove illegal move */
			move_list->length--;
			if (i < last_i) {
				/* replace move with (possibly) valid move from end */
				move_list->moves[i] = move_list->moves[last_i];
			} else {
				/* no moves left to evaluate */
				return;
			}
		} else {
			/* move is legal; evaluate next move */
			i++;
		}
	}
}

inline tinybool minimax_is_game_over(const board_t *board) {
  minimax_state_t state = minimax_get_board_state(board);
  return state == MINIMAX_CHECKMATE || state == MINIMAX_DRAW;
}
