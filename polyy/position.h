#ifndef __POSITION__
#define __POSITION__


struct Data {
    bool neighbour;
    bool joint;
};

class Position {
public:
    Position();
    Position(const Position& pos);
    Position& operator=(const Position& pos);
    void do_move(Move move);
    Player get_winner() const {
        return _winner;
    }
    Player get_field(int i) const {
        return _fields[i];
    }
    Player get_player() const {
        return _player;
    }
    int get_moves() const {
        return _moves;
    }

    int get_white_corners() const {
        int c = 0;
        for(int i = 1; i <= 5; ++i) {
            if(_control[i] == WHITE) {
                ++c;
            }
        }
        return c;
    }

    int get_black_corners() const {
        int c = 0;
        for(int i = 1; i <= 5; ++i) {
            if(_control[i] == BLACK) {
                ++c;
            }
        }
        return c;
    }

    Move get_last_move() const {
        return _last_move;
    }

    bool end_game() const {
        return (_winner != NONE);
    }

    bool is_joint_move(int m) const {
        const Data* data = _player == WHITE ? _data_white : _data_black;
        return data[m].joint;
    }

    bool is_neighbour_move(int m) const {
        const Data* data = _player == WHITE ? _data_white : _data_black;
        return data[m].neighbour;
    }
	
    bool is_joint_opp_move(int m) const {
        const Data* data = _player != WHITE ? _data_white : _data_black;
        return data[m].joint;
    }

    bool is_neighbour_opp_move(int m) const {
        const Data* data = _player != WHITE ? _data_white : _data_black;
        return data[m].neighbour;
    }	
	
    bool is_joint_last_move(int m) const {
		bool joint_last_move = false;
		for(int* j = joint[_last_move]; *j != 0; j += 3) {
			if(*j == m) {
				joint_last_move = true;
				break;
			}
		}
		return joint_last_move;
    }

    bool is_neighbour_last_move(int m) const {
		bool neighbour_last_move = false;
		for(int* n = neighbours[_last_move]; *n != 0; ++n) {
			if(*n == m) {
				neighbour_last_move = true;
				break;
			}
		}
		return neighbour_last_move;
    }	
		
	bool is_defending_move(int move) const {
		if((_last_move != SWAP_MOVE) and (_last_move != UNKNOWN_MOVE)) {
			int m = (int) _last_move;
			for(int* a = attack[m]; *a != 0; a += 3) {
				int a0 = *a;
				int a1 = *(a + 1);
				int a2 = *(a + 2);
				if(((a0 == -1) or (_fields[a0] == _player))
					and ((a1 == -1) or (_fields[a1] == _player))
					and (_fields[a2] == NONE)
					and (move == a2)) {
					return true;
				}
			}
		}
		return false;
	}
	
	bool is_attacking_move(int move) const {
		if(_last_move == UNKNOWN_MOVE) {
			return false;
		}

		int m = (int) _last_move;
		Player opp = 1 - _player;
		for(int* w = weak[m]; *w != 0; w += 2) {
			int w0 = *w;
			int w1 = *(w + 1);
			if((_fields[w0] == opp) and (_fields[w1] == NONE) and (move == w1)) {
				return true;
			}
		}
		//////
		for(int* j = joint[m]; *j != 0; j += 3) {
			int j0 = *j;
			int j1 = *(j + 1);
			int j2 = *(j + 2);
			if((j0 == -1) or _fields[j0] == opp) {
				if((_fields[j1] == _player) and (_fields[j2] == NONE) and (move == j2)) {
					return true;
				} else if((_fields[j1] == NONE) and (_fields[j2] == _player) and (move == j1)) {
					return true;
				}
			}
		}		
		
		return false;
	}
	
	bool is_weakly_connected(int m) const {
	    bool weakly_connected = false;
	    for(int* w = weak[m]; *w != 0; w += 2) {
	        int w0 = *w;
	        int w1 = *(w+1);
	        if(_fields[w0] == _player and _fields[w1] == NONE) {
	            weakly_connected = true;
	            break;
	        }
	    }
	    return weakly_connected;
	}

    void get_result(int& white_corners, int& black_corners) {
        white_corners = 0;
        black_corners = 0;
        for(int i = 1; i <= 5; ++i) {
            if(_control[i] == WHITE) {
                ++white_corners;
            }
            if(_control[i] == BLACK) {
                ++black_corners;
            }
        }
    }
	
	//get the value & visits to give to move m in this position
	void get_HEURISTIC(int m, double& value, int& visits) const;

    Move get_random_move() const;
    Move get_random_attacking_move() const;
    Move get_winning_move() const;
    int get_defending_moves(Move defending_moves[3]) const;
	int get_defending_moves_without_edges(Move defending_moves[3]) const;
	Move get_random_move_biased() const;
	Move get_random_neighbour_move() const;
	Move get_random_joint_move() const;
	Move get_random_elsewhere_move() const;

private:
    void _swap() {
        int f = (int) _last_move;
        _fields[f] = BLACK;
        for(int i = 1; i <= N; ++i) {
            _data_black[i] = _data_white[i];
            _data_white[i].joint = false;
            _data_white[i].neighbour = false;
        }
    }

    void _toggle_player() {
        _player = 1 - _player;
    }

    void _update(int f);

    Player _player;
    Player _winner;
    int _moves;
    Move _last_move;
    Player _fields[N + 1];
    Player _control[6];
    Data _data_white[N + 1];
    Data _data_black[N + 1];
};

#endif
