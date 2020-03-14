#include <vector>
#include <string>
#include <tuple>
#include "tic_tac_toe_board.h"


TicTacToeBoard::TicTacToeBoard(size_t n) {
    table_map.reserve(n);
    size = n;
    for (int i = 0; i < n; ++i) {
        table_map.emplace_back(n, 0);
    }
}

std::string TicTacToeBoard::get_repr_string() {
    std::string representation;
    representation.append("\n");
    for (auto &row : table_map) {
        representation.append("|");
        for (int j = 0; j < size; ++j) {
            if (row[j] == 1) {
                std::string symbol = std::string{cross};
                representation.append(symbol);
                representation.append("|");
            } else if (row[j] == -1) {
                std::string symbol = std::string{zero};
                representation.append(symbol);
                representation.append("|");
            } else if (row[j] == 0) {
                std::string symbol = std::string{empty};
                representation.append(symbol);
                representation.append("|");
            }
        }
        representation.append("\n");

    }
    return representation;
}

int TicTacToeBoard::check_endgame() {
    std::vector<int> cross_row(size, 1);
    std::vector<int> zero_row(size, -1);
    for (auto &row :table_map) {
        if (row == cross_row) {
            return 1;
        } else if (row == zero_row) {
            return -1;
        }
    }
    std::vector<int> main_diagonal;
    std::vector<int> sub_diagonal;
    main_diagonal.reserve(size);
    sub_diagonal.reserve(size);
    int j = size - 1;
    for (int i = 0; i < size; ++i) {
        main_diagonal.push_back(table_map[i][i]);
        sub_diagonal.push_back(table_map[j][i]);
        j--;
    }
    if (main_diagonal == cross_row || sub_diagonal == cross_row) {
        return 1;
    } else if (main_diagonal == zero_row || sub_diagonal == zero_row) {
        return -1;
    }
    for (int i = 0; i < size; ++i) {
        std::vector<int> column;
        column.reserve(size);
        for (int k = 0; k < size; ++k) {
            column.push_back(table_map[k][i]);
        }
        if (column == cross_row) {
            return 1;
        } else if (column == zero_row) {
            return -1;
        }
    }
    return 0;
};

void TicTacToeBoard::set_cross(int i, int j) {
    if (i >= 0 && i < size && j >= 0 && j < size) {
        table_map[i][j] = 1;
    }
}

void TicTacToeBoard::set_zero(int i, int j) {
    if (i >= 0 && i < size && j >= 0 && j < size) {
        table_map[i][j] = -1;
    }
}

std::vector<std::tuple<int, int>> TicTacToeBoard::get_free() {
    std::vector<std::tuple<int, int>> free;
    for (auto row = table_map.begin(); row != table_map.end(); row++) {
        for (auto col = row->begin(); col != row->end(); col++) {
            if ((*col) == 0) {
                int i = row - table_map.begin();
                int j = col - row->begin();
                free.emplace_back(i, j);
            }

        }
    }
    return free;
}



