#include "Common.h"

#include "AI.h"
#include "Position.h"
#include "Util.h"
#include "Timer.h"

#define MAX_EVAL 1048576

static Int evaluate(Position* pos) {
	Int i;
	Int dmin;
	Int sumwd = 0;
	Int sumbd = 0;
	Int maxwd = 0;
	Int maxbd = 0;
	Int wc = 0;
	Int bc = 0;
	MoveList moves;
	for (i = 0; i < pos->white_groups_count; ++i) {
		Int idx = pos->white_groups_idx[i];
		Group* g = &pos->white_groups[idx];
		Int c = Group_get_possible_moves(g, pos, moves, &dmin);
		if (dmin != OO) {
			sumwd += dmin;
			maxwd = maxwd > dmin ? maxwd : dmin;
			++wc;
		}
	}

	for (i = 0; i < pos->black_groups_count; ++i) {
		Int idx = pos->black_groups_idx[i];
		Group* g = &pos->black_groups[idx];
		Int c = Group_get_possible_moves(g, pos, moves, &dmin);
		if (dmin != OO) {
			sumbd += dmin;
			maxbd = maxbd > dmin ? maxbd : dmin;
			++bc;
		}
	}

	Int e = maxbd - maxwd;

	if (pos->player == BLACK) {
		e = -e;
	}

	return e;
}

static Int nodes = 0;

static Int DFS(Position* pos, Int depth, Int alpha, Int beta, Move* best_move_ptr) {
	MoveList moves;
	Int count = Position_get_moves(pos, moves);
	if (count == 0) {
		++nodes;
		return +OO;
	}

	if (depth == 0) {
		++nodes;
		return evaluate(pos);
	}

	Util_shuffle_moves(moves, count);

	Int i;
	Int lalpha = alpha;
	Int best_value = -OO;
	Move best_move = moves[0];
	for (i = 0; i < count; ++i) {
		Move move = moves[i];

		Position next;
		Position_copy(&next, pos);

		Int value = -DFS(&next, depth - 1, -beta, -lalpha, NULL);

		if (best_value < value) {
			best_value = value;
			best_move = move;
		}

		lalpha = lalpha > value ? lalpha : value;

		if (best_value >= beta) {
			break;
		}
	}

	if (best_move_ptr != NULL) {
		*best_move_ptr = best_move;
	}

	return best_value;
}

Move AI_DFS_get_best_move(Position* pos) {
	Move best_move;
	nodes = 0;
	Timer_start();
	Int value = DFS(pos, 4, -OO, +OO, &best_move);
	Timer_stop();
	Int dt = Timer_get_delta_time();
	Int tt = Timer_get_total_time();
	Util_fprflush(stderr, "v=%d dt=%d tt=%d n=%d\n", value, dt, tt, nodes);

	return best_move;
}
