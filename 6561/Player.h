#pragma once

class Board;
class Player
{
public:
    enum class Type
    {
        RANDOM,
        HUMAN,
        EXPECT_MAX,
        EXPECT_MAX_LIGHTWEIGHT
    };

    virtual Move get_best_move( const Board& board ) = 0;
    virtual void
    change_root( const Move& move )
    {
    }
};

class Random : public Player
{
public:
    Random( );
    virtual ~Random( );

    Move get_best_move( const Board& board ) override;
};

class Human : public Player
{
public:
    Human( );
    virtual ~Human( );

    Move get_best_move( const Board& board ) override;
};

class Timer;
class TTable;
class Configuration;
class ExpectMax : public Player
{
public:
    explicit ExpectMax( const Configuration& configuration );
    ~ExpectMax( );

    Move get_best_move( const Board& board ) override;

    void enable_solo_mode( );
    void enable_logging( );
    void disable_logging( );

private:
    int32_t m_nodes;
    int32_t m_total_nodes;
    int32_t m_total_time;
    bool m_use_ttable;
    bool m_can_abort;
    bool m_aborted;
    bool m_solo;
    bool m_log;
    int32_t m_min_depth;
    Move m_forbidden_move;

    std::unique_ptr< TTable > m_ttable;
    std::unique_ptr< Timer > m_timer;

    using HistoryNode = std::pair< Board, Move >;
    std::list< HistoryNode > m_history;

    const Configuration& m_configuration;

    double depth_first_search( const Board& board,
                               uint32_t depth,
                               uint32_t max_depth,
                               bool& exact,
                               Move* out_best_move = nullptr );
};
