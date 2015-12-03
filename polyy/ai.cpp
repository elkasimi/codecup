double AI::_total_time = 0.0;
int AI::_simulations = 0;

static struct {
    struct {
        Move white;
        Move black;
    } last_good_reply[N + 1];

    struct {
        struct {
            int wins;
            int visits;
        } white, black;
    } move_stats[N + 1];
} HISTORY;

void AI::_init_history() {
    for(int i = 0; i <= N; ++i) {
        HISTORY.last_good_reply[i].white = UNKNOWN_MOVE;
        HISTORY.last_good_reply[i].black = UNKNOWN_MOVE;
        HISTORY.move_stats[i].white.wins = 1;
        HISTORY.move_stats[i].white.visits = 2;
        HISTORY.move_stats[i].black.wins = 1;
        HISTORY.move_stats[i].black.visits = 2;
    }
}

void AI::_update_history(Move last_move, Move move, Player player, Player winner) {
    int i = (int) last_move;
    if(player == WHITE) {
        if(winner == WHITE) {
            HISTORY.last_good_reply[i].white = move;
            HISTORY.move_stats[i].white.wins += 1;
        } else if(HISTORY.last_good_reply[i].white == move) {
            HISTORY.last_good_reply[i].white = UNKNOWN_MOVE;
        }
        HISTORY.move_stats[i].white.visits += 1;
    } else {
        if(winner == BLACK) {
            HISTORY.last_good_reply[i].black = move;
            HISTORY.move_stats[i].black.wins += 1;
        } else if(HISTORY.last_good_reply[i].black == move) {
            HISTORY.last_good_reply[i].black = UNKNOWN_MOVE;
        }
        HISTORY.move_stats[i].black.visits += 1;
    }
}

Move AI::_get_killer_move(const Position& pos) {
    int i = (int) pos.get_last_move();
    Move killer = UNKNOWN_MOVE;
    if(pos.get_player() == WHITE) {
        killer = HISTORY.last_good_reply[i].white;
    } else {
        killer = HISTORY.last_good_reply[i].black;
    }
    if(killer == UNKNOWN_MOVE) {
        killer = pos.get_random_move();
    } else if((killer == SWAP_MOVE) and (pos.get_moves() != 1)) {
        killer = pos.get_random_move();
    } else {
        int ki = (int) killer;
        if(pos.get_field(ki) != NONE) {
            killer = pos.get_random_move();
        }
    }
    return killer;
}

Move AI::_get_default_policy_move(const Position& pos, const Tree* white_GIBBS_tree, const Tree* black_GIBBS_tree) {
    Move default_policy_move = UNKNOWN_MOVE;
	
	Move defending_moves[3];
	int count = pos.get_defending_moves(defending_moves);
	if(count > 0) {
		int idx = rand() % count;
		default_policy_move = defending_moves[idx];
	}
	/*	
	if(default_policy_move == UNKNOWN_MOVE) {
		if(pos.get_player() == WHITE) {
			if(white_GIBBS_tree != NULL) {
				default_policy_move = white_GIBBS_tree->get_GIBBS_move(pos);
			}
		} else {
			if(black_GIBBS_tree != NULL) {
				default_policy_move = black_GIBBS_tree->get_GIBBS_move(pos);
			}
		}
	}
	*/
	if(default_policy_move == UNKNOWN_MOVE) {
		default_policy_move = _get_killer_move(pos);
	}

	if(default_policy_move == UNKNOWN_MOVE) {
		default_policy_move = pos.get_random_move();
		//default_policy_move = pos.get_random_move_biased();
	}
	
    return default_policy_move;
}

Move AI::_get_best_move_mcrave(const Position& pos) {
    //to store variations information
    Move tree_policy_variation[N + 1];
    Move default_policy_variation[N + 1];
    int tree_policy_count, default_policy_count;
    clock_t start_clock, end_clock;
    ///////////////////////////////////////////////////////////////////////////
    //start profiler
    start_clock = clock();
    ///////////////////////////////////////////////////////////////////////////
    //clear already allocated trees
    Tree::clear_allocated_trees();
    //init history
    _init_history();
    //init the root tree
    Tree* root_tree = Tree::create(0, UNKNOWN_MOVE, NULL, pos);
	int i;
    for (i = 1; i <= MAX_ITERATIONS; ++i) {
        // if (i % 1000 == 0) {
        // cerr << "iter = " << i << endl;
        // }
        Tree* tree = root_tree;
        Position tmp = pos;
        tree_policy_count = 0;
		
		//these trees are for GIBBS sampling moves
		Tree* white_GIBBS_tree = NULL;
		Tree* black_GIBBS_tree = NULL;
		Tree* first_tree_selected = NULL;
		
        //selection
        while (tree->is_fully_expanded() and !tree->is_leaf()) {
			//update white_GIBBS_tree and black_GIBBS_tree
			/*
			if(tree->get_MC_visits() >= 50) {
				if(tree->get_player() == WHITE) {
					black_GIBBS_tree = tree;
				} else {
					white_GIBBS_tree = tree;
				}
			}
			*/

            tree = tree->select();
            tmp.do_move(tree->get_move());
            tree_policy_variation[tree_policy_count++] = tree->get_move();
			if(first_tree_selected == NULL) {
				first_tree_selected = tree;
			}
        }
        //expansion
        if (!tree->is_fully_expanded()) {
            tree = tree->expand(tmp);
            tree_policy_variation[tree_policy_count++] = tree->get_move();
        }
        default_policy_count = 0;
        //default policy play
        while (!tmp.end_game()) {
            //Move random_move = tmp.get_default_policy_move();
            Move random_move = _get_default_policy_move(tmp, white_GIBBS_tree, black_GIBBS_tree);
            tmp.do_move(random_move);
            default_policy_variation[default_policy_count++] = random_move;
        }
        Player winner = tmp.get_winner();
        int horizon = tmp.get_moves();
		
        //update history now with simulation result
        Move last_move = tree_policy_variation[0];
        for(int k = 1; k < tree_policy_count; ++k) {
            Player player = pos.get_player();
            if(k % 2 == 1) {
                player = 1 - player;
            }
            Move move = tree_policy_variation[k];
            _update_history(last_move, move, player, winner);
            last_move = move;
        }
        for(int k = 0; k < default_policy_count; ++k) {
            Player player = pos.get_player();
            if((k + tree_policy_count) % 2 == 1) {
                player = 1 - player;
            }
            Move move = default_policy_variation[k];
            _update_history(last_move, move, player, winner);
            last_move = move;
        }
        //back propagate
        while (tree != NULL) {
            //Monte Carlo update
            tree->MC_update(winner, horizon);
            //RAVE update
            //first with tree policy
            for (int k = tree->get_level() - 1; k < tree_policy_count; ++k) {
                Player player = pos.get_player();
                if (k % 2 == 1) {
                    player = 1 - player;
                }
                tree->RAVE_update(tree_policy_variation[k], player, winner, k);
            }
            //second with the default policy
            for (int k = 0; k < default_policy_count; ++k) {
                Player player = pos.get_player();
                if ((tree_policy_count + k) % 2 == 1) {
                    player = 1 - player;
                }
                tree->RAVE_update(default_policy_variation[k], player, winner, tree_policy_count + k);
            }
            //go to previous tree
            tree = tree->get_parent();
        }
		
		//test if the first_tree_selected is not largely selected
		//normaly the move with largest visits will be choosen so
		//if one child have more than half of the visits sure it
		//will be choosen at the end so we can stop search here
		//without any loss of efficiency of the player
		if(first_tree_selected != NULL) {
			if(first_tree_selected->get_MC_visits() >= MAX_VISITS) {
				cerr << "break at iteration = " << i << ", max visits reached!" << endl;
				break;
			}
		}
    }
    _simulations += i < MAX_ITERATIONS ? i : MAX_ITERATIONS;

    end_clock = clock();
    double dt = 1.0 * (end_clock - start_clock) / CLOCKS_PER_SEC;
    _total_time += dt;
#ifdef DEBUGGING
    for(int i = 0; i <= N; ++i) {
        Tree* child = root_tree->get_child(i);
        if(child != NULL) {
            child->display_stats();
        }
    }
#endif
    Tree* best_child = root_tree->select_most_visited_child();
    best_child->display_stats();
    cerr << "dt = " << dt << ", tt = " << _total_time << endl;
    //output expected variation
    Tree* tree = best_child;
    cerr << tree->get_move();
    while (tree->is_fully_expanded() and !tree->is_leaf()) {
        tree = tree->select();
        cerr << "->" << tree->get_move();
    }
    cerr << endl;

    return best_child->get_move();
}

Move AI::get_best_move(const Position& pos) {
    if (pos.end_game()) {
        cerr << "--> This position is a final state!" << endl;
        cerr << "--> Winner is " << (pos.get_winner() == WHITE ? "white" : "black") << endl;
        exit(-1);
    }
    
    Move best_move = UNKNOWN_MOVE;

    //if this is the first white move play a bad place!
	if(pos.get_moves() == 0) {
	    int bad_places[] = {5, 9, 17, 25, 62, 72, 83, 91, 102, 104};
	    int idx = rand() % 10;
	    best_move = (Move) bad_places[idx];
	    cerr << "using a bad place move!" << endl;
	}

	//first try if there is a winning move
	if(best_move == UNKNOWN_MOVE) {
        best_move = pos.get_winning_move();
        if(best_move != UNKNOWN_MOVE) {
            cerr << "using a winning move!" << endl;
        }
    }
 
    //second try finding if there is uniq defending move    
	if(best_move == UNKNOWN_MOVE) {
		int defending_moves[3];
		int count = pos.get_defending_moves_without_edges(defending_moves);
		if(count == 1) {
			best_move = defending_moves[0];
			cerr << "using a defending move!" << endl;
		}
	}
	//else search for the best move using Monte Carlo Tree Search(MCTS)
	if(best_move == UNKNOWN_MOVE) {
		if(_simulations < PHASE_1_LIMIT) {
			MAX_ITERATIONS = PHASE_1_ITERATIONS;
		} else if(_simulations < PHASE_2_LIMIT) {
			MAX_ITERATIONS = PHASE_2_ITERATIONS;
		} else if(_simulations < PHASE_3_LIMIT) {
			MAX_ITERATIONS = PHASE_3_ITERATIONS;
		} else {
			MAX_ITERATIONS = PHASE_4_ITERATIONS;
		}
		MAX_VISITS = (MAX_ITERATIONS / 2) + 50;
		cerr << "max iter = " << MAX_ITERATIONS << endl;
		best_move = _get_best_move_mcrave(pos);
	}

    return best_move;
}
