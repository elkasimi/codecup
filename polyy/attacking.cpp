#include "position.h"

Move Position::get_random_attacking_move() const {
    //search if there is a weak connection to the last move played
    Move move = UNKNOWN_MOVE;
    Move moves[10];
    int count = 0;
    int m = (int) _last_move;
    Player opp = 1 - _player;
    for(int* w = weak[m]; *w != 0; w += 2) {
        int w0 = *w;
        int w1 = *(w + 1);
        if((_fields[w0] == opp) and (_fields[w1] == NONE)) {
            moves[count++] = (Move)w1;
        }
    }

    //another is with joint move but one neighbour is occuped
    for(int* j = joint[m]; *j != 0; j += 3) {
        int j0 = *j;
        int j1 = *(j + 1);
        int j2 = *(j + 2);
        if((j0 == -1) or _fields[j0] == opp) {
            if((_fields[j1] == _player) and (_fields[j2] == NONE)) {
                moves[count++] = (Move)j2;
            } else if((_fields[j1] == NONE) and (_fields[j2] == _player)) {
                moves[count++] = (Move)j1;
            }
        }
    }

    if(count > 0) {
        int idx = rand() % count;
        move = moves[idx];
    }

    return move;
}
