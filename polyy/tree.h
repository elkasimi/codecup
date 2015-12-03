#ifndef __TREE__
#define __TREE__


class Tree {
public:
    static Tree* create(int level, Move move, Tree* parent, const Position& pos);
    static void clear_allocated_trees();
    bool is_fully_expanded() const {
        return (_untried_moves_count == 0);
    }
    bool is_leaf() const {
        return _is_leaf;
    }
    Tree* expand(Position& pos);
    Tree* select();
    Tree* select_most_visited_child();
    Tree* select_random_child();
    void display_stats();
    void MC_update(Player winner, int h);
    void RAVE_update(Move move, Player player, Player winner, int index);
    Move get_GIBBS_move(const Position& pos) const;

    double get_RAVE_value() const {
        return _RAVE.value;
    }
    int get_RAVE_visits() const {
        return _RAVE.visits;
    }
    Move get_move() const {
        return _move;
    }
    int get_level() const {
        return _level;
    }
    Tree* get_child(int i) const {
        return _children[i];
    }
    Tree* get_parent() const {
        return _parent;
    }
    int get_MC_visits() const {
        return _MC.visits;
    }
    double get_MC_value() const {
        return _MC.value;
    }
	Player get_player() const {
		return _player;
	}

	double get_value() const;
	double get_MC_RAVE_value() const;
	double get_UCT_value() const;

private:
    static Tree _allocated_trees[MAX_TREES];
    static int _allocated_trees_count;

    //the move that got us to this tree
    Move _move;

    //the parent tree NULL for root tree
    Tree* _parent;

    //tree children
    Tree* _children[N + 1];

    //Monte Carlo stats
    struct {
        double value;
        double horizon;
        int visits;
    } _MC;

    //RAVE stats
    struct {
        double value;
        int visits;
    } _RAVE;

    //untried moves
    bool _untried_moves[N + 1];

    //player just moved
    Player _player;

    //to know tree level
    int _level;

    //to know if tree is leaf or not
    bool _is_leaf;

    //to know how many moves are not tried
    int _untried_moves_count;
	
	double _value;
};

#endif

