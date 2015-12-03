#include "Common.h"

#include "Position.h"
#include "OpeningBook.h"

extern Move AI_LightWeight_get_best_move(Position* pos);

void generate_opening_moves(Position* pos, Int index, Int count) {
	if (index == count) {
		MoveList moves;
		Int c = Position_get_favorized_moves(pos, moves);

		Move best_move = INVALID_MOVE;
		Real best_value = -OO;
		
		Int i;
		for (i = 0; i < c; ++i) {
			Move move = moves[i];
			Position next;
			Position_copy(&next, pos);
			Position_do_move(&next, move);

			Int j;
			Real value = 0.0;
			Int S = 2000;
			for (j = 0; j < S; ++j) {
				Position tmp;
				Position_copy(&tmp, &next);
				Move move;
				Int h = 0;
				for (move = AI_LightWeight_get_best_move(&tmp); move != INVALID_MOVE; move = AI_LightWeight_get_best_move(&tmp)) {
					++h;
					Position_do_move(&tmp, move);
				}
				
				value += (next.player != tmp.player) ? (1.0 - 0.001 * h) : (0.001 * h);
			}
			value /= S;
			
			if (best_value < value) {
				best_value = value;
				best_move = move;
			}

			Real a = 100 * i;
			a /= c;
			fprintf(stderr, "\b\b\b");
			fprintf(stderr, "%.0f%%", a);
		}
		fprintf(stderr, "\b\b\b");
		fprintf(stdout, "{0x%08x, 0x%08x, 0x%04x, %.2f},\n", pos->hash, pos->lock, best_move, best_value);
		fflush(stdout);
	} else {
		if ((index + count) % 2 == 0) {
			Move move = OpeningBook_get_best_move(pos);
			Position next;
			Position_copy(&next, pos);
			Position_do_move(&next, move);
			generate_opening_moves(&next, index + 1, count);
		} else {
			MoveList moves;
			Int c = Position_get_moves(pos, moves);
			Int i;
			for (i = 0; i < c; ++i) {
				Move move = moves[i];
				Position next;
				Position_copy(&next, pos);
				Position_do_move(&next, move);
				generate_opening_moves(&next, index + 1, count);
			}
		}
	}
}