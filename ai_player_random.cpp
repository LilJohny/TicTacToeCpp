#include <tuple>
#include "ai_player_random.h"
#include "tic_tac_toe_board.h"

std::random_device   ai_player_random::m_rd;
std::mt19937 ai_player_random::m_rng(ai_player_random::m_rd());


std::tuple<int, int> ai_player_random::get_next_step(std::tuple<int, TicTacToeBoard> state) {
    auto table = std::get<1>(state);
    auto next_steps = table.get_free();
    std::uniform_real_distribution<double> dist(0, next_steps.size());
    int ind = dist(m_rng);
    return next_steps[ind];
}
