#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "board.h"

#define NO_EN_PASSANT -1

static const int16_t piece_values[7]={0,1,3,3,5,9,200};

static inline board_mat_value_t piece_base_value(piece_type_t type) {
	return piece_values[type];
}

static inline board_mat_value_t pawn_value_adjustment(piece_color_t color, int8_t piece_row) {
	board_mat_value_t adjustment = (color == PIECE_COLOR_WHITE)? (piece_row - 4) : (3 - piece_row);
	return (adjustment > 0)? adjustment : 0;
}

/* determine adjusted piece value based on position (if it's a pawn) */
static inline board_mat_value_t  adjusted_piece_value(piece_t piece, int8_t piece_row) {
	piece_type_t type = piece_type(piece);
	piece_color_t color = piece_color(piece);
	board_mat_value_t value = piece_base_value(type);

	/* adjust pawns close to the far end of the board */
	if (type == PIECE_TYPE_PAWN)
		value += pawn_value_adjustment(color, piece_row);

	return value;
}

void board_apply_move(board_t *board, board_move_t move)
{
	bool player_is_white = !board->last_player_is_white;

	piece_t piece = board->pieces[move.start_row][move.start_col];
	piece_color_t color = piece_color(piece);
	/* adjust relative material value if a pawn is progressing far enough */
	if (piece_type(piece) == PIECE_TYPE_PAWN && pawn_value_adjustment(color, move.end_row) > 0)
	board->rel_mat_value_w_b += (player_is_white? 1 : -1);

	piece_t rip = board->pieces[move.end_row][move.end_col];
	/* did the move result in a piece being killed? */
	if (rip) {
		/* adjust relative material value if a piece was killed */
		board_mat_value_t rip_val = adjusted_piece_value(rip, move.end_row);
		board->rel_mat_value_w_b = player_is_white? (board->rel_mat_value_w_b + rip_val) : (board->rel_mat_value_w_b - rip_val);
	}

	/* convert pieces for pawn promotions */
	if (move.end_row < 0) {
		piece = (0 - move.end_row) | color;
		move.end_row = 0;
	}
	if (move.end_row > 7) {
		piece = (move.end_row - 7) | color;
		move.end_row = 7;
	}

	/* perform move */
	board->pieces[move.end_row][move.end_col] = piece;
	board->pieces[move.start_row][move.start_col] = PIECE_TYPE_NULL;

	/* switch turns */
	board->last_player_is_white = player_is_white;
}

// void Position::makeMove(Piece& p, const Move &m)
// { //OLD: returns false if it appears useless
// 	/* remember that black's end is 0 and white's end is 7 */
// // 		++analyzed_moves;

// 	if (next_turn==WHITE)
// 		next_turn=BLACK;
// 	else
// 		next_turn=WHITE;

// 	Piece& rip = getTarget(m);
// 	if (rip.alive()) {
// 		rip.kill();
// 		if (next_turn==WHITE)
// 			rel_value_b_w+=pieceval[rip.getType()];
// 		else
// 			rel_value_b_w-=pieceval[rip.getType()];
// 		if (rip.getType()==TYPE_PAWN) {
// 			if (next_turn==WHITE) { /* pawn is white; black starts at 1, white starts at 6 */
// 				/* closer to black's end (0) is worth more for black to capture */
// 				if (rip.getY()<=3) rel_value_b_w+=4-rip.getY();
// 			} else { /* pawn is black */
// 				/* closer to white's end (7) is worth more for white to capture */
// 				if (rip.getY()>=4) rel_value_b_w-=rip.getY()-3;
// 			}
// 		}
// 	}
// 	p.setDirty();
// 	for (Piece &p2: pieces) {
// 		if (!p2.alive()) continue;
// 		if (p2.checkLOF(p.getX(), p.getY())) { //piece moved out of LOF
// 			p2.setDirty();
// 		}
// 		if (p2.checkLOF(m.getX(), m.getY())) { //piece moved out of LOF
// 			p2.setDirty();
// 		}
// 	}
// 	if (m.extra) {
// 		if (m.extra&bitflags[0]) { //pawn promotion
// 			p.setType(TYPE_QUEEN);
// 			if (next_turn==WHITE) /* new black king */
// 				rel_value_b_w+=pieceval[TYPE_QUEEN];
// 			else /* new white king */
// 				rel_value_b_w-=pieceval[TYPE_QUEEN];
// 		} else if (m.extra&bitflags[1]) { //en passant
// 			Piece& rip = getTarget(m); //pieces[board[m.x][p.y]];
// 			rip.kill();
// 			if (next_turn==WHITE) /* white pawn captured */
// 				rel_value_b_w+=pieceval[rip.getType()];
// 			else /* black pawn captured */
// 				rel_value_b_w-=pieceval[rip.getType()];
// 		} else if (m.extra&bitflags[3]) { //pawn progression
// 			if (next_turn==WHITE && m.getY()>=4) /* black pawn progressed closer to 7 */
// 				rel_value_b_w+=1;
// 			else if (m.getY()<=3) /* white pawn progressed closer to 0 */
// 				rel_value_b_w-=1;
// 		}
// 	}
// 	if (m.extra&bitflags[2]) //pawn jump forward 2
// 		enpassant=p.getX(); //m.getX() works too
// 	else
// 		enpassant=-1;

// 	setTargetId(m, board[p.getX()][p.getY()]);
// 	board[p.getX()][p.getY()]=0;
// 	p.setX(m.getX());
// 	p.setY(m.getY());

// 	updatePieces();
// }

static inline void add_move(board_move_list_t *move_list, int8_t start_row, int8_t start_col, int8_t end_row, int8_t end_col)
{
	move_list->moves[move_list->length++] = (board_move_t) {.start_row = start_row, .start_col = start_col, .end_row = end_row, .end_col = end_col};
}

static inline void add_pawn_promotions(board_move_list_t *move_list, int8_t start_row, int8_t start_col, int8_t end_row, int8_t end_col)
{
	for (int i = PIECE_TYPE_KNIGHT; i <= PIECE_TYPE_QUEEN; i++) {
		if (end_row == 7) {
			/* white */
			add_move(move_list, start_row, start_col, 7 + i, end_col);
		} else {
			/* black */
			add_move(move_list, start_row, start_col, 0 - i, end_col);
		}
	}
}

static inline bool square_is_valid(int8_t row, int8_t col)
{
	return (row >= 0 && row < 8) && (col >= 0 && col < 8);
}

static inline bool square_is_blocked(const board_t *board, int8_t row, int8_t col)
{
	piece_color_t player_color = (board->last_player_is_white? PIECE_COLOR_BLACK : PIECE_COLOR_WHITE);
	piece_t target_piece = board->pieces[row][col];
	return (target_piece && piece_color(target_piece) == player_color);
	// (!target_piece || piece_color(target_piece) != player_color)
}

static inline void add_pawn_moves(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col, int en_passant)
{
	bool player_is_white = !board->last_player_is_white;
	int8_t row_dir = player_is_white? 1 : -1;
	piece_color_t player_color = player_is_white? PIECE_COLOR_WHITE : PIECE_COLOR_BLACK;

	int8_t new_row = row + row_dir;
	// forward 1
	if (square_is_valid(new_row, col) && !square_is_blocked(board, new_row, col)) {
		add_move(move_list, row, col, new_row, col);
		// forward 2
		bool in_starting_square = player_is_white? (row == 1) : (row == 6);
		add_move(move_list, row, col, new_row + row_dir, col);
	}
	// diagonal capture
	//TODO: split into function
	if (square_is_valid(new_row, col + 1)) {
		piece_t target_piece = board->pieces[new_row][col + 1];
		if (target_piece && piece_color(target_piece) != player_color)
			add_move(move_list, row, col, new_row, col + 1);
	}
	if (square_is_valid(new_row, col - 1)) {
		piece_t target_piece = board->pieces[new_row][col - 1];
		if (target_piece && piece_color(target_piece) != player_color)
			add_move(move_list, row, col, new_row, col - 1);
	}
	// en passant
	if (en_passant != NO_EN_PASSANT) {
		int8_t en_passant_row = player_is_white? 4 : 3;
		if (row != en_passant_row)
			return;

		int8_t new_col;
		if (col + 1 == en_passant)
			new_col = col + 1;
		else if (col - 1 == en_passant)
			new_col = col - 1;
		else
			return;
	}
}

static inline void add_knight_moves(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col)
{
	int8_t new_row[8];
	int8_t new_col[8];
	new_row[0]=row+2;
	new_row[1]=row+1;
	new_row[2]=row-1;
	new_row[3]=row-2;
	new_row[4]=row-2;
	new_row[5]=row-1;
	new_row[6]=row+1;
	new_row[7]=row+2;

	new_col[0]=col+1;
	new_col[1]=col+2;
	new_col[2]=col+2;
	new_col[3]=col+1;
	new_col[4]=col-1;
	new_col[5]=col-2;
	new_col[6]=col-2;
	new_col[7]=col-1;

	for (int i=0; i<8; i++) {
		if (square_is_valid(new_row[i], new_col[i]) && !square_is_blocked(board, new_row[i], new_col[i]))
			add_move(move_list, row, col, new_row[i], new_col[i]);
		// if (x2[n]>-1 && x2[n]<8 && y2[n]>-1 && y2[n]<8 && (b.piece[x2[n]][y2[n]]==0 || (b.piece[x2[n]][y2[n]]&black^c))) addmove(&m,b,x,y,x2[n],y2[n],c);
	}
}

static inline void add_moves_in_direction(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col, int8_t row_dir, int8_t col_dir)
{
					int8_t new_row = row;
					int8_t new_col = col;
					bool loop = true;
					do {
						new_row += row_dir;
						new_col += col_dir;
						if (!square_is_valid(new_row, new_col) || square_is_blocked(board, new_row, new_col))
							break;

						add_move(move_list, row, col, new_row, new_col);
					} while (loop);
}

static inline void add_bishop_moves(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col)
{
	add_moves_in_direction(board, move_list, row, col, 1, 1);
	add_moves_in_direction(board, move_list, row, col, 1, -1);
	add_moves_in_direction(board, move_list, row, col, -1, 1);
	add_moves_in_direction(board, move_list, row, col, -1, -1);
}

static inline void add_rook_moves(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col)
{
	add_moves_in_direction(board, move_list, row, col, 0, 1);
	add_moves_in_direction(board, move_list, row, col, 0, -1);
	add_moves_in_direction(board, move_list, row, col, 1, 0);
	add_moves_in_direction(board, move_list, row, col, -1, 0);
}

static inline void add_queen_moves(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col)
{
	add_bishop_moves(board, move_list, row, col);
	add_rook_moves(board, move_list, row, col);
}

static inline void add_king_moves(const board_t *board, board_move_list_t *move_list, int8_t row, int8_t col)
{
	// all squares around the king
	const int8_t row_dir[8] = {0, 0, 1, 1, 1, -1, -1, -1};
	const int8_t col_dir[8] = {1, -1, 0, 1, -1, 0, 1, -1};

	for (int i = 0; i < 8; i++) {
		int8_t new_row = row + row_dir[i];
		int8_t new_col = col + col_dir[i];
		if (square_is_valid(new_row, new_col) && !square_is_blocked(board, new_row, new_col))
			add_move(move_list, row, col, new_row, new_col);
	}
}

board_move_list_t board_get_possible_moves(const board_t *board) {
	board_move_list_t move_list = {.length = 0};
	bool player_is_white = !board->last_player_is_white;
	piece_color_t player_color = (player_is_white? PIECE_COLOR_WHITE : PIECE_COLOR_BLACK);

	/* iterate over all squares on the board */
	for (int row=0; row<8; row++) {
		for (int col=0; col<8; col++) {
			piece_t piece = (board->pieces[row][col]);
			/* skip empty squares */
			if (!piece) continue;
			piece_color_t color = piece_color(piece);
			/* skip opponent's pieces */
			if (color != player_color) continue;
			piece_type_t type = piece_type(piece);

			/* pre-compute whether/where en passant could be valid */
			int en_passant = NO_EN_PASSANT;
			board_move_t last_move = board->last_move;
			if (piece_type(board->pieces[last_move.end_row][last_move.end_col]) == PIECE_TYPE_PAWN) {
				if ((last_move.start_row == 1 && last_move.end_row == 3) ||
				    (last_move.start_row = 6 && last_move.end_row == 4))
					en_passant = last_move.end_col;
			}

			switch (type)
			{
			case PIECE_TYPE_PAWN:
				add_pawn_moves(board, &move_list, row, col, en_passant);
				break;
			case PIECE_TYPE_KNIGHT:
				add_knight_moves(board, &move_list, row, col);
				break;
			case PIECE_TYPE_BISHOP:
				add_bishop_moves(board, &move_list, row, col);
				break;
			case PIECE_TYPE_ROOK:
				add_rook_moves(board, &move_list, row, col);
				break;
			case PIECE_TYPE_QUEEN:
				add_queen_moves(board, &move_list, row, col);
				break;
			case PIECE_TYPE_KING:
				add_king_moves(board, &move_list, row, col);
				break;

			default:
				// fail!
				printf("error: invalid piece type: %d\n", type);
				assert(0);
				break;
			}
		}
	}
	return move_list;
}

// void board_init(board_t *board)
board_t board_create_init()
{
	// board->flags = 0;
	// board->last_move = {.start_row = 0, .start_col = 0, .end_row = 0, .end_col = 0};
	// board->last_player_is_white = false;
	// board->rel_mat_value_w_b = 0;

	const piece_t white_pawn = PIECE_COLOR_WHITE | PIECE_TYPE_PAWN;
	const piece_t white_knight = PIECE_COLOR_WHITE | PIECE_TYPE_KNIGHT;
	const piece_t white_bishop = PIECE_COLOR_WHITE | PIECE_TYPE_BISHOP;
	const piece_t white_rook = PIECE_COLOR_WHITE | PIECE_TYPE_ROOK;
	const piece_t white_queen = PIECE_COLOR_WHITE | PIECE_TYPE_QUEEN;
	const piece_t white_king = PIECE_COLOR_WHITE | PIECE_TYPE_KING;

	const piece_t black_pawn = PIECE_COLOR_BLACK | PIECE_TYPE_PAWN;
	const piece_t black_knight = PIECE_COLOR_BLACK | PIECE_TYPE_KNIGHT;
	const piece_t black_bishop = PIECE_COLOR_BLACK | PIECE_TYPE_BISHOP;
	const piece_t black_rook = PIECE_COLOR_BLACK | PIECE_TYPE_ROOK;
	const piece_t black_queen = PIECE_COLOR_BLACK | PIECE_TYPE_QUEEN;
	const piece_t black_king = PIECE_COLOR_BLACK | PIECE_TYPE_KING;

	assert(white_pawn != black_pawn);

	return (board_t) {
		.flags = 0,
		.last_move = {.start_row = 0, .start_col = 0, .end_row = 0, .end_col = 0},
		.last_player_is_white = false,
		.rel_mat_value_w_b = 0,
		.pieces = {
			{white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook},
			{white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn},
			{0},
			{0},
			{0},
			{0},
			{black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn},
			{black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook}
		}
	};

	// board->pieces[0][0] = white_rook;
	// board->pieces[0][1] = white_knight;
	// board->pieces[0]
}