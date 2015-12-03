#include "position.h"

void Position::get_HEURISTIC(int m, double& value, int& visits) const {
	//biasing toward swap move
	if(m == SWAP_MOVE) {
		value = 1.0;
		visits = 100;
	}
	//biasing toward defending moves
	else if(is_defending_move(m)) {
	    value = 1.0;
	    visits = 100;
	}
	//biasing toward neighbour moves
	else if(is_neighbour_move(m)) {
	    if(_moves < OPENING_MOVES) {
	        value = 0.8;
	        visits = 50;
	    } else {
	        value = 1.0;
	        visits = 50;
	    }
	}
	//biasing toward joint moves
	else if(is_joint_move(m)) {
        value = 1.0;
        visits = 50;
	}
	//biasing toward weekly connected moves
	/* else if(is_weakly_connected(m)) {
		value = 0.6;
		visits = 40;
	}

	//biasing toward neighbour last move
	else if(is_neighbour_last_move(m)) {
		value = 0.6;
		visits = 40;
	}
	//biasing toward joint last move
	else if(is_joint_last_move(m)) {
		value = 0.6;
		visits = 40;
	}*/
	//biasing toward elsewhere moves as are bad in general
	else {
        value = 0.2;
        visits = 50;
	}

	//biasing to edges distance
	/*
	int q[N], start, end, d[N+1], mask;
	for(int i = 0; i <= N; ++i) d[i] = OO;
	start = end = 0;
	q[end++] = m;
	d[m] = 0;
	mask = field_mask[m];
	while(start != end) {
		int t = q[start++];
		for(int* n = neighbours[t]; *n != 0; ++n) {
			if(_fields[*n] == _player and d[*n] != 0) {
				d[*n] = 0;
				q[end++] = *n;
				mask |= field_mask[*n];
			}
		}

		for(int* j = joint[t]; *j != 0; j += 3) {
			int j0 = *j;
			int j1 = *(j+1);
			int j2 = *(j+2);
			if(_fields[j1] == NONE and _fields[j2] == NONE) {
				if(j0 == -1) {
					mask |= field_mask[j1] & field_mask[j2];
				} else if(_fields[j0] == _player and d[j0] != 0){
					d[j0] = 0;
					q[end++] = j0;
					mask |= field_mask[j0];
				}
			}
		}
	}
	start = 0;
	while(start != end) {
		int t = q[start++];
		for(int* n = neighbours[t]; *n != 0; ++n) {
			if(_fields[*n] == NONE and d[*n] > d[t] + 1) {
				d[*n] = d[t] + 1;
				q[end++] = *n;
			}
		}
	}

	int edge_distance[6];
	for(int i = 1; i <= 5; ++i) edge_distance[i] = OO;
	for(int i = 1; i <= 5; ++i) {
		for(int* s = sides[i]; *s != 0; ++s) {
			if(edge_distance[i] > d[*s]) {
				edge_distance[i] = d[*s];
			}
		}
	}

	int V = 20;
    if((_control[1] == NONE) and ((mask & MASK_CORNER_1) == MASK_CORNER_1) and (mask != MASK_CORNER_1)) {
        value = V + visits*value;
		value /= V + visits;
		visits += V;
    }
    if((_control[2] == NONE) and ((mask & MASK_CORNER_2) == MASK_CORNER_2) and (mask != MASK_CORNER_2)) {
        value = V + visits*value;
		value /= V + visits;
		visits += V;
    }
    if((_control[3] == NONE) and ((mask & MASK_CORNER_3) == MASK_CORNER_3) and (mask != MASK_CORNER_3)) {
        value = V + visits*value;
		value /= V + visits;
		visits += V;
    }
    if((_control[4] == NONE) and ((mask & MASK_CORNER_4) == MASK_CORNER_4) and (mask != MASK_CORNER_4)) {
        value = V + visits*value;
		value /= V + visits;
		visits += V;
    }
    if((_control[5] == NONE) and ((mask & MASK_CORNER_5) == MASK_CORNER_5) and (mask != MASK_CORNER_5)) {
        value = V + visits*value;
		value /= V + visits;
		visits += V;
    }
    */
}
