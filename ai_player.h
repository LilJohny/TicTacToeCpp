#ifndef TICTACTOE_AI_PLAYER_H
#define TICTACTOE_AI_PLAYER_H


#include <tuple>
#include "tic_tac_toe_board.h"

class ai_player {
public:
    static std::tuple<int, int> get_next_step(std::tuple<int, TicTacToeBoard> state);
};


#endif //TICTACTOE_AI_PLAYER_H
