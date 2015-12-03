#include "Common.h"

#include "AI.h"
#include "Position.h"
#include "Timer.h"
#include "Util.h"

static Int EVAL(Position* pos) {
	Int e = 0;
	Int i;
	for (i = 0; i < pos->white_groups_count; ++i) {
		Int idx = pos->white_groups_idx[i];
		Group* g = &pos->white_groups[idx];
		Int dmin = Group_get_dmin(g, pos);
		if (dmin != OO) {
			e -= dmin * dmin - g->count * g->count;
		}
	}

	for (i = 0; i < pos->black_groups_count; ++i) {
		Int idx = pos->black_groups_idx[i];
		Group* g = &pos->black_groups[idx];
		Int dmin = Group_get_dmin(g, pos);
		if (dmin != OO) {
			e += dmin * dmin - g->count * g->count;
		}
	}

	if (pos->player == BLACK) {
		e *= -1;
	}

	return e;
}

static Int DFS(Position* pos, Int depth, Int alpha, Int beta, Move* best_move_ptr) {
	MoveList moves;
	Int c = Position_get_moves(pos, moves);
	if (c == 0) {
		return +OO;
	}

	if (depth == 0) {
		return EVAL(pos);
	}

	//shuffle moves;
	Int count = c;
	while (count > 0) {
		Int r = rand() % count;
		Move t = moves[r];
		moves[r] = moves[count - 1];
		moves[count - 1] = t;
		--count;
	}

	Int best = -OO - 1;
	Move best_move = INVALID_MOVE;
	Int i;
	Int lalpha = alpha;
	for (i = 0; i < c; ++i) {
		Move move = moves[i];
		Position next;
		Position_copy(&next, pos);
		Position_do_move(&next, move);
		Int value = -DFS(&next, depth - 1, -beta, -lalpha, NULL);
		if (best < value) {
			best = value;
			best_move = move;
		}

		lalpha = lalpha > value ? lalpha : value;

		if (best >= beta) {
			break;
		}
	}

	if (best_move_ptr != NULL) {
		*best_move_ptr = best_move;
	}

	return best;
}

Move AI_Simple_get_best_move(Position* pos) {
	Move best_move;
	Timer_start();
	Int best_value = DFS(pos, 4, -OO, +OO, &best_move);
	Timer_stop();
	Int dt = Timer_get_delta_time();
	Int tt = Timer_get_total_time();
	Util_fprflush(stderr, "dt=%d tt=%d v=%d\n", dt, tt, best_value);
	return best_move;
}
