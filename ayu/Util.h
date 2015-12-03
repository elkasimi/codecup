#ifndef __UTIL_H__
#define __UTIL_H__

Int Util_fprflush(FILE* stream, const char *fmt, ...);
void Util_init_random_seed();
void Util_display_first_error();
void Util_shuffle_moves(MoveList moves, Int count);
Int Util_get_distance_to_center(Int f);
Int Util_get_outside_inside_delta(Int from, Int to);
Bool Util_is_outside_inside_move(Int from, Int to);
Bool Util_is_edge(Int f);

#endif
