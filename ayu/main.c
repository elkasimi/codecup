#include "Common.h"

#include "Position.h"
#include "IO.h"
#include "AI.h"
#include "Util.h"
#include "Tree.h"

int main(int argc, char* argv[]) {
	if (argc > 1) {
		//analyze mode
		Position pos;
		Position_init(&pos);
		Int i;
		for (i = 1; i < argc; ++i) {
			Move move = IO_read_move(argv[i]);
			Position_do_move(&pos, move);
		}
		Move best_move = AI_get_best_move(&pos);
		IO_println_move(stderr, best_move);
		Tree_destroy_root();
	} else {
		String s;
		Position pos;
		//display the first error that indicates it is a random player
		Util_display_first_error();
		//display some statistics
		Util_fprflush(stderr, "ST = %d\n", sizeof(Tree));
		Util_fprflush(stderr, "SP = %d\n", sizeof(Position));
		Util_fprflush(stderr, "SG = %d\n", sizeof(Group));
		//init random seed
		Util_init_random_seed();
		Position_init(&pos);
		READ_STRING(s);
		while (!EQUAL_STRING(s, "Quit")) {
			if (!EQUAL_STRING(s, "Start")) {
				Move opp_move = IO_read_move(s);
				Position_do_move(&pos, opp_move);
				Tree_update_root(opp_move);
			}
			Move my_move = AI_get_best_move(&pos);
			Position_do_move(&pos, my_move);
			Tree_update_root(my_move);
			IO_println_move(stderr, my_move);
			IO_println_move(stdout, my_move);
			READ_STRING(s);
		}
		Tree_destroy_root();
	}
	return 0;
}
