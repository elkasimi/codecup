#include "Common.h"

#include "Position.h"
#include "Timer.h"
#include "Util.h"

static Real weights[NXN][3] = {
	{0.0, 0.0, 0.0},
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 }
};

static Real sigomid(Real z) {
	return (1.0 / (1.0 + exp(-z)));
}

static Real eval(Position* pos) {
	Real z = 0.0;
	Int f;
	for (f = 0; f < NXN; ++f) {
		Int i = (Int)pos->owner[f];
		z += weights[f][i];
	}
	Real e = sigomid(z);
	return e;
}

static Move epsilon_greedy(Position* pos, Real epsilon, Real* return_best_value) {
	Move best_move = INVALID_MOVE;
	Real best_value = -OO;
	Real r = rand();
	r /= RAND_MAX;
	if (r < epsilon) {
		best_move = Position_get_random_move(pos);
	} else {
		MoveList moves;
		Int c = Position_get_moves(pos, moves);
		Int i;
		for (i = 0; i < c; ++i) {
			Move move = moves[i];
			Int from = FROM(move);
			Int to = TO(move);
			pos->owner[from] = NONE;
			pos->owner[to] = pos->player;
			Real value = eval(pos);
			pos->owner[from] = pos->player;
			pos->owner[to] = NONE;
			if (pos->player == BLACK) {
				value *= -1.0;
			}
			if (best_value < value) {
				best_value = value;
				best_move = move;
			}
		}
	}

	if (return_best_value) {
		*return_best_value = best_value;
	}

	return best_move;
}

static void self_play(Position* pos) {
	Real v[1000];
	Int t = 0;
	v[0] = eval(pos);
	Move move;
	Real epsilon = 0.1;
	move = epsilon_greedy(pos, epsilon, NULL);
	while (move != INVALID_MOVE) {
		Position_do_move(pos, move);
		move = epsilon_greedy(pos, epsilon, NULL);
		if (move != INVALID_MOVE) {
			v[++t] = eval(pos);
		} else {
			v[++t] = pos->player == WHITE ? 1.0 : 0.0;
		}
		if (t >= 2) {
			Real delta = v[t] - v[t - 2];
			Int f;
			for (f = 0; f < NXN; ++f) {
				Int i = (Int)pos->owner[f];
				weights[f][i] += 0.1 * delta;
			}
		}
	}
}

Move AI_TDL_get_best_move(Position* pos) {
	Int s = 0;
	while (s < 20000) {
		++s;
		Position tmp;
		Position_copy(&tmp, pos);
		self_play(&tmp);
	}
	
	Int f;
	for (f = 0; f < NXN; ++f) {
		Real* w = weights[f];
		fprintf(stderr, "%f %f %f\n", w[0], w[1], w[2]);
	}
	
	Real v;
	Move move = epsilon_greedy(pos, 0.0, &v);
	Util_fprflush(stderr, "v=%f\n", v);
	return move;
}
