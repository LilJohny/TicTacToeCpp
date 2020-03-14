#ifndef TICTACTOE_TICTACTOE_H
#define X_PLAYER 1
#define O_PLAYER -1
#define AI 0
#define PERSON 1

#include <vector>
#include <string>

class TicTacToeBoard {
private:
    std::vector<std::vector<int >> table_map;
    const static char cross = 'x';
    const static char zero = 'o';
    const static char empty = '.';
    const static char vertical_line = '|';
    const static char horizontal_line = '-';

    bool coordinate_in_range(int coordinate);

public:
    size_t size;

    explicit TicTacToeBoard(size_t n = 0);

    TicTacToeBoard(TicTacToeBoard const &board);

    std::string get_repr_string();

    int check_endgame();

    void set_cross(int i, int j);

    void set_zero(int i, int j);

    std::vector<std::tuple<int, int>> get_free();

    bool coordinates_in_range(std::tuple<int, int> coordinates);
};

#define TICTACTOE_TICTACTOE_H

#endif //TICTACTOE_TICTACTOE_H
