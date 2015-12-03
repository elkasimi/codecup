#include "Common.h"

#include "AI.h"
#include "OpeningBook.h"
#include "Timer.h"

extern Move AI_MCTS_get_best_move(Position* pos, Int max_iterations, Int max_time);

extern Move AI_DFS_get_best_move(Position* pos);

Move AI_get_best_move(Position* pos) {
	Move best_move = INVALID_MOVE;

	//first search in the opening book
	best_move = OpeningBook_get_best_move(pos);

	//else use MCTS-UCT algorithm
	if (best_move == INVALID_MOVE) {
		Int max_time = Timer_get_max_time_for_move(pos);
		Int max_iterations = MAX_ITERATIONS;
		best_move = AI_MCTS_get_best_move(pos, max_iterations, max_time);
	}

	AYU_ASSERT(best_move != INVALID_MOVE);

	return best_move;
}
