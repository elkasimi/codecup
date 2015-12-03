#include "Common.h"

#include "Position.h"
#include "Group.h"
#include "Queue.h"
#include "Data.h"
#include "Util.h"

static void Position_zobrist_toggle_player(Position* pos) {
#if USE_HASH_SET
	pos->hash ^= zobrist_hash_player;
	pos->lock ^= zobrist_lock_player;
#endif
}

static void Position_zobrist_toggle_field(Position* pos, Int f, Player player) {
#if USE_HASH_SET
	Int i = (Int)player;
	pos->hash ^= zobrist_hash_field[f][i];
	pos->lock ^= zobrist_lock_field[f][i];
#endif
}

static void Position_change_player(Position* pos) {
	pos->last_player = pos->player;
	pos->player = 1 - pos->player;
}


static Bool critical_check = FALSE;

void Position_activate_critical_check() {
	critical_check = TRUE;
}

void Position_deactivate_critical_check() {
	critical_check = FALSE;
}

void Position_init(Position* pos) {
	Int i, j;
#if USE_HASH_SET
	pos->hash = zobrist_hash_init_value;
	pos->lock = zobrist_lock_init_value;
#endif
	pos->player = WHITE;
	pos->last_player = BLACK;
	pos->white_groups_count = 0;
	pos->black_groups_count = 0;
	for (i = 0; i < NXN; ++i) {
		pos->owner[i] = NONE;
	}
	for (i = 0; i < N; ++i) {
		Int j0;
		Player p;
		if (i % 2 == 0) {
			j0 = 1;
			p = WHITE;
		} else {
			j0 = 0;
			p = BLACK;
		}
		for (j = j0; j < N; j += 2) {
			Int f = N * i + j;
			pos->owner[f] = p;
			Position_zobrist_toggle_field(pos, f, p);
			Group* g;
			if (p == WHITE) {
				pos->white_groups_idx[pos->white_groups_count] = pos->white_groups_count;
				g = &pos->white_groups[pos->white_groups_count];
				pos->white_groups_count += 1;
			} else {
				pos->black_groups_idx[pos->black_groups_count] = pos->black_groups_count;
				g = &pos->black_groups[pos->black_groups_count];
				pos->black_groups_count += 1;
			}
			Group_init(g, p);
			Group_add(g, f);

			switch(f) {
			case 1:
			case 9:
			case 11:
			case 21:
			case 99:
			case 109:
			case 111:
			case 119:
				Group_favorize(g);
			}
		}
	}
	pos->last_move = INVALID_MOVE;
	pos->last_random_move_dmin = OO;
	pos->critical = FALSE;
	pos->moves = 0;
}

void Position_copy(Position* dst_pos, Position* src_pos) {
	memcpy(dst_pos, src_pos, sizeof(Position));
}

void Position_do_move(Position* pos, Move move) {
	Int from = FROM(move);
	Int to = TO(move);
	pos->owner[from] = NONE;
	pos->owner[to] = pos->player;
	Position_zobrist_toggle_field(pos, from, pos->player);
	Position_zobrist_toggle_field(pos, to, pos->player);
	Int* count = (pos->player == WHITE) ? &pos->white_groups_count : &pos->black_groups_count;
	Group* groups = (pos->player == WHITE) ? pos->white_groups : pos->black_groups;
	Int* groups_idx = (pos->player == WHITE) ? pos->white_groups_idx : pos->black_groups_idx;
	Int i;
	Group* merged = NULL;
	for (i = 0; i < *count;) {
		Int idx = groups_idx[i];
		Group* g = &groups[idx];
		if (Group_has_neighbor(g, to)) {
			if (merged == NULL) {
				merged = g;
				++i;
			} else {
				Group_merge_with(merged, g);
				*count -= 1;
				groups_idx[i] = groups_idx[*count];
			}
		} else {
			++i;
		}
	}
	Group_add(merged, to);
	Group_remove(merged, from);

	//update criticality of the position
	if (critical_check && (pos->last_random_move_dmin == 1) && (*count >= 2) && (*count <= CRITICAL_GROUP_COUNT)) {
		pos->critical = !Position_player_can_move(pos, pos->player);
	} else {
		pos->critical = FALSE;
	}

	//update player to move
	Position_change_player(pos);
	Position_zobrist_toggle_player(pos);
	pos->last_move = move;
	pos->moves++;
}

Int Position_get_moves(Position* pos, MoveList moves) {
	Int count = (pos->player == WHITE) ? pos->white_groups_count : pos->black_groups_count;
	Group* groups = (pos->player == WHITE) ? pos->white_groups : pos->black_groups;
	Int* groups_idx = (pos->player == WHITE) ? pos->white_groups_idx : pos->black_groups_idx;
	Int moves_count = 0;
	Int i;
	for (i = 0; i < count; ++i) {
		Int idx = groups_idx[i];
		Group* group = &groups[idx];
		Int dmin;
		Int c = Group_get_possible_moves(group, pos, moves + moves_count, &dmin);
		moves_count += c;
	}
	return moves_count;
}

Int Position_get_favorized_moves(Position* pos, MoveList moves) {
	Int count = (pos->player == WHITE) ? pos->white_groups_count : pos->black_groups_count;
	Group* groups = (pos->player == WHITE) ? pos->white_groups : pos->black_groups;
	Int* groups_idx = (pos->player == WHITE) ? pos->white_groups_idx : pos->black_groups_idx;
	Int moves_count = 0;
	Int i;
	for (i = 0; i < count; ++i) {
		Int idx = groups_idx[i];
		Group* group = &groups[idx];
		if (group->favorized) {
			Int dmin;
			Int c = Group_get_possible_moves(group, pos, moves + moves_count, &dmin);
			moves_count += c;
		}
	}

	return moves_count;
}

Bool Position_is_empty(Position* pos, Int f) {
	return (pos->owner[f] == NONE);
}

void Position_display(Position* pos) {
	Int i, j;
	char c;
	Util_fprflush(stderr, "     ");
	for (c = 'A'; c <= 'K'; ++c) {
		Util_fprflush(stderr, "%c  ", c);
	}
	Util_fprflush(stderr, "\n");
	Util_fprflush(stderr, "-----");
	for (c = 'A'; c <= 'K'; ++c) {
		Util_fprflush(stderr, "---", c);
	}
	Util_fprflush(stderr, "\n");
	for (i = N - 1; i >= 0; --i) {
		for (j = 0; j < N; ++j) {
			Int f = N*i + j;
			Player owner;
			char c;
			if (j%N == 0) {
				Util_fprflush(stderr, "%2d | ", i + 1);
			}
			owner = pos->owner[f];
			c = '-';
			switch (owner) {
			case WHITE:
				c = 'X';
				break;
			case BLACK:
				c = 'O';
				break;
			}
			Util_fprflush(stderr, "%c ", c);
			if ((j + 1) % N == 0) {
				Util_fprflush(stderr, "\n");
			} else {
				Util_fprflush(stderr, " ");
			}
		}
	}
	Util_fprflush(stderr, "==>%s\n", pos->player == WHITE ? "White to move." : "Black to move.");
}


Move Position_get_random_move(Position* pos) {
	Move random_move = INVALID_MOVE;
	Int c = (pos->player == WHITE) ? pos->white_groups_count : pos->black_groups_count;
	Group* groups = (pos->player == WHITE) ? pos->white_groups : pos->black_groups;
	Int* groups_idx = (pos->player == WHITE) ? pos->white_groups_idx : pos->black_groups_idx;
	while (c > 0) {
		Int r = rand() % c;
		Int idx = groups_idx[r];
		Group* group = &groups[idx];
		random_move = Group_get_random_move(group, pos);
		if (random_move != INVALID_MOVE) {
			break;
		} else {
			Int t = groups_idx[r];
			groups_idx[r] = groups_idx[c - 1];
			groups_idx[c - 1] = t;
			--c;
		}
	}
	
	return random_move;
}

//I didn't have any good biasing function until now :(
Real Position_get_heuristic_value(Position* pos, Move move) {
	(void)move;
	(void)pos;
	Real value = 0.0;

	return value;
}

Bool Position_is_valid_move(Position* pos, Move move) {
	if (move == INVALID_MOVE) {
		return FALSE;
	}

	Int from = FROM(move);
	Int to = TO(move);

	if (pos->owner[from] != pos->player) {
		return FALSE;
	}

	if (pos->owner[to] != NONE) {
		return FALSE;
	}

	//optimize distance check as possible
	Int d[NXN];
	Bool marked[NXN];
	Int f;
	Int dmin = OO;
	for (f = 0; f < NXN; ++f) {
		d[f] = OO;
		marked[f] = FALSE;
	}

	Queue q;
	Queue_init(&q);

	d[from] = 0;
	marked[from] = TRUE;
	Queue_push(&q, from);


	while (!Queue_is_empty(&q)) {
		Int t = Queue_pop(&q);
		Int* n;
		for (n = neighbors[t]; *n != END; ++n) {
			if ((pos->owner[*n] == pos->owner[from]) && !marked[*n]) {
				d[*n] = 0;
				marked[*n] = TRUE;
				Queue_push(&q, *n);
			}
		}
	}

	q.start = 0;
	while (!Queue_is_empty(&q) && (dmin == OO)) {
		Int t = Queue_pop(&q);
		Int* n;
		for (n = neighbors[t]; *n != END; ++n) {
			if ((pos->owner[*n] == NONE) && (d[*n] > d[t] + 1)) {
				d[*n] = d[t] + 1;
				Queue_push(&q, *n);
			}

			if ((pos->owner[*n] == pos->owner[from]) && !marked[*n]) {
				dmin = d[t];
				break;
			}
		}
	}

	if (dmin == OO) {
		return FALSE;
	}

	//verify that to is neighbor of the group
	if (d[to] != 1) {
		return FALSE;
	}

	//verify that to point reach a group with dmin
	Queue_clear(&q);
	for (f = 0; f < NXN; ++f) {
		d[f] = OO;
	}

	d[to] = 1;
	Queue_push(&q, to);

	Int dto = OO;

	while (!Queue_is_empty(&q) && (dmin == OO)) {
		Int t = Queue_pop(&q);
		Int* n;

		if (d[t] > dmin) {
			continue;
		}

		for (n = neighbors[t]; *n != END; ++n) {
			if ((pos->owner[*n] == NONE) && (d[*n] > d[t] + 1)) {
				d[*n] = d[t] + 1;
				Queue_push(&q, *n);
			}

			if ((pos->owner[*n] == pos->owner[from]) && !marked[*n]) {
				dto = d[t];
				break;
			}
		}
	}

	if (dto != dmin) {
		return FALSE;
	}

	//need check that from is not an articulation point
	//!TODO

	return TRUE;
}

Bool Position_is_separating_move(Position* pos, Move move) {
	Int to = TO(move);

	if ((to + 1 < NXN) && (to >= 1) && (pos->owner[to + 1] == pos->last_player) && (pos->owner[to - 1] == pos->last_player)) {
		return TRUE;
	}

	if ((to + N < NXN) && (to >= N) && (pos->owner[to + N] == pos->last_player) && (pos->owner[to - N] == pos->last_player)) {
		return TRUE;
	}

	return FALSE;
}

Bool Position_is_critical(Position* pos) {
	return pos->critical;
}

Bool Position_player_can_move(Position* pos, Player player) {
	Int count = (player == WHITE) ? pos->white_groups_count : pos->black_groups_count;
	Group* groups = (player == WHITE) ? pos->white_groups : pos->black_groups;
	Int* groups_idx = (player == WHITE) ? pos->white_groups_idx : pos->black_groups_idx;
	Int i;
	Bool can_move = FALSE;
	for (i = 0; i < count; ++i) {
		Int idx = groups_idx[i];
		Group* g = &groups[idx];
		Int dmin = Group_get_dmin(g, pos);
		if (dmin != OO) {
			can_move = TRUE;
			break;
		}
	}
	return can_move;
}

static Position saving_pos;
Move Position_get_random_saving_move(Position* pos) {
	//here test all moves from an edge point
	MoveList moves;
	Int count = (pos->player == WHITE) ? pos->white_groups_count : pos->black_groups_count;
	Group* groups = (pos->player == WHITE) ? pos->white_groups : pos->black_groups;
	Int* groups_idx = (pos->player == WHITE) ? pos->white_groups_idx : pos->black_groups_idx;
	Int moves_count = 0;
	Int i;
	for (i = 0; i < count; ++i) {
		Int idx = groups_idx[i];
		Group* group = &groups[idx];
		Int c = Group_get_edge_moves(group, pos, moves + moves_count);
		moves_count += c;
	}

	//simply test if oponent can move after your move
	MoveList choices;
	Int choices_count = 0;
	for (i = 0; i < moves_count; ++i) {
		Move move = moves[i];
		Position_copy(&saving_pos, pos);
		Position_do_move(&saving_pos, move);
		if (Position_player_can_move(&saving_pos, saving_pos.player)) {
			choices[choices_count++] = move;
		}
	}

	Move res = INVALID_MOVE;

	if (choices_count > 0) {
		Int r = rand() % choices_count;
		res = choices[r];
	}

	return res;
}

static struct {
	Int maxd;
	Int canonical;
} BFSResult[60];

static void BFS(Position* pos, Int f0, Bool marked[NXN], Bool reached[NXN], Int* maxd) {
	Queue q;
	Queue_init(&q);
	Int d[NXN];
	Int f;
	for (f = 0; f < NXN; ++f) {
		d[f] = OO;
	}

	marked[f0] = TRUE;
	reached[f0] = TRUE;
	d[f0] = 0;
	Queue_push(&q, f0);
	while (!Queue_is_empty(&q)) {
		Int t = Queue_pop(&q);
		Int* n;
		for (n = neighbors[t]; *n != END; ++n) {
			if (!marked[*n] && (pos->owner[*n] == pos->owner[f0])) {
				marked[*n] = TRUE;
				reached[*n] = TRUE;
				d[*n] = 0;
				Queue_push(&q, *n);
			}
		}
	}

	q.start = 0;
	Int m = 0;
	while (!Queue_is_empty(&q)) {
		Int t = Queue_pop(&q);
		if (pos->owner[t] == pos->owner[f0]) {
			reached[t] = TRUE;
			m = m > d[t] ? m : d[t];
		}

		Int* n;
		for (n = neighbors[t]; *n != END; ++n) {
			if ((pos->owner[*n] == NONE) && (d[*n] > d[t] + 1)) {
				d[*n] = d[t] + 1;
				Queue_push(&q, *n);
			} else if ((pos->owner[*n] == pos->owner[f0]) && (d[*n] > d[t])) {
				d[*n] = d[t];
				Queue_push(&q, *n);
			}
		}
	}


	*maxd = m;
}

void Position_get_diameters(Position* pos, Int* white_diameter_ptr, Int* black_diameter_ptr) {
	Int c = 0;

	Bool marked[NXN];
	memset(marked, FALSE, NXN);

	Int f;
	for (f = 0; f < NXN; ++f) {
		if (marked[f]) {
			continue;
		}

		if (pos->owner[f] == NONE) {
			continue;
		}

		Bool reached[NXN];
		memset(reached, FALSE, NXN);

		Int maxd;
		BFS(pos, f, marked, reached, &maxd);

		Int i;
		for (i = 0; i < c; ++i) {
			Int canonical = BFSResult[i].canonical;
			if (reached[canonical]) {
				if (BFSResult[i].maxd < maxd) {
					BFSResult[i].maxd = maxd;
				}

				break;
			}
		}

		if (i == c) {
			BFSResult[i].maxd = maxd;
			BFSResult[i].canonical = f;
			c += 1;
		}
	}

	*white_diameter_ptr = 0;
	*black_diameter_ptr = 0;

	Int i;
	for (i = 0; i < c; ++i) {
		Int canonical = BFSResult[i].canonical;
		if (pos->owner[canonical] == WHITE) {
			*white_diameter_ptr += BFSResult[i].maxd;
		} else {
			*black_diameter_ptr += BFSResult[i].maxd;
		}
	}
}
