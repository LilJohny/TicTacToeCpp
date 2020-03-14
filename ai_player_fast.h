#ifndef TICTACTOE_AI_PLAYER_FAST_H

#include <random>
#include "tic_tac_toe_board.h"
#include <cstdlib>
#include <ctime>

class ai_player_fast {
private:
    static int get_steps_to_win(TicTacToeBoard cur_board, std::tuple<int, int> coordinates, int player);

public:
    ai_player_fast();

    static std::tuple<int, int> get_next_step(std::tuple<int, TicTacToeBoard> state);

};

#define TICTACTOE_AI_PLAYER_FAST_H

#endif //TICTACTOE_AI_PLAYER_FAST_H
