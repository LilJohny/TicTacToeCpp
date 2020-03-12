#include <iostream>
#include <vector>

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
    TicTacToe(size_t n) {
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
    int check_endgame(){
        for(auto &row :table)
    }
};

int main() {
    auto t = new TicTacToe(5);
    std::cout << t->get_string();
    return 0;
}
