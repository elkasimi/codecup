#ifndef __POSITION__
#define __POSITION__

#include "Group.h"

typedef struct Position {
	//player to move
	Player player;
	Player last_player;
	Player owner[NXN];
	Int moves;
	Int white_groups_count;
	Int white_groups_idx[MAX_PLAYER_GROUPS];
	Group white_groups[MAX_PLAYER_GROUPS];
	Int black_groups_count;
	Int black_groups_idx[MAX_PLAYER_GROUPS];
	Group black_groups[MAX_PLAYER_GROUPS];
	Move last_move;
	Bool critical;
	Int last_random_move_dmin;

#if USE_HASH_SET
	UInt hash;
	UInt lock;
#endif
} Position;

void Position_activate_critical_check();
void Position_deactivate_critical_check();
void Position_init(Position* pos);
void Position_copy(Position* dst_pos, Position* src_pos);
void Position_do_move(Position* pos, Move move);
Int Position_get_moves(Position* pos, MoveList moves);
Int Position_get_favorized_moves(Position* pos, MoveList moves);
void Position_display(Position* pos);
Move Position_get_random_move(Position* pos);
Real Position_get_heuristic_value(Position* pos, Move move);
Bool Position_is_valid_move(Position* pos, Move move);
Bool Position_is_separating_move(Position* pos, Move move);
Bool Position_is_critical(Position* pos);
Bool Position_player_can_move(Position* pos, Player player);
Move Position_get_random_saving_move(Position* pos);
void Position_get_diameters(Position* pos, Int* white_diameter_ptr, Int* black_diameter_ptr);

#endif
