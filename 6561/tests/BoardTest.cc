#include "../sources/Common.h"
#include "../sources/Board.h"

#include <gtest/gtest.h>

TEST( BoardTest, check_board_initialization )
{
    Board board;
    ASSERT_FALSE( board.end_game( ) );
}
