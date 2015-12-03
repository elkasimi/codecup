#include "Common.h"

#include "AI.h"
#include "Position.h"

Move AI_Random_get_best_move(Position* pos) {
	Move random_move = Position_get_random_move(pos);
	return random_move;
}
