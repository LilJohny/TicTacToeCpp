#ifndef TICTACTOE_AI_PLAYERS_H

#include <random>
#include "tic_tac_toe_board.h"
#include <cstdlib>
#include <ctime>

class ai_player {
private:
    static int get_step_score(TicTacToeBoard cur_board, std::tuple<int, int> coordinates, int player, TicTacToeBoard board,
                       int ai_player = DEFAULT_PLAYER,
                       int current_score = 0);

public:
    ai_player();

    static std::tuple<int, int> get_next_step(std::tuple<int, TicTacToeBoard> state);

};

#define TICTACTOE_AI_PLAYERS_H

#endif //TICTACTOE_AI_PLAYERS_H
