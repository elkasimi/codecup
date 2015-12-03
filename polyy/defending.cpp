#include "position.h"

int Position::get_defending_moves(Move defending_moves[3]) const {
    int count = 0;
    if((_last_move != SWAP_MOVE) and (_last_move != UNKNOWN_MOVE)) {
        int m = (int) _last_move;
        for(int* a = attack[m]; *a != 0; a += 3) {
            int a0 = *a;
            int a1 = *(a + 1);
            int a2 = *(a + 2);
            if(((a0 == -1) or (_fields[a0] == _player))
				and ((a1 == -1) or (_fields[a1] == _player))
				and (_fields[a2] == NONE)) {
                defending_moves[count++] = (Move)a2;
            }
        }
    }
	return count;
}

int Position::get_defending_moves_without_edges(Move defending_moves[3]) const {
    int count = 0;
    if((_last_move != SWAP_MOVE) and (_last_move != UNKNOWN_MOVE)) {
        int m = (int) _last_move;
        for(int* a = attack[m]; *a != 0; a += 3) {
            int a0 = *a;
            int a1 = *(a + 1);
            int a2 = *(a + 2);
            if(((a0 != -1) and (_fields[a0] == _player))
				and ((a1 != -1) and (_fields[a1] == _player))
				and (_fields[a2] == NONE)) {
                defending_moves[count++] = (Move)a2;
            }
        }
    }
	return count;
}
