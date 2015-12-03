#include "Common.h"

#include "Position.h"

static struct {
	Real value;
	Int count;
} Stats[100];

Move AI_LightWeight_get_best_move(Position* pos) {
	/*
	MoveList moves;
	Int c = Position_get_moves(pos, moves);
	if (c == 0) {
		return INVALID_MOVE;
	}
	Int i;
	for (i = 0; i < c; ++i) {
		Stats[i].count = 0;
		Stats[i].value = 0.0;
	}

	Int j = 0;
	for (i = 0; i < 128; ++i) {
		Position tmp;
		Position_copy(&tmp, pos);
		Position_do_move(&tmp, moves[j]);
		Move move;
		Int h = 0;
		for (move = Position_get_random_move(&tmp); move != INVALID_MOVE; move = Position_get_random_move(&tmp)) {
			++h;
			Position_do_move(&tmp, move);
		}

		Real s;
		if (tmp.player == pos->player) {
			s = 1.0 - 0.001 * h;
		}
		else {
			s = 0.001 * h;
		}

		Stats[j].value += s;
		Stats[j].count += 1;

		j = (j + 1) % c;
	}

	Move best_move = moves[0];
	Real best_value = Stats[0].value / Stats[0].count;

	for (i = 1; i < c; ++i) {
		Move move = moves[i];
		Real value = Stats[i].value;
		value /= Stats[i].count;

		if (best_value < value) {
			best_value = value;
			best_move = move;
		}
	}

	return best_move;
	*/
	Move move = Position_get_random_move(pos);
	return move;
}
