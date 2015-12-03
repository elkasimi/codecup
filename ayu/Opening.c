#include "Common.h"

#include "AI.h"
#include "Position.h"
#include "Group.h"
#include "Util.h"

static Real get_distance_to_center(Group* g) {
	Int f;
	Real res = 0.0;
	for (f = 0; f < NXN; ++f) {
		if (Group_has_member(g, f)) {
			Int d = Util_get_distance_to_center(f);
			res += d;
		}
	}
	res /= g->count;
	return res;
}

static Real evaluate(Position* pos) {
	Real value = 0.0;
	Int i;
	for (i = 0; i < pos->white_groups_count; ++i) {
		Int idx = pos->white_groups_idx[i];
		Group* g = &pos->white_groups[idx];
		value += get_distance_to_center(g);
	}
	for (i = 0; i < pos->black_groups_count; ++i) {
		Int idx = pos->black_groups_idx[i];
		Group* g = &pos->black_groups[idx];
		value -= get_distance_to_center(g);
	}
	if (pos->player == WHITE) {
		value *= -1.0;
	}
	return value;
}

Move AI_Opening_get_best_move(Position* pos) {
	Move best_move = INVALID_MOVE;
	if (pos->moves < OPENING_MOVES) {
		MoveList moves;
		Int c = Position_get_moves(pos, moves);
		Int i;
		Real best_value = -OO;
		for (i = 0; i < c; ++i) {
			Move move = moves[i];
			Position tmp;
			Position_copy(&tmp, pos);
			Position_do_move(&tmp, move);
			Real value = -evaluate(&tmp);
			if (best_value < value) {
				best_value = value;
				best_move = move;
			}
		}
	}
	return best_move;
}
