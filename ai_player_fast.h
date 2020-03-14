#ifndef TICTACTOE_AI_PLAYER_FAST_H

#include <random>
#include "tic_tac_toe_board.h"
#include "ai_player.h"
#include <cstdlib>
#include <ctime>

class ai_player_fast:ai_player {
private:
    static int get_steps_to_win(TicTacToeBoard current_board, int player);

public:
    ai_player_fast();

    static std::tuple<int, int> get_next_step(std::tuple<int, TicTacToeBoard> state);

};

#define TICTACTOE_AI_PLAYER_FAST_H

#endif //TICTACTOE_AI_PLAYER_FAST_H
