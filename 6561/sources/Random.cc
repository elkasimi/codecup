#include "Common.h"

#include "Board.h"
#include "Player.h"

Random::Random( )
{
}

Random::~Random( )
{
}

Move
Random::get_best_move( const Board& board )
{
    return board.get_random_move( );
}
