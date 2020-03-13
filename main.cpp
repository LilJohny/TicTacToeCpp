#include <iostream>
#include <vector>
#include <tuple>

class TicTacToe {
private:
    std::vector<std::vector<int >> table;
    const static char cross = 'x';
    const static char zero = 'o';
    const static char empty = '.';
    const static char vertical_line = '|';
    const static char horizontal_line = '-';
    size_t size;

public:
    explicit TicTacToe(size_t n) {
        table.reserve(n);
        size = n;
        for (int i = 0; i < n; ++i) {
            table.emplace_back(n, 0);
        }
    }

    std::string get_string() {
        std::string representation;
        representation.append("\n");
        for (auto &row : table) {
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

    int check_endgame() {
        std::vector<int> cross_row(size, 1);
        std::vector<int> zero_row(size, -1);
        for (auto &row :table) {
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
            main_diagonal.push_back(table[i][i]);
            sub_diagonal.push_back(table[j][i]);
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
                column.push_back(table[k][i]);
            }
            if (column == cross_row) {
                return 1;
            } else if (column == zero_row) {
                return -1;
            }
        }
        return 0;
    }

    void set_cross(int i, int j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            table[i][j] = 1;
        }
    }

    void set_zero(int i, int j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            table[i][j] = -1;
        }
    }

    std::vector<std::tuple<int, int>> get_free() {
        std::vector<std::tuple<int, int>> free;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (table[i][j] == 0) {
                    free.emplace_back(i,j);
                }
            }
        }
        return free;
    }


};

int main() {
    auto t = new TicTacToe(5);
    std::cout << t->get_string();
    t->check_endgame();
    return 0;
}
