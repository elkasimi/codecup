#include "Common.h"

#include "Group.h"
#include "Position.h"
#include "Queue.h"
#include "Stack.h"
#include "Data.h"
#include "Util.h"

void Group_init(Group* group, Player owner) {
	group->owner = owner;
	group->count = 0;
	Int i;
	for (i = 0; i < NXN; ++i) {
		group->has_member[i] = FALSE;
		group->neighbors[i] = 0;
		group->froms_count = 0;
	}
	group->need_check = FALSE;
	group->favorized = FALSE;
}

void Group_copy(Group* dst_group, Group* src_group) {
	memcpy(dst_group, src_group, sizeof(Group));
}

void Group_favorize(Group* group) {
	group->favorized = TRUE;
}

void Group_add(Group* group, Int m) {
	if (!Group_has_member(group, m)) {
		group->has_member[m] = TRUE;
		group->members[group->count] = m;
		group->count += 1;
		Int* n = neighbors[m];
		for (; *n != END; ++n) {
			group->neighbors[*n] += 1;
		}
		group->need_check = TRUE;
	}
}

void Group_remove(Group* group, Int m) {
	if (Group_has_member(group, m)) {
		group->has_member[m] = FALSE;
		Int i;
		Int idx = -1;
		Int c = group->count;
		for (i = 0; i < c; ++i) {
			if (group->members[i] == m) {
				idx = i;
				break;
			}
		}
		group->members[idx] = group->members[c - 1];
		group->count -= 1;
		Int* n = neighbors[m];
		for (; *n != END; ++n) {
			group->neighbors[*n] -= 1;
		}
		group->need_check = TRUE;
	}
}

Bool Group_has_member(Group* group, Int m) {
	return group->has_member[m];
}

Bool Group_has_neighbor(Group* group, Int n) {
	return (group->neighbors[n] > 0);
}

void Group_merge_with(Group* group, Group* other_group) {
	Int i;
	for (i = 0; i < other_group->count; ++i) {
		Int m = other_group->members[i];
		Group_add(group, m);
	}

	group->favorized |= other_group->favorized;
}

#define NIL -1

static void articulation(Position* pos, Int u, Bool visited[NXN], Int disc[NXN], Int low[NXN], Int parent[NXN], Bool ap[NXN]) {
	// A static variable is used for simplicity, we can avoid use of static
	// variable by passing a pointer.
	static Int time = 0;
	// Count of children in DFS Tree
	Int children = 0;
	// Mark the current node as visited
	visited[u] = TRUE;
	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;
	// Go through all vertices adjacent to this
	Int* n;
	for (n = neighbors[u]; *n != END; ++n) {
		Int v = *n;
		if (pos->owner[u] != pos->owner[v]) {
			continue;
		}
		// If v is not visited yet, then make it a child of u
		// in DFS tree and recur for it
		if (!visited[v]) {
			children++;
			parent[v] = u;
			articulation(pos, v, visited, disc, low, parent, ap);
			// Check if the sub-tree rooted with v has a connection to
			// one of the ancestors of u
			low[u] = low[u] < low[v] ? low[u] : low[v];
			// u is an articulation point in following cases
			// (1) u is root of DFS tree and has two or more children.
			if (parent[u] == NIL && children > 1) {
				ap[u] = TRUE;
			}
			// (2) If u is not root and low value of one of its child is more
			// than discovery value of u.
			if (parent[u] != NIL && low[v] >= disc[u]) {
				ap[u] = TRUE;
			}
		}
		// Update low value of u for parent function calls.
		else if (v != parent[u]) {
			low[u] = low[u] < disc[v] ? low[u] : disc[v];
		}
	}
}

static Int Group_find_possible_froms(Group* group, Position* pos, Int froms[NXN]) {
	if (group->need_check) {
		//find non articulation points as the from moves
		Bool visited[NXN], ap[NXN];
		Int i, disc[NXN], low[NXN], parent[NXN];
		for (i = 0; i < group->count; ++i) {
			Int m = group->members[i];
			parent[m] = NIL;
			visited[m] = FALSE;
			ap[m] = FALSE;
		}

		for (i = 0; i < group->count; ++i) {
			Int m = group->members[i];
			if (!visited[m]) {
				articulation(pos, m, visited, disc, low, parent, ap);
			}
		}

		Int c = 0;
		for (i = 0; i < group->count; ++i) {
			Int m = group->members[i];
			if (!ap[m]) {
				group->froms[c++] = m;
			}
		}
		group->froms_count = c;
		group->need_check = FALSE;
	}

	Int count = group->froms_count;
	memcpy(froms, group->froms, count * sizeof(Int));

	return count;
}

#define RIGHT 1
#define LEFT 2
#define UP 4
#define DOWN 8

static Int oriented_neighbors[NXN][9] = {
	{ 11, DOWN, 1, LEFT, END },
	{ 12, DOWN, 0, RIGHT, 2, LEFT, END },
	{ 13, DOWN, 1, RIGHT, 3, LEFT, END },
	{ 14, DOWN, 2, RIGHT, 4, LEFT, END },
	{ 15, DOWN, 3, RIGHT, 5, LEFT, END },
	{ 16, DOWN, 4, RIGHT, 6, LEFT, END },
	{ 17, DOWN, 5, RIGHT, 7, LEFT, END },
	{ 18, DOWN, 6, RIGHT, 8, LEFT, END },
	{ 19, DOWN, 7, RIGHT, 9, LEFT, END },
	{ 20, DOWN, 8, RIGHT, 10, LEFT, END },
	{ 21, DOWN, 9, RIGHT, END },
	{ 0, UP, 22, DOWN, 12, LEFT, END },
	{ 1, UP, 23, DOWN, 11, RIGHT, 13, LEFT, END },
	{ 2, UP, 24, DOWN, 12, RIGHT, 14, LEFT, END },
	{ 3, UP, 25, DOWN, 13, RIGHT, 15, LEFT, END },
	{ 4, UP, 26, DOWN, 14, RIGHT, 16, LEFT, END },
	{ 5, UP, 27, DOWN, 15, RIGHT, 17, LEFT, END },
	{ 6, UP, 28, DOWN, 16, RIGHT, 18, LEFT, END },
	{ 7, UP, 29, DOWN, 17, RIGHT, 19, LEFT, END },
	{ 8, UP, 30, DOWN, 18, RIGHT, 20, LEFT, END },
	{ 9, UP, 31, DOWN, 19, RIGHT, 21, LEFT, END },
	{ 10, UP, 32, DOWN, 20, RIGHT, END },
	{ 11, UP, 33, DOWN, 23, LEFT, END },
	{ 12, UP, 34, DOWN, 22, RIGHT, 24, LEFT, END },
	{ 13, UP, 35, DOWN, 23, RIGHT, 25, LEFT, END },
	{ 14, UP, 36, DOWN, 24, RIGHT, 26, LEFT, END },
	{ 15, UP, 37, DOWN, 25, RIGHT, 27, LEFT, END },
	{ 16, UP, 38, DOWN, 26, RIGHT, 28, LEFT, END },
	{ 17, UP, 39, DOWN, 27, RIGHT, 29, LEFT, END },
	{ 18, UP, 40, DOWN, 28, RIGHT, 30, LEFT, END },
	{ 19, UP, 41, DOWN, 29, RIGHT, 31, LEFT, END },
	{ 20, UP, 42, DOWN, 30, RIGHT, 32, LEFT, END },
	{ 21, UP, 43, DOWN, 31, RIGHT, END },
	{ 22, UP, 44, DOWN, 34, LEFT, END },
	{ 23, UP, 45, DOWN, 33, RIGHT, 35, LEFT, END },
	{ 24, UP, 46, DOWN, 34, RIGHT, 36, LEFT, END },
	{ 25, UP, 47, DOWN, 35, RIGHT, 37, LEFT, END },
	{ 26, UP, 48, DOWN, 36, RIGHT, 38, LEFT, END },
	{ 27, UP, 49, DOWN, 37, RIGHT, 39, LEFT, END },
	{ 28, UP, 50, DOWN, 38, RIGHT, 40, LEFT, END },
	{ 29, UP, 51, DOWN, 39, RIGHT, 41, LEFT, END },
	{ 30, UP, 52, DOWN, 40, RIGHT, 42, LEFT, END },
	{ 31, UP, 53, DOWN, 41, RIGHT, 43, LEFT, END },
	{ 32, UP, 54, DOWN, 42, RIGHT, END },
	{ 33, UP, 55, DOWN, 45, LEFT, END },
	{ 34, UP, 56, DOWN, 44, RIGHT, 46, LEFT, END },
	{ 35, UP, 57, DOWN, 45, RIGHT, 47, LEFT, END },
	{ 36, UP, 58, DOWN, 46, RIGHT, 48, LEFT, END },
	{ 37, UP, 59, DOWN, 47, RIGHT, 49, LEFT, END },
	{ 38, UP, 60, DOWN, 48, RIGHT, 50, LEFT, END },
	{ 39, UP, 61, DOWN, 49, RIGHT, 51, LEFT, END },
	{ 40, UP, 62, DOWN, 50, RIGHT, 52, LEFT, END },
	{ 41, UP, 63, DOWN, 51, RIGHT, 53, LEFT, END },
	{ 42, UP, 64, DOWN, 52, RIGHT, 54, LEFT, END },
	{ 43, UP, 65, DOWN, 53, RIGHT, END },
	{ 44, UP, 66, DOWN, 56, LEFT, END },
	{ 45, UP, 67, DOWN, 55, RIGHT, 57, LEFT, END },
	{ 46, UP, 68, DOWN, 56, RIGHT, 58, LEFT, END },
	{ 47, UP, 69, DOWN, 57, RIGHT, 59, LEFT, END },
	{ 48, UP, 70, DOWN, 58, RIGHT, 60, LEFT, END },
	{ 49, UP, 71, DOWN, 59, RIGHT, 61, LEFT, END },
	{ 50, UP, 72, DOWN, 60, RIGHT, 62, LEFT, END },
	{ 51, UP, 73, DOWN, 61, RIGHT, 63, LEFT, END },
	{ 52, UP, 74, DOWN, 62, RIGHT, 64, LEFT, END },
	{ 53, UP, 75, DOWN, 63, RIGHT, 65, LEFT, END },
	{ 54, UP, 76, DOWN, 64, RIGHT, END },
	{ 55, UP, 77, DOWN, 67, LEFT, END },
	{ 56, UP, 78, DOWN, 66, RIGHT, 68, LEFT, END },
	{ 57, UP, 79, DOWN, 67, RIGHT, 69, LEFT, END },
	{ 58, UP, 80, DOWN, 68, RIGHT, 70, LEFT, END },
	{ 59, UP, 81, DOWN, 69, RIGHT, 71, LEFT, END },
	{ 60, UP, 82, DOWN, 70, RIGHT, 72, LEFT, END },
	{ 61, UP, 83, DOWN, 71, RIGHT, 73, LEFT, END },
	{ 62, UP, 84, DOWN, 72, RIGHT, 74, LEFT, END },
	{ 63, UP, 85, DOWN, 73, RIGHT, 75, LEFT, END },
	{ 64, UP, 86, DOWN, 74, RIGHT, 76, LEFT, END },
	{ 65, UP, 87, DOWN, 75, RIGHT, END },
	{ 66, UP, 88, DOWN, 78, LEFT, END },
	{ 67, UP, 89, DOWN, 77, RIGHT, 79, LEFT, END },
	{ 68, UP, 90, DOWN, 78, RIGHT, 80, LEFT, END },
	{ 69, UP, 91, DOWN, 79, RIGHT, 81, LEFT, END },
	{ 70, UP, 92, DOWN, 80, RIGHT, 82, LEFT, END },
	{ 71, UP, 93, DOWN, 81, RIGHT, 83, LEFT, END },
	{ 72, UP, 94, DOWN, 82, RIGHT, 84, LEFT, END },
	{ 73, UP, 95, DOWN, 83, RIGHT, 85, LEFT, END },
	{ 74, UP, 96, DOWN, 84, RIGHT, 86, LEFT, END },
	{ 75, UP, 97, DOWN, 85, RIGHT, 87, LEFT, END },
	{ 76, UP, 98, DOWN, 86, RIGHT, END },
	{ 77, UP, 99, DOWN, 89, LEFT, END },
	{ 78, UP, 100, DOWN, 88, RIGHT, 90, LEFT, END },
	{ 79, UP, 101, DOWN, 89, RIGHT, 91, LEFT, END },
	{ 80, UP, 102, DOWN, 90, RIGHT, 92, LEFT, END },
	{ 81, UP, 103, DOWN, 91, RIGHT, 93, LEFT, END },
	{ 82, UP, 104, DOWN, 92, RIGHT, 94, LEFT, END },
	{ 83, UP, 105, DOWN, 93, RIGHT, 95, LEFT, END },
	{ 84, UP, 106, DOWN, 94, RIGHT, 96, LEFT, END },
	{ 85, UP, 107, DOWN, 95, RIGHT, 97, LEFT, END },
	{ 86, UP, 108, DOWN, 96, RIGHT, 98, LEFT, END },
	{ 87, UP, 109, DOWN, 97, RIGHT, END },
	{ 88, UP, 110, DOWN, 100, LEFT, END },
	{ 89, UP, 111, DOWN, 99, RIGHT, 101, LEFT, END },
	{ 90, UP, 112, DOWN, 100, RIGHT, 102, LEFT, END },
	{ 91, UP, 113, DOWN, 101, RIGHT, 103, LEFT, END },
	{ 92, UP, 114, DOWN, 102, RIGHT, 104, LEFT, END },
	{ 93, UP, 115, DOWN, 103, RIGHT, 105, LEFT, END },
	{ 94, UP, 116, DOWN, 104, RIGHT, 106, LEFT, END },
	{ 95, UP, 117, DOWN, 105, RIGHT, 107, LEFT, END },
	{ 96, UP, 118, DOWN, 106, RIGHT, 108, LEFT, END },
	{ 97, UP, 119, DOWN, 107, RIGHT, 109, LEFT, END },
	{ 98, UP, 120, DOWN, 108, RIGHT, END },
	{ 99, UP, 111, LEFT, END },
	{ 100, UP, 110, RIGHT, 112, LEFT, END },
	{ 101, UP, 111, RIGHT, 113, LEFT, END },
	{ 102, UP, 112, RIGHT, 114, LEFT, END },
	{ 103, UP, 113, RIGHT, 115, LEFT, END },
	{ 104, UP, 114, RIGHT, 116, LEFT, END },
	{ 105, UP, 115, RIGHT, 117, LEFT, END },
	{ 106, UP, 116, RIGHT, 118, LEFT, END },
	{ 107, UP, 117, RIGHT, 119, LEFT, END },
	{ 108, UP, 118, RIGHT, 120, LEFT, END },
	{ 109, UP, 119, RIGHT, END },
};

static Int dirs[16][5] = {
	{ 0 },
	{ +1, 0 },
	{ -1, 0 },
	{ +1, -1, 0 },
	{ +N, 0 },
	{ +1, +N, 0 },
	{ -1, +N, 0 },
	{ +1, -1, +N, 0 },
	{ -N, 0 },
	{ +1, -N, 0 },
	{ -1, -N, 0 },
	{ +1, -1, -N, 0 },
	{ +N, -N, 0 },
	{ +1, +N, -N, 0 },
	{ -1, +N, -N, 0 },
	{ +1, -1, +N, -N, 0 },
};

Int Group_find_possible_tos(Group* group, Position* pos, Int tos[NXN], Int* dmin) {
	Queue q;
	Queue_init(&q);

	Int d[NXN], prev[NXN];
	Bool possible[NXN], used[NXN];
	Int f;
	for (f = 0; f < NXN; ++f) {
		prev[f] = 0;
		possible[f] = FALSE;
		used[f] = FALSE;
		if (Group_has_member(group, f)) {
			d[f] = 0;
		} else if (Group_has_neighbor(group, f)) {
			if (pos->owner[f] == NONE) {
				d[f] = 1;
				Queue_push(&q, f);
			}
		} else {
			d[f] = OO;
		}
	}

	Int m = OO;
	Int c = 0;
	while (!Queue_is_empty(&q)) {
		Int t = Queue_pop(&q);

		if (d[t] > m) {
			break;
		}

		Int* n;
		for (n = oriented_neighbors[t]; *n != END; n += 2) {
			if (pos->owner[*n] == NONE) {
				if (d[*n] >= d[t] + 1) {
					if (d[*n] > d[t] + 1) {
						prev[*n] = 0;
						d[*n] = d[t] + 1;
						Queue_push(&q, *n);
					}

					prev[*n] |= *(n + 1);
				}
			} else if (pos->owner[*n] == group->owner) {
				if (!Group_has_member(group, *n)) {
					//here we reach one of the nearest group
					m = d[t];

					//mark the starting neighbor as possible
					Stack s;
					Stack_init(&s);
					Stack_push(&s, t);
					while (!Stack_is_empty(&s)) {
						Int top = Stack_pop(&s);

						if (used[top]) {
							continue;
						}

						used[top] = TRUE;

						Int prev_top = prev[top];
						if (prev_top == 0) {
							if (!possible[top]) {
								possible[top] = TRUE;
								tos[c++] = top;
							}
						} else {
							Int* dir;
							for (dir = dirs[prev_top]; *dir != 0; ++dir) {
								Stack_push(&s, top + *dir);
							}
						}
					}
				}
			}
		}
	}

	*dmin = m;

	return c;
}

Int Group_get_possible_moves(Group* group, Position* pos, MoveList moves, Int* dmin) {
	Int tos[NXN];
	Int tos_len = Group_find_possible_tos(group, pos, tos, dmin);

	if (tos_len == 0) {
		return 0;
	}

	Int froms[NXN];
	Int froms_len = Group_find_possible_froms(group, pos, froms);

	Int i, j;
	Int c = 0;
	for (i = 0; i < froms_len; ++i) {
		for (j = 0; j < tos_len; ++j) {
			Int from = froms[i];
			Int to = tos[j];
			//check here if:
			// 1 - "to" point is neighbor to another point than from or
			// 2 - group is a unit group
			if ((group->count == 1) || (group->neighbors[to] > 1) || (!are_neighbors[from][to])) {
				moves[c++] = MAKE_MOVE(from, to);
			}
		}
	}

	return c;
}

Int Group_get_edge_moves(Group* group, Position* pos, MoveList moves) {
	Int tos[NXN];
	Int dmin;
	Int tos_len = Group_find_possible_tos(group, pos, tos, &dmin);

	if (tos_len == 0) {
		return 0;
	}

	Int froms[NXN];
	Int froms_len = Group_find_possible_froms(group, pos, froms);

	Int i, j;
	Int c = 0;
	for (i = 0; i < froms_len; ++i) {
		for (j = 0; j < tos_len; ++j) {
			Int from = froms[i];
			if (!Util_is_edge(from)) {
				continue;
			}

			Int to = tos[j];
			//check here if:
			// 1 - "to" point is neighbor to another point than from or
			// 2 - group is a unit group
			if ((group->count == 1) || (group->neighbors[to] > 1) || (!are_neighbors[from][to])) {
				moves[c++] = MAKE_MOVE(from, to);
			}
		}
	}

	return c;
}

/*
which one to choose ??
static Int Group_get_random_to(Group* group, Position* pos, Int* dmin) {
Int to = -1;
Int tos[NXN];
Int len = Group_find_possible_tos(group, pos, tos, dmin);
if (len > 0) {
Int r = rand() % len;
to = tos[r];
}

return to;
}
*/

static Int Group_get_random_to(Group* group, Position* pos, Int* dmin) {
	Int f, prev[NXN], d[NXN];
	for (f = 0; f < NXN; ++f) {
		prev[f] = -1;
		d[f] = OO;
	}

	Queue q;
	Queue_init(&q);

	for (f = 0; f < NXN; ++f) {
		if (Group_has_member(group, f)) {
			d[f] = 0;
		} else if (Group_has_neighbor(group, f)) {
			if (pos->owner[f] == NONE) {
				d[f] = 1;
				Queue_push(&q, f);
			}
		}
	}

	//shuffle array q.arr
	Int c = q.end;
	Int* a = q.arr;
	while (c > 1) {
		Int r = rand() % c;
		Int t = a[r];
		a[r] = a[c - 1];
		a[c - 1] = t;
		--c;
	}

	*dmin = OO;
	while (!Queue_is_empty(&q)) {
		Int t = Queue_pop(&q);

		Int* n;
		for (n = neighbors[t]; *n != END; ++n) {
			if (pos->owner[*n] == NONE) {
				if (d[*n] > d[t] + 1) {
					d[*n] = d[t] + 1;
					Queue_push(&q, *n);
					prev[*n] = t;
				}
			} else if (pos->owner[*n] == group->owner) {
				if (!Group_has_member(group, *n)) {
					//here we reach one of the nearest group
					*dmin = d[t];

					Int o = t;
					while (prev[o] != -1) {
						o = prev[o];
					}

					return o;
				}
			}
		}
	}

	return -1;
}

Move Group_get_random_move(Group* group, Position* pos) {
	Move move = INVALID_MOVE;
	Int dmin;
	Int to = Group_get_random_to(group, pos, &dmin);
	pos->last_random_move_dmin = dmin;
	if (to != -1) {
		Int c = 0;
		Int froms[NXN];
		Int froms_len = Group_find_possible_froms(group, pos, froms);
		MoveList moves;
		Int i;
		for (i = 0; i < froms_len; ++i) {
			Int from = froms[i];
			//check here if:
			// 1 - "to" point is neighbor to another point than from or
			// 2 - group is a unit group
			if ((group->count == 1) || (group->neighbors[to] > 1) || (!are_neighbors[from][to])) {
				Move move = MAKE_MOVE(from, to);
				moves[c++] = move;
			}
		}
		if (c > 0) {
			Int r = rand() % c;
			move = moves[r];
		}
	}
	return move;
}

Int Group_get_dmin(Group* group, Position* pos) {
	Queue q;
	Queue_init(&q);

	Bool marked[NXN];
	memset(marked, FALSE, NXN);

	Int d[NXN];
	Int f;
	for (f = 0; f < NXN; ++f) {
		if (Group_has_member(group, f)) {
			d[f] = 0;
			marked[f] = TRUE;
		} else if (Group_has_neighbor(group, f)) {
			if (pos->owner[f] == NONE) {
				d[f] = 1;
				Queue_push(&q, f);
			}
		} else {
			d[f] = OO;
		}
	}

	Int dmin = OO;
	while (!Queue_is_empty(&q) && (dmin == OO)) {
		Int t = Queue_pop(&q);
		Int* n;
		for (n = neighbors[t]; *n != END; ++n) {
			if (pos->owner[*n] == NONE) {
				if (d[*n] > d[t] + 1) {
					d[*n] = d[t] + 1;
					Queue_push(&q, *n);
				}
			} else if (pos->owner[*n] == group->owner) {
				if (!marked[*n]) {
					dmin = d[t];
					break;
				}
			}
		}
	}

	return dmin;
}
