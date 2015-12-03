#include "Common.h"

#include "Util.h"
#include "Group.h"
#include "Position.h"

Int Util_fprflush(FILE *stream, const char *fmt, ...) {
	Int r;
	va_list ap;
	va_start(ap, fmt);
	r = vfprintf(stream, fmt, ap);
	va_end(ap);
	fflush(stream);
	return r;
}

void Util_init_random_seed() {
	unsigned long seed = (UInt)time(NULL);
	srand(seed);
}

void Util_display_first_error() {
	Util_fprflush(stderr, "R Mamay\n");
}

void Util_shuffle_moves(MoveList moves, Int count) {
	Int c = count;
	while (c > 0) {
		Int r = rand() % c;
		Move t = moves[r];
		moves[r] = moves[c - 1];
		moves[c - 1] = t;
		--c;
	}
}

Int Util_get_distance_to_center(Int f) {
	Int x = f % N;
	Int y = f / N;
	Int xc = N / 2;
	Int yc = N / 2;
	Int dx = x > xc ? (x - xc) : (xc - x);
	Int dy = y > yc ? (y - yc) : (yc - y);
	Int d = dx + dy;
	return d;
}

Int Util_get_outside_inside_delta(Int from, Int to) {
	Int from_x = from % N;
	Int from_y = from / N;
	Int to_x = to % N;
	Int to_y = to / N;
	Int xc = N / 2;
	Int yc = N / 2;
	Int from_dx = from_x > xc ? (from_x - xc) : (xc - from_x);
	Int from_dy = from_y > yc ? (from_y - yc) : (yc - from_y);
	Int to_dx = to_x > xc ? (to_x - xc) : (xc - to_x);
	Int to_dy = to_y > yc ? (to_y - yc) : (yc - to_y);
	Int d;
	if (from_dx < from_dy) {
		d = from_dy - to_dy;
	} else if (from_dx > from_dy) {
		d = from_dx - to_dx;
	} else {
		Int d1 = from_dy - to_dy;
		Int d2 = from_dx - to_dx;
		d = d1 > d2 ? d1 : d2;
	}
	
	return d;
}

Bool Util_is_outside_inside_move(Int from, Int to) {
	Int from_x = from % N;
	Int from_y = from / N;
	Int to_x = to % N;
	Int to_y = to / N;
	Int xc = N / 2;
	Int yc = N / 2;
	Int from_dx = from_x > xc ? (from_x - xc) : (xc - from_x);
	Int from_dy = from_y > yc ? (from_y - yc) : (yc - from_y);
	Int to_dx = to_x > xc ? (to_x - xc) : (xc - to_x);
	Int to_dy = to_y > yc ? (to_y - yc) : (yc - to_y);
	if (from_dx < from_dy) {
		return (to_dy < from_dy);
	} else if (from_dx > from_dy) {
		return (to_dx < from_dx);
	} else {
		return (to_dy < from_dy) || (to_dx < from_dx);
	}
}

Bool Util_is_edge(Int f) {
	Int x = f % N;
	Int y = f / N;
	return (x == 0) || (x == N - 1) || (y == 0) || (y == N - 1);
}