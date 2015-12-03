Position::Position() {
    _player = WHITE;
    _winner = NONE;
    _last_move = UNKNOWN_MOVE;
    _moves = 0;
    _control[0] = NONE;
    _control[1] = NONE;
    _control[2] = NONE;
    _control[3] = NONE;
    _control[4] = NONE;
    _control[5] = NONE;
    memset(_fields, NONE, (N + 1) * sizeof(Player));
    memset(_data_white, false, (N + 1) * sizeof(Data));
    memset(_data_black, false, (N + 1) * sizeof(Data));
}

Position::Position(const Position& pos) {
    _player = pos._player;
    _winner = pos._winner;
    _last_move = pos._last_move;
    _moves = pos._moves;
    _control[0] = pos._control[0];
    _control[1] = pos._control[1];
    _control[2] = pos._control[2];
    _control[3] = pos._control[3];
    _control[4] = pos._control[4];
    _control[5] = pos._control[5];
    memcpy(_fields, pos._fields, (N + 1) * sizeof(Player));
    memcpy(_data_white, pos._data_white, (N + 1) * sizeof(Data));
    memcpy(_data_black, pos._data_black, (N + 1) * sizeof(Data));
}

Position& Position::operator=(const Position& pos) {
    _player = pos._player;
    _winner = pos._winner;
    _last_move = pos._last_move;
    _moves = pos._moves;
    _control[0] = pos._control[0];
    _control[1] = pos._control[1];
    _control[2] = pos._control[2];
    _control[3] = pos._control[3];
    _control[4] = pos._control[4];
    _control[5] = pos._control[5];
    memcpy(_fields, pos._fields, (N + 1) * sizeof(Player));
    memcpy(_data_white, pos._data_white, (N + 1) * sizeof(Data));
    memcpy(_data_black, pos._data_black, (N + 1) * sizeof(Data));
    return *this;
}

void Position::do_move(Move move) {
    if(move == SWAP_MOVE) {
        _swap();
    } else {
        int f = (int) move;
        _fields[f] = _player;
        //update winner & player's data
        _update(f);
		_last_move = move;
    }
    _toggle_player();
    _moves++;
    
}

Move Position::get_winning_move() const {
    //normaly a win can occur only after 24 moves
    //at least
    if(_moves >= 24) {
        for(int i = 1; i <= N; ++i) {
            if((_fields[i] == NONE) and (is_neighbour_move(i))) {
                Position tmp = *this;
                tmp.do_move(i);
                if(tmp.end_game()) {
                    return ((Move)i);
                }
            }
        }
    }
    return UNKNOWN_MOVE;
}

Move Position::get_random_move_biased() const {
	double pn, pj;
	if(_moves < 10) {
		pn = 0.20;
		pj = 0.40;
	} else if(_moves < 30) {
		pn = 0.50;
		pj = 0.40;
	} else if(_moves < 60) {
		pn = 0.47;
		pj = 0.47;
	} else {
		pn = 0.50;
		pj = 0.50;
	}
	
	double r = rand();
	r /= RAND_MAX;
	
	Move move = UNKNOWN_MOVE;
	
	if(r < pn) {
		move = get_random_neighbour_move();
	} else if(r < pn + pj) {
		move = get_random_joint_move();
	} else {
		move = get_random_elsewhere_move();
	}
	if(move == UNKNOWN_MOVE) {
		move = get_random_move();
	}
	
	return move;
}
