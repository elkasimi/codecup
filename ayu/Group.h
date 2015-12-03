#ifndef __GROUP_H__
#define __GROUP_H__

typedef struct Group {
	Player owner;
	Int count;
	Bool has_member[NXN];
	Int neighbors[NXN];
	Int froms_count;
	Int froms[NXN];
	Bool need_check;
	Int members[MAX_GROUP_MEMBERS];
	Bool favorized;
} Group;

typedef Group GroupList[MAX_GROUPS];

void Group_init(Group* group, Player owner);
void Group_copy(Group* dst_group, Group* src_group);
void Group_favorize(Group* group);
void Group_add(Group* group, Int m);
void Group_remove(Group* group, Int m);
Bool Group_has_member(Group* group, Int m);
Bool Group_has_neighbor(Group* group, Int n);
void Group_merge_with(Group* group, Group* other_group);
Move Group_get_random_move(Group* group, Position* pos);
Int Group_get_possible_moves(Group* group, Position* pos, MoveList moves, Int* dmin);
Int Group_get_edge_moves(Group* group, Position* pos, MoveList moves);
Int Group_get_dmin(Group* group, Position* pos);

#endif
