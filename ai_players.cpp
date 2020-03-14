#include <tuple>
#include <vector>
#include "ai_players.h"

int
ai_player::get_step_score(TicTacToeBoard cur_board, std::tuple<int, int> coordinates, int player, TicTacToeBoard board,
                          int ai_player,
                          int current_score) {
    if (ai_player == DEFAULT_PLAYER) {
        ai_player = player;
    }
    if (cur_board.get_free().empty()) {
        if (cur_board.check_endgame() == ai_player)
            return 1;
        else
            return 0;
    }

    if (player == X_PLAYER) {
        cur_board.set_cross(std::get<0>(coordinates), std::get<1>(coordinates));

    } else {
        cur_board.set_zero(std::get<0>(coordinates), std::get<1>(coordinates));
    }
    int sum_of_subscores = 0;
    while (!cur_board.get_free().empty()) {
        std::vector<std::tuple<int, int>> free_coords = board.get_free();
        for (std::tuple<int, int> coords : free_coords) {
            sum_of_subscores += get_step_score(cur_board, coords, -player, board, ai_player, current_score);
        }

    }
    return sum_of_subscores;

}


ai_player::ai_player() = default;

std::tuple<int, int> ai_player::get_next_step_naive(TicTacToeBoard table) {
    auto next_steps = table.get_free();
    return next_steps[0];
}

std::tuple<int, int> ai_player::get_next_step_tree_strategy(int player, TicTacToeBoard board) {
    if (player != X_PLAYER && player != O_PLAYER) {
        throw std::runtime_error("Player values should be -1 for o or 1 for x (X_PLAYER and O_PLAYER)");
    }
    std::vector<std::tuple<int, int>> free_coords = board.get_free();
    if (free_coords.empty()) {
        throw std::runtime_error("Game is over. No free coordinates");
    }
    std::tuple<int, int> current_best_step = free_coords[0];
    int current_best_score = -10;

    for (std::tuple<int, int> coordinates : free_coords) {
        int current_score = get_step_score(board, coordinates, player, board);//Is it copy? Should be copy
        if (current_score > current_best_score) {
            current_best_score = current_score;
            current_best_step = coordinates;
        }
    }
    return current_best_step;
}
