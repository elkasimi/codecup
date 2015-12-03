Tree Tree::_allocated_trees[MAX_TREES];
int Tree::_allocated_trees_count = 0;

Tree* Tree::create(int level, Move move, Tree* parent, const Position& pos) {
	Tree* tree = &_allocated_trees[_allocated_trees_count++];
	tree->_move = move;
	tree->_parent = parent;
	//init the children's list
	for (int i = 0; i <= N; ++i) {
		tree->_children[i] = NULL;
	}
	//init MC
	tree->_MC.value = 0.0;
	tree->_MC.visits = 0;
	
	//init horizon value to the maximum horizon possible so simulations only
	//will decrease it, initializing it to zero is a bad idea!
	tree->_MC.horizon = N;

	//init RAVE stats
	tree->_RAVE.value = 0.0;
	tree->_RAVE.visits = 0;

	for (int i = 0; i <= N; ++i) {
		tree->_untried_moves[i] = false;
	}
	//if this position is not an ending position get all possible moves
	tree->_untried_moves_count = 0;
	if (!pos.end_game()) {
		tree->_is_leaf = false;
		//add the swap move if possible
		if (pos.get_moves() == 1) {
			tree->_untried_moves[0] = true;
			tree->_untried_moves_count += 1;
		}
		for (int i = 1; i <= N; ++i) {
			if (pos.get_field(i) == NONE) {
				tree->_untried_moves[i] = true;
				tree->_untried_moves_count += 1;
			}
		}
	} else {
		tree->_is_leaf = true;
	}
	tree->_player = 1 - pos.get_player();
	//init tree level
	tree->_level = level;

	return tree;
}

void Tree::clear_allocated_trees() {
	_allocated_trees_count = 0;
}

Tree* Tree::expand(Position& pos) {
	int count = 0;
	Move choices[N + 1];
	int best = -1;
	for (int i = 0; i <= N; ++i) {
		if (_untried_moves[i]) {
			int v = 0;
			if(pos.is_neighbour_move(i)) {
				++v;
			}
			if(pos.is_joint_move(i)) {
				++v;
			}

			if(best <= v) {
				best = v;
				if(best < v) {
					count = 0;
				}
				choices[count++] = (Move) i;
			}
		}
	}
	int idx = rand() % count;
	Move move = choices[idx];

	int visits;
	double value;
	pos.get_HEURISTIC(move, value, visits);

	pos.do_move(move);
	Tree* new_child = create(_level + 1, move, this, pos);

	new_child->_MC.value = value;
	new_child->_MC.visits = visits;

	new_child->_RAVE.value = value;
	new_child->_RAVE.visits = visits;

	//remove move from tree's untried moves list
	idx = (int) move;
	_untried_moves[idx] = false;

	//decrease untried moves count
	_untried_moves_count -= 1;

	//add the new child to the tree children list
	_children[idx] = new_child;

	return new_child;
}

double Tree::get_value() const {
	//double value = get_UCT_value();
	//double value = get_RAVE_value();
	//double value = get_MC_RAVE_value();
	return _value;
}

double Tree::get_MC_RAVE_value() const {
	double b = 5e-5;
	int m = _RAVE.visits;
	int n = _MC.visits;
    double beta = m;
    beta /= m + n + b * m * n;
	double value = (1 - beta) * _MC.value + beta * _RAVE.value /* + EXPLORATION_BONUS[n] */;

	return value;
}

double Tree::get_UCT_value() const {
	int Mi = _MC.visits;
	int M = _parent->_MC.visits;
	double value = _MC.value + UCTK * sqrt(log(M) / Mi);
	return value;
}

Tree* Tree::select() {
	Tree* best_child = NULL;
	double best_value = -OO;
	double best_horizon = 200;
	for(int i = 0; i <= N; ++i) {
		Tree* child = _children[i];
		if(child != NULL) {
			double value = child->get_value();
			if(best_value < value) {
				best_value = value;
				best_child = child;
				best_horizon = child->_MC.horizon;
			} else if((fabs(best_value - value) <= 0.001)) {
				if(value >= 0.5 and (best_horizon > child->_MC.horizon)) {
					best_value = value;
					best_child = child;
					best_horizon = child->_MC.horizon;
				} else if(value < 0.5 and (best_horizon < child->_MC.horizon)) {
					best_value = value;
					best_child = child;
					best_horizon = child->_MC.horizon;
				}
			}
		}
	}
	return best_child;
}

Tree* Tree::select_most_visited_child() {
	Tree* most_visited_child = NULL;
	int maxv = -1;
	for(int i = 0; i <= N; ++i) {
		Tree* child = _children[i];
		if(child != NULL) {
			if(maxv < child->_MC.visits) {
				maxv = child->_MC.visits;
				most_visited_child = child;
			}
		}
	}
	return most_visited_child;
}

Tree* Tree::select_random_child() {
	Tree* choices[N+1];
	int count = 0;
	for(int i = 0; i <= N; ++i) {
		Tree* child = _children[i];
		if(child != NULL) {
		    choices[count++] = child;
		}
	}
	int idx = rand() % count;
	Tree* selected = choices[idx];
	return selected;    
}

void Tree::MC_update(Player winner, int horizon) {
	int r = (_player == winner);

	_MC.value = _MC.value * _MC.visits + r;
	_MC.value /= _MC.visits + 1;

	_MC.horizon = _MC.horizon * _MC.visits + horizon;
	_MC.horizon /= _MC.visits + 1;

	_MC.visits += 1;
	_value = get_MC_RAVE_value();
}

void Tree::RAVE_update(Move move, Player player, Player winner, int i) {
	if (_player == player) {
		int r = (_player == winner);
		int idx = (int) move;
		if(_parent != NULL) {
			Tree* child = _parent->_children[idx];
			if(child != NULL) {
				child->_RAVE.value = child->_RAVE.value * child->_RAVE.visits + r;
				child->_RAVE.value /= child->_RAVE.visits + 1;
				child->_RAVE.visits += 1;
				child->_value = child->get_MC_RAVE_value();
			}
		}
	}
}

//get a gibbs sampling move
//which have a simple idea to choose the best moves with high probability
Move Tree::get_GIBBS_move(const Position& pos) const {
	double p[N];
	Move available_moves[N];
	int count = 0;
	if(pos.get_moves() == 1) {
		available_moves[count] = SWAP_MOVE;
		Tree* child = _children[0];
		p[count] = child->_RAVE.value;
		++count;
	}

	for(int i = 1; i <= N; ++i) {
		if(pos.get_field(i) == NONE) {
			Tree* child = _children[i];
			available_moves[count] = i;
			p[count] = child->_RAVE.value;
			if(count > 0) {
				p[count] += p[count-1];
			}
			++count;
		}
	}
	double r = rand();
	r /= RAND_MAX;
	r *= p[count-1];

	int m = 0;
	int M = count - 1;
	//binary search the move to player to the random number r
	//linear search is time consuming O(n) where this binary
	//search is O(log(n))
	while(m < M) {
		int a = (m + M) >> 1;
		if(r < p[a]) {
			M = a;
		} else {
			m = a + 1;
		}
	}

	return available_moves[M];
}

void Tree::display_stats() {
	double value = get_value();
	double h = _MC.horizon;
	cerr.setf(ios::fixed);
	cerr.precision(3);
	//display stats
	cerr << "m = " << _move <<
		", w = " << value <<
		", w1 = " << _MC.value <<
		", v1 = " << _MC.visits <<
		", w2 = " << _RAVE.value <<
		", v2 = " << _RAVE.visits <<
		", h = " << h << endl;
}
