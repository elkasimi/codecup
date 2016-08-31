#include "Common.h"

#include "Configuration.h"
#include "PlayerFactory.h"

std::unique_ptr< Player >
PlayerFactory::create( Player::Type player_type )
{
    std::unique_ptr< Player > player;

    switch ( player_type )
    {
    case Player::Type::RANDOM:
        player = std::make_unique< Random >( );
        break;

    case Player::Type::HUMAN:
        player = std::make_unique< Human >( );
        break;

    case Player::Type::EXPECT_MAX:
        player = std::make_unique< ExpectMax >(
            Configuration::get_best_configuration( ) );
        break;

    case Player::Type::EXPECT_MAX_LIGHTWEIGHT:
        player = std::make_unique< ExpectMax >(
            Configuration::get_lightweight_configuration( ) );
        break;
    }

    return player;
}
