#pragma once

#include "Player.h"

class Competition
{
public:
    using Interval = std::pair< double, double >;
    struct Result
    {
        int32_t fails;
        double mean_score;
        double min_score;
        double max_score;
        Interval confidence_interval;
    };

    Competition( const Player::Type first_player_type,
                 const Player::Type second_player_type,
                 const int32_t iterations,
                 const int32_t simultaneous );
    ~Competition( );

    Result run( );

private:
    Player::Type m_first_player_type;
    Player::Type m_second_player_type;
    int32_t m_iterations;
    int32_t m_simultaneous;
};
