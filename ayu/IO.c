#include "Common.h"

#include "IO.h"
#include "Util.h"

Move IO_read_move(String s) {
	//log the move
	Util_fprflush(stderr, "%s\n", s);
	char cf, ct;
	Int nf, nt, r;
	UInt a, b, c, d, f, t;
	Move move;
	r = sscanf(s, "%c%d-%c%d", &cf, &nf, &ct, &nt);
	AYU_ASSERT(r == 4);
	a = cf - 'A';
	b = nf - 1;
	c = ct - 'A';
	d = nt - 1;
	f = N * b + a;
	t = N * d + c;
	move = MAKE_MOVE(f, t);
	return move;
}

void IO_print_move(FILE* out, Move m) {
	char cf, ct;
	UInt nf, nt, f, t;
	f = FROM(m);
	t = TO(m);
	cf = 'A' + (f % N);
	nf = 1 + (f / N);
	ct = 'A' + (t % N);
	nt = 1 + (t / N);
	Util_fprflush(out, "%c%d-%c%d", cf, nf, ct, nt);
}

void IO_println_move(FILE* out, Move m) {
	char cf, ct;
	UInt nf, nt, f, t;
	f = FROM(m);
	t = TO(m);
	cf = 'A' + (f % N);
	nf = 1 + (f / N);
	ct = 'A' + (t % N);
	nt = 1 + (t / N);
	Util_fprflush(out, "%c%d-%c%d\n", cf, nf, ct, nt);
}
