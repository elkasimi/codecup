#include "Common.h"

#include "Position.h"


//Optimize as possible this function
Int __Group_find_possible_tos(Group* group, Position* pos, Int tos[NXN], Int* dmin) {
	//INIT MIND = OO
	//DO A BFS SEARCH
	//ADD ELEMENT WHEN ITS DISTANCE ISS LESS THAN MIND
	//WHENEVER YOU REACH A NEW GROUP
	//UPDATE MIND
	//MARK THE ORIGIN NEIGHBOUR AS A POSSIBLE MOVE
	Int f, mind, d[NXN], origin[NXN];
	Bool possible[NXN];
	Queue q;
	mind = OO;
	memset(possible, FALSE, NXN);
	Queue_init(&q);
	for (f = 0; f < NXN; ++f) {
		origin[f] = -1;
		if (Group_has_member(group, f)) {
			d[f] = 0;
		} else if (Group_has_neighbor(group, f)) {
			if (pos->owner[f] == NONE) {
				d[f] = 1;
				origin[f] = f;
				Queue_push(&q, f);
			}
		} else {
			d[f] = OO;
		}
	}
	Int c = 0;
	while (!Queue_is_empty(&q)) {
		Int t, *n;
		t = Queue_pop(&q);

		if (d[t] > mind) {
			break;
		}

		Int ot = origin[t];
		if (possible[ot]) {
			continue;
		}

		for (n = neighbors[t]; *n != END; ++n) {
			if (pos->owner[*n] == NONE) {
				if (d[*n] >= d[t] + 1) {
					d[*n] = d[t] + 1;
					Queue_push(&q, *n);
					origin[*n] = origin[t];
				}
			} else if (pos->owner[*n] == group->owner) {
				if (!Group_has_member(group, *n)) {
					//we reach one of the nearest group so ..

					//update min distance
					mind = d[t];

					//mark the origin as possible
					Int o = origin[t];
					if (!possible[o]) {
						possible[o] = TRUE;
						tos[c++] = o;
					}

					break;
				}
			}
		}
	}

	*dmin = mind;

	return c;
}

Int __Group_find_possible_tos(Group* group, Position* pos, Int tos[NXN], Int* dmin);
Int Group_find_possible_tos(Group* group, Position* pos, Int tos[NXN], Int* dmin);

static void GroupCheck(Group* group, Position* pos) {
	Bool b1[NXN], b2[NXN];
	Int i;
	for (i = 0; i < NXN; ++i) {
		b1[i] = b2[i] = FALSE;
	}

	Int tos[NXN];
	Int d1;
	Int c1 = Group_find_possible_tos(group, pos, tos, &d1);
	for (i = 0; i < c1; ++i) {
		Int t = tos[i];
		b1[t] = TRUE;
	}
	Int d2;
	Int c2 = __Group_find_possible_tos(group, pos, tos, &d2);
	for (i = 0; i < c2; ++i) {
		Int t = tos[i];
		b2[t] = TRUE;
	}

	if (d1 != d2) {
		Util_fprflush(stderr, "distance bug!!\n");
	}

	for (i = 0; i < NXN; ++i) {
		if (b1[i] != b2[i]) {
			Util_fprflush(stderr, "to bug!!\n");
			Util_fprflush(stderr, "Group_find_possible_tos ==> %d %d!!\n", i, b1[i]);
			Util_fprflush(stderr, "__Group_find_possible_tos ==> %d %d!!\n", i, b2[i]);
			Position_display(pos);
			Util_fprflush(stderr, "\n\n");
			getchar();
		}
	}
}

static void PositionCheck(Position* pos) {
	Int count = pos->player == WHITE ? pos->white_groups_count : pos->black_groups_count;
	Int* groups_idx = pos->player == WHITE ? pos->white_groups_idx : pos->black_groups_idx;
	Group* groups = pos->player == WHITE ? pos->white_groups : pos->black_groups;
	Int i;
	for (i = 0; i < count; ++i) {
		Int idx = groups_idx[i];
		Group* g = &groups[idx];
		GroupCheck(g, pos);
	}
}

static void Check() {
	Position pos;
	Position_init(&pos);
	Move move;
	for (move = Position_get_random_move(&pos); move != INVALID_MOVE; move = Position_get_random_move(&pos)) {
		Position_do_move(&pos, move);
		PositionCheck(&pos);
	}
	Util_fprflush(stderr, "Check finished!\n");
}

void CheckRandomness() {
	Position pos;
	Position_init(&pos);
	Move move;
	Int r = 0;
	for (move = Position_get_random_move(&pos); (r < 40) && (move != INVALID_MOVE); move = Position_get_random_move(&pos), ++r) {
		Position_do_move(&pos, move);
	}

	Position_display(&pos);
	int m[16000];
	int i;
	for (i = 0; i < 16000; ++i) {
		m[i] = 0;
	}

	Group* g = NULL;
	int max = 0;
	for (i = 0; i < pos.white_groups_count; ++i) {
		int idx = pos.white_groups_idx[i];
		Group* t = &pos.white_groups[idx];
		int dmin;
		MoveList moves;
		int len = Group_get_possible_moves(t, &pos, moves, &dmin);
		if (max < len) {
			max = len;
			g = t;
		}
	}

	for (i = 0; i < 10000; ++i) {
		move = Group_get_random_move(g, &pos);
		m[move]++;
	}

	MoveList moves;
	int dmin;
	Int c = Group_get_possible_moves(g, &pos, moves, &dmin);

	for (i = 0; i < c; ++i) {
		IO_print_move(stderr, moves[i]);
		Util_fprflush(stderr, " %d\n", m[moves[i]]);
	}
}
