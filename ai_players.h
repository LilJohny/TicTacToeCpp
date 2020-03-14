#ifndef TICTACTOE_AI_PLAYERS_H

#include "tictactoe_board.h"


class ai_player {
private:
    int get_step_score(TicTacToeBoard cur_board, std::tuple<int, int> coordinates, int player, TicTacToeBoard board,
                       int ai_player = DEFAULT_PLAYER,
                       int current_score = 0);

public:
    ai_player();

    static std::tuple<int, int> get_next_step_naive(TicTacToeBoard table);

    std::tuple<int, int> get_next_step_tree_strategy(int player, TicTacToeBoard board);

};

#define TICTACTOE_AI_PLAYERS_H

#endif //TICTACTOE_AI_PLAYERS_H
