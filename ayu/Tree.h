#ifndef __TREE_H__
#define __TREE_H__

typedef struct Tree {
	//the move that got us to this tree
	Move move;

	//the parent tree NULL for root tree
	struct Tree* parent;

	//tree children
	struct Tree* children[MAX_MOVES];
	Int children_count;

	//untried moves
	Int untried_moves_count;
	MoveList untried_moves;

	//Monte Carlo stats
	Real value;
	Real bias;
	Int visits;

	//player just moved
	Player player;

	//to know tree level
	Int level;

	Bool is_leaf;

	//hash and lock of this tree
#if USE_HASH_SET
	UInt hash;
	UInt lock;
#endif
} Tree;

int Tree_get_allocated_trees_count();
Tree* Tree_create(Tree* parent, Move move, Position* pos);
void Tree_destroy(Tree* t);
void Tree_prune_unfavorized_from_root(Position* pos);
void Tree_destroy_root();
void Tree_update_root(Move move);
void Tree_update_root_children_bias(Position* pos);
Bool Tree_is_leaf(Tree* t);
Bool Tree_is_fully_expanded(Tree* t);
Tree* Tree_UCT_select(Tree* t);
Tree* Tree_GIBBS_select(Tree* t);
Tree* Tree_select(Tree* t);
Tree* Tree_select_most_visited(Tree* t);
Tree* Tree_select_with_move(Tree* t, Move move);
Tree* Tree_expand(Tree* t, Position* pos);
void Tree_update(Tree* t, Player player, Real score, Int count);
void Tree_display_expected_variation(Tree* t);

typedef struct TreeIterator {
	Tree* tree;
	struct TreeIterator* next;
} TreeIterator;

extern Tree* root;

#endif
