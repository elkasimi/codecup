void display_first_error() {
    cerr << "R player" << endl;
    cerr << "sizeof tree " << sizeof(Tree) << endl;
    cerr << "sizeof position " << sizeof(Position) << endl;
}

void init_rand_seed() {
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);
}

void init() {
	init_rand_seed();
	
	for(int i = 1; i < MAX_TREES; ++i) {
		EXPLORATION_BONUS[i] = UCTK / sqrt((double)i);
		//EXPLORATION_BONUS[i] = 0.0;
	}
}

Move read_move(const string& s) {
    istringstream iss(s);
    int i;
    iss >> i;
    cerr << i << endl;
    if(i == -1) {
        i = 0;
    }
    Move move = (Move)i;
    return move;
}

void display_move(Move move) {
    int i;
    if(move == SWAP_MOVE) {
        i = -1;
    } else {
        i = (int) move;
    }
    cout << i << endl;
    cerr << i << endl;
}

int main(int argc, char** argv) {
    if(argc > 1) {
		init();
		Position pos;
		for (int i = 2; i < argc; ++i) {
			Move move = read_move(argv[i]);
			pos.do_move(move);
		}
		Move best_move = AI::get_best_move(pos);
		display_move(best_move);
    } else {
        Position pos;
        display_first_error();
        init();
        string s;
        cin >> s;
        while(s != "Quit") {
            if(s != "Start") {
                Move opp_move = read_move(s);
                pos.do_move(opp_move);
            }
            Move my_move = AI::get_best_move(pos);
            pos.do_move(my_move);
            display_move(my_move);
            cin >> s;
        }
    }
    return 0;
}
