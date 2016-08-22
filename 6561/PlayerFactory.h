#pragma once

#include "Player.h"

class PlayerFactory
{
public:
    static std::unique_ptr< Player > create( Player::Type player_type );
};
