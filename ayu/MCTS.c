#include "Common.h"

#include "AI.h"
#include "Tree.h"
#include "Position.h"
#include "Timer.h"
#include "Util.h"
#include "HashSet.h"

static Int ratio = 4000;

static Real EPSILON = 0.001;

static Real P = 0.005;

#if USE_LAST_GOOD_REPLY

#define MAX_MOVE_VALUE 16000

static Move last_good_reply[MAX_MOVE_VALUE][2];

static void init_last_good_replies() {
	Int i;
	for (i = 0; i < MAX_MOVE_VALUE; ++i) {
		last_good_reply[i][0] = INVALID_MOVE;
		last_good_reply[i][1] = INVALID_MOVE;
	}
}

//update last good replies using last iterations results
static void update_last_good_replies(MoveList moves, Int count, Player player, Player winner) {
	Int i;
	for (i = 1; i < count; ++i) {
		Move move = moves[i];
		Move last_move = moves[i - 1];
		Player p = i % 2 == 0 ? player : (1 - player);
		if (p == winner) {
			last_good_reply[last_move][p] = move;
		} else if (last_good_reply[last_move][p] == move) {
			last_good_reply[last_move][p] = INVALID_MOVE;
		}
	}
}

//get last good reply using stored data
static Move get_last_good_reply(Move last_move, Player player) {
	return last_good_reply[last_move][player];
}
#endif

static Move get_default_policy_move(Position* pos) {
	//Move reply = get_last_good_reply(pos->last_move, pos->player);
	//Move move;
	//if (Position_is_valid_move(pos, reply)) {
	//	move = reply;
	//} else {
	//	move = Position_get_random_move(pos);
	//}

	Move move = INVALID_MOVE;
	if (Position_is_critical(pos)) {
		move = Position_get_random_saving_move(pos);
	}

	if (move == INVALID_MOVE) {
		move = Position_get_random_move(pos);
	}

	return move;
}

/*
** !TODO put local variables in a Ctx
*/
static Real playout(Position* pos, Player player) {
	Real score = 0.0;
	Int i;
	for (i = 1; i <= SAMPLES; ++i) {
		Position tmp;
		Position_copy(&tmp, pos);
		Int h = 0;
		Move move;
		for (move = get_default_policy_move(&tmp);
		        move != INVALID_MOVE;
		        move = get_default_policy_move(&tmp)) {
			Position_do_move(&tmp, move);
			++h;
		}
		Real s;
		if (tmp.player == player) {
			s = 1.0 - P * h;
			s = s > 0.5 ? s : 0.5;
		} else {
			s = P * h;
			s = s < 0.5 ? s : 0.5;
		}
		score += s;
	}
	score /= SAMPLES;
	return score;
}

static Int hashset_use = 0;

/*
** !TODO put local variables in a Ctx
*/
static Position iter_pos;
static void do_one_iteration(Position* pos) {
	Tree* t = root;
	Position_copy(&iter_pos, pos);
	while (Tree_is_fully_expanded(t) && !Tree_is_leaf(t)) {
		t = Tree_UCT_select(t);
		Position_do_move(&iter_pos, t->move);
	}
	if (!Tree_is_leaf(t)) {
		t = Tree_expand(t, &iter_pos);
	}
	Real score;
	if (!Tree_is_leaf(t)) {
		score = playout(&iter_pos, pos->player);
	} else {
		score = pos->player == iter_pos.player ? 1.0 : 0.0;
	}
#if USE_HASH_SET
	TreeIterator* it;
	Int u = 0;
	for (it = HashSet_find(t); it != NULL; it = it->next) {
		if (it->tree->lock == t->lock) {
			++u;
			Tree* tree = it->tree;
			while (tree != NULL) {
				Tree_update(tree, pos->player, score, SAMPLES);
				tree = tree->parent;
			}
		}
	}
	hashset_use += u - 1;
#else
	while (t != NULL) {
		Tree_update(t, pos->player, score, SAMPLES);
		t = t->parent;
	}
#endif
}

Move AI_MCTS_get_best_move(Position* pos, Int max_iterations, Int max_time) {
	Move best_move = INVALID_MOVE;

	if (root == NULL) {
		root = Tree_create(NULL, INVALID_MOVE, pos);
	}

	if (pos->moves < OPENING_MOVES) {
		Tree_prune_unfavorized_from_root(pos);
	}

	if (pos->moves >= CRITICAL_CHECK_LIMIT) {
		Position_activate_critical_check();
	} else {
		Position_deactivate_critical_check();
	}

	Timer_start();
#if USE_TIME_LIMIT
	Timer_set_alarm(max_time);
#endif
	hashset_use = 0;
	Int i;
	for (i = 0; i < max_iterations; ++i) {
		do_one_iteration(pos);

#if USE_TIME_LIMIT
		if (Timer_is_time_over()) {
			break;
		}
#endif

	}
	//verify that the most visited child is also the higher value child
	Tree* selected = Tree_select_most_visited(root);
	Tree* concurrent = Tree_select(root);

	Int vi;
	for (vi = 0; (selected->value + EPSILON < concurrent->value) && (vi < MAX_VERIFICATION_ITERATIONS); ++vi) {
		do_one_iteration(pos);
		selected = Tree_select_most_visited(root);
		concurrent = Tree_select(root);
	}
#if USE_TIME_LIMIT
	Timer_clear_alarm();
#endif
	Timer_stop();
	Int dt = Timer_get_delta_time();
	Int tt = Timer_get_total_time();
	if (dt != 0) {
		ratio = 1000 * root->visits / dt;
	}
	best_move = selected->move;
	Util_fprflush(stderr, "mt=%d\n", max_time);
	Util_fprflush(stderr, "c=%d\n", root->children_count);
	Util_fprflush(stderr, "i=%d vi=%d v=%.2f n=%d dt=%d tt=%d r=%d\n",
	              i, vi, selected->value, selected->visits, dt, tt, ratio);
	Util_fprflush(stderr, "hsu=%d\n", hashset_use);
	Tree_display_expected_variation(root);

	//Util_fprflush(stderr, "(");
	//for (i = 0; i < root->children_count; ++i) {
	//	if (i > 0) {
	//		Util_fprflush(stderr, " ");
	//	}
	//
	//	Util_fprflush(stderr, "%d", root->children[i]->visits);
	//}
	//Util_fprflush(stderr, ")\n");

	return best_move;
}
