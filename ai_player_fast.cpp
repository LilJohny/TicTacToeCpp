#include <tuple>
#include <vector>
#include <iostream>
#include "tic_tac_toe_board.h"
#include "ai_player_fast.h"

int
ai_player_fast::get_steps_to_win(TicTacToeBoard current_board, std::tuple<int, int> coordinates, int player) {
    int ai_player = player;
    std::vector<TicTacToeBoard> generated_boards;
    generated_boards.push_back(current_board);
    int num_steps = 0;
    int cur_board_ind = 0;
    int cur_player = player;
    int prev_num_free_places = current_board.get_free().size();
    TicTacToeBoard cur_board;
    while(cur_board_ind < generated_boards.size()){
        cur_board = generated_boards[cur_board_ind];
        std::vector<std::tuple<int, int>> free_in_cur_board = cur_board.get_free();
        for( std::tuple<int,int> coord : free_in_cur_board){
            if(free_in_cur_board.size() < prev_num_free_places){
                prev_num_free_places = free_in_cur_board.size();
                num_steps++;
            }
            TicTacToeBoard new_board = TicTacToeBoard(generated_boards[cur_board_ind]);
            if (player == X_PLAYER) {
                new_board.set_cross(std::get<0>(coord), std::get<1>(coordinates));
            } else {
                new_board.set_zero(std::get<0>(coord), std::get<1>(coordinates));
            }
            generated_boards.push_back(new_board);
            cur_player = -cur_player;
            if(new_board.check_endgame() == ai_player){
                return num_steps;
            }

        }
        cur_board_ind++;



    }
    return current_board.size * current_board.size;

}


ai_player_fast::ai_player_fast() = default;

std::tuple<int, int> ai_player_fast::get_next_step(std::tuple<int, TicTacToeBoard> state) {
    int player = std::get<0>(state);
    auto board = std::get<1>(state);
    if (player != X_PLAYER && player != O_PLAYER) {
        throw std::runtime_error("Player values should be -1 for o or 1 for x (X_PLAYER and O_PLAYER)");
    }
    std::vector<std::tuple<int, int>> free_coords = board.get_free();
    if (free_coords.empty()) {
        throw std::runtime_error("Game is over. No free coordinates");
    }
    std::tuple<int, int> current_best_step = free_coords[0];
    int min_steps_to_win = board.size * board.size;

    for (std::tuple<int, int> coordinates : free_coords) {
        int current_min_steps_to_win = get_steps_to_win(board, coordinates, player);//Is it copy? Should be copy
        if (current_min_steps_to_win < min_steps_to_win) {
            min_steps_to_win= current_min_steps_to_win;
            current_best_step = coordinates;
        }
    }
    return current_best_step;
}


