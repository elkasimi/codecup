#ifndef __AI__
#define __AI__


class AI {
public:
    //function to search the best move in a given position
	static Move get_best_move(const Position& pos);

private:
    //function to search the best move in a given position
    //using the Monte Carlo algorithm with RAVE biasing
	static Move _get_best_move_mcrave(const Position& pos);
	
	//init the history of simulations
	static void _init_history();
	
	//update the state of a move according to the simulation winner
	static void _update_history(Move last_move, Move move, Player player, Player winner);
	
	//get the last winning move saved for the given position according
	//to the last move
	static Move _get_killer_move(const Position& pos);
	
	//get the default policy move according to some rules
	//see this function implementation for more details
	static Move _get_default_policy_move(const Position& pos, const Tree* white_GIBBS_tree, const Tree* black_GIBBS_tree);

	static double _total_time;
	static int _simulations;
};

#endif
