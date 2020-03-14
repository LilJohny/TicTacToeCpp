//
// Created by denis on 14.03.20.
//

#include <tuple>
#include "ai_player_random.h"
#include "tictactoe_board.h"

std::random_device   ai_player_random::m_rd;
std::mt19937 ai_player_random::m_rng(ai_player_random::m_rd());


std::tuple<int, int> ai_player_random::get_next_step_naive(TicTacToeBoard table) {
    auto next_steps = table.get_free();
    std::uniform_real_distribution<double> dist(0, next_steps.size());
    int ind = dist(m_rng);
    return next_steps[ind];
}
