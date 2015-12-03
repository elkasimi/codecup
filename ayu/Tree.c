#include "Common.h"

#include "Tree.h"
#include "Position.h"
#include "Util.h"
#include "IO.h"
#include "HashSet.h"
#include "Data.h"
#include "Timer.h"

#define T 40

static Int curr_tree = 0;

static Real UCTK = 0.1;

Tree* root = NULL;

int Tree_get_allocated_trees_count() {
	return curr_tree;
}

void Tree_destroy_root() {
	if (root != NULL) {
		Tree_destroy(root);
		root = NULL;
	}
}

void Tree_update_root(Move move) {
	Timer_start();
	if (root != NULL) {
		Tree* selected = NULL;
		Int i;
		for (i = 0; i < root->children_count; ++i) {
			Tree* child = root->children[i];
			if (child->move == move) {
				selected = child;
			} else {
				Tree_destroy(child);
			}
		}
		if (selected != NULL) {
			selected->parent = NULL;
		}
		root = selected;
	}
	Timer_stop();
	Int dt = Timer_get_delta_time();
	if (root == NULL) {
		Util_fprflush(stderr, "root=null dt=%d\n", dt);
	} else {
		Util_fprflush(stderr, "root={v:%d,a:%d} dt=%d\n", root->visits, curr_tree, dt);
	}
}

void Tree_update_root_children_bias(Position* pos) {
	if(root != NULL) {
		Int i;
		for (i = 0; i < root->children_count; ++i) {
			Tree* child = root->children[i];
			Position tmp;
			Position_copy(&tmp, pos);
			Position_do_move(&tmp, child->move);
			child->bias = Position_get_heuristic_value(&tmp, child->move);
		}
	}
}


void Tree_destroy(Tree* t) {
	--curr_tree;
	Int i;
	for (i = 0; i < t->children_count; ++i) {
		Tree* child = t->children[i];
		Tree_destroy(child);
	}

#if USE_HASH_SET
	HashSet_remove(t);
#endif
	free(t);
}

#define MAX_MOVE_VALUE 16000
static Bool favorized_move[MAX_MOVE_VALUE];
void Tree_prune_unfavorized_from_root(Position* pos) {
	memset(favorized_move, FALSE, MAX_MOVE_VALUE);

	MoveList moves;
	Int c = Position_get_favorized_moves(pos, moves);
	Int i;
	for (i = 0; i < c; ++i) {
		Int idx = (Int)moves[i];
		favorized_move[idx] = TRUE;
	}

	//prune from expanded children
	for (i = 0; i < root->children_count;) {
		Tree* child = root->children[i];
		Int idx = (Int)child->move;
		if (favorized_move[idx]) {
			++i;
		} else {
			Int count = root->children_count;
			root->children[i] = root->children[count - 1];
			root->children_count = count - 1;
			Tree_destroy(child);
		}
	}

	//prune from untried moves
	for (i = 0; i < root->untried_moves_count;) {
		Int idx = (Int)root->untried_moves[i];
		if (favorized_move[idx]) {
			++i;
		} else {
			Int count = root->untried_moves_count;
			root->untried_moves[i] = root->untried_moves[count - 1];
			root->untried_moves_count = count - 1;
		}
	}
}

Tree* Tree_create(Tree* parent, Move move, Position* pos) {
	++curr_tree;
	Tree* t = (Tree*)malloc(sizeof(Tree));
	t->parent = parent;
	t->level = (parent != NULL) ? (parent->level + 1) : 0;
	t->player = pos->last_player;
	t->move = move;
#if USE_HASH_SET
	t->hash = pos->hash;
	t->lock = pos->lock;
#endif
	t->untried_moves_count = Position_get_moves(pos, t->untried_moves);
	t->is_leaf = (t->untried_moves_count == 0);
	t->children_count = 0;
	//init tree value
	t->value = 0.0;
	t->visits = 0;
	t->bias = 0.0;
#if USE_HASH_SET
	HashSet_store(t);
#endif
	return t;
}

Bool Tree_is_fully_expanded(Tree* t) {
	return (t->untried_moves_count == 0);
}

Bool Tree_is_leaf(Tree* t) {
	return t->is_leaf;
}

Tree* Tree_select(Tree* t) {
	Tree* selected = NULL;
	Real best_value = -OO;
	Int i;
	for (i = 0; i < t->children_count; ++i) {
		Tree* child = t->children[i];
		if (best_value < child->value) {
			best_value = child->value;
			selected = child;
		}
	}
	return selected;
}

Tree* Tree_UCT_select(Tree* t) {
	Tree* selected = NULL;
	Real best_value = -OO;
	Int i;
	for (i = 0; i < t->children_count; ++i) {
		Tree* child = t->children[i];
		Real value = child->value;
		value += UCTK * sqrt(log((Real)t->visits) / child->visits);
		//value += child->bias / child->visits;
		if (best_value < value) {
			best_value = value;
			selected = child;
		}
	}
	return selected;
}

Tree* Tree_GIBBS_select(Tree* t) {
	Real values[MAX_MOVES];
	Int i;
	Int c = t->children_count;
	for (i = 0; i < c; ++i) {
		Tree* child = t->children[i];
		values[i] = exp(T * child->value);
		if (i > 0) {
			values[i] += values[i - 1];
		}
	}

	Real max_value = values[c - 1];
	Int m = 0;
	Int M = c - 1;
	Real r = rand();
	r *= max_value;
	r /= RAND_MAX;
	while (m < M) {
		int a = (m + M) >> 1;
		if (r < values[a]) {
			M = a;
		} else {
			m = a + 1;
		}
	}

	Tree* selected = t->children[M];

	return selected;
}

Tree* Tree_select_most_visited(Tree* t) {
	Tree* selected = NULL;
	Int i, max_visits = -OO;
	for (i = 0; i < t->children_count; ++i) {
		Tree* child = t->children[i];
		if (max_visits < child->visits) {
			max_visits = child->visits;
			selected = child;
		}
	}
	return selected;
}

Tree* Tree_select_with_move(Tree* t, Move move) {
	Tree* selected = NULL;
	if (t != NULL) {
		Int i;
		for (i = 0; i < t->children_count; ++i) {
			Tree* child = t->children[i];
			if (child->move == move) {
				selected = child;
				break;
			}
		}
	}
	return selected;
}

Tree* Tree_expand(Tree* t, Position* pos) {
	int r = rand() % t->untried_moves_count;
	Move move = t->untried_moves[r];
	Position_do_move(pos, move);
	//remove from untried moves
	t->untried_moves_count -= 1;
	t->untried_moves[r] = t->untried_moves[t->untried_moves_count];
	Tree* new_child = Tree_create(t, move, pos);
	//add to children
	t->children[t->children_count] = new_child;
	t->children_count += 1;
	return new_child;
}

void Tree_update(Tree* t, Player player, Real score, Int count) {
	t->value *= t->visits;
	if (t->player == player) {
		t->value += score * count;
	} else {
		t->value += (1 - score) * count;
	}
	t->visits += count;
	t->value /= t->visits;
}

void Tree_display_expected_variation(Tree* root) {
	Util_fprflush(stderr, "ev=r(%d)", root->visits);
	Tree* t = root;
	Int l = 0;
	while (Tree_is_fully_expanded(t) && !Tree_is_leaf(t)) {
		Util_fprflush(stderr, "->");
		if (l == 4) {
			Util_fprflush(stderr, "..");
			break;
		} else {
			++l;
		}
		Tree* next = Tree_select_most_visited(t);
		IO_print_move(stderr, next->move);
		Util_fprflush(stderr, "(%d)", next->visits);
		t = next;
	}
	Util_fprflush(stderr, "\n");
}
