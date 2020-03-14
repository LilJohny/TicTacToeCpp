//
// Created by denis on 14.03.20.
//

#include <random>
#include "tic_tac_toe_board.h"

#ifndef TICTACTOE_AI_PLAYER_NAIVE_H

using std::mt19937;

class ai_player_random {
    static std::random_device m_rd;
    static std::mt19937 m_rng;
public:
    static std::tuple<int, int> get_next_step(std::tuple<int, TicTacToeBoard> state);
};

#define TICTACTOE_AI_PLAYER_NAIVE_H

#endif //TICTACTOE_AI_PLAYER_NAIVE_H
