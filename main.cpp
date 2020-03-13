#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define X_PLAYER 1
#define O_PLAYER -1
#define DEFAULT_PLAYER -2

class TicTacToe {
private:
    std::vector<std::vector<int >> table_map;
    const static char cross = 'x';
    const static char zero = 'o';
    const static char empty = '.';
    const static char vertical_line = '|';
    const static char horizontal_line = '-';


public:
    size_t size;

    explicit TicTacToe(size_t n = 0) {// DEFAULT ZERO NEEDED FOR CONSTRUCTOR GAME
        table_map.reserve(n);
        size = n;
        for (int i = 0; i < n; ++i) {
            table_map.emplace_back(n, 0);
        }
    }

    std::string get_string() {
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

    int check_endgame() {//DRAW???
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

    void set_cross(int i, int j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            table_map[i][j] = 1;
        }
    }

    void set_zero(int i, int j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            table_map[i][j] = -1;
        }
    }

    std::vector<std::tuple<int, int>> get_free() {
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
};

class ai_player {
private:

    int
    get_step_score(TicTacToe cur_board, std::tuple<int, int> coordinates, int player, TicTacToe board,
                   int ai_player = DEFAULT_PLAYER,
                   int current_score = 0) {
        if (ai_player == DEFAULT_PLAYER) {
            ai_player = player;
        }
        if (cur_board.get_free().empty()) {
            if (cur_board.check_endgame() == ai_player)
                return 1;
            else
                return 0;
        }

        if (player == X_PLAYER) {
            cur_board.set_cross(std::get<0>(coordinates), std::get<1>(coordinates));

        } else {
            cur_board.set_zero(std::get<0>(coordinates), std::get<1>(coordinates));
        }
        int sum_of_subscores = 0;
        while (!cur_board.get_free().empty()) {
            std::vector<std::tuple<int, int>> free_coords = board.get_free();
            for (std::tuple<int, int> coords : free_coords) {
                sum_of_subscores += get_step_score(cur_board, coords, -player, board, ai_player, current_score);
            }

        }
        return sum_of_subscores;

    }

public:


    ai_player() = default;

    std::tuple<int, int> get_next_step_naive(TicTacToe table) {
        auto next_steps = table.get_free();
        return next_steps[0];
    }

    std::tuple<int, int> get_next_step_tree_strategy(int player, TicTacToe board) {
        if (player != X_PLAYER && player != O_PLAYER) {
            throw std::invalid_argument("Player values should be -1 for o or 1 for x (X_PLAYER and O_PLAYER)");
        }
        std::vector<std::tuple<int, int>> free_coords = board.get_free();
        if (free_coords.empty()) {
            throw std::invalid_argument("Game is over. No free coordinates");
        }
        std::tuple<int, int> current_best_step = free_coords[0];
        int current_best_score = -10;

        for (std::tuple<int, int> coordinates : free_coords) {
            int current_score = get_step_score(board, coordinates, player, board);//Is it copy? Should be copy
            if (current_score > current_best_score) {
                current_best_score = current_score;
                current_best_step = coordinates;
            }
        }
        return current_best_step;
    }

};

class Game {
private:
    ai_player ai;
    int AI = 0;
    int PERSON = 1;


    void personalized_play() {

        std::cout << "Let's start\n";
        std::cout << "Player 1 will play for X\n Player 2 will play for 0";
        int num_moves = 0;
        while (!table.get_free().empty()) {//ENDGAME ???????????????????/ check is invalid for draw ???
            if (table.check_endgame() != 0)
                break;
            std::tuple<int, int> next_move;
            std::cout << table.get_string();
            if (rival == AI && num_moves % 2 != 0) {
                next_move = ai.get_next_step_naive(table);
            } else {
                next_move = get_move(num_moves % 2 + 1);
            }
            if (num_moves % 2 == 0) {
                table.set_cross(std::get<0>(next_move), std::get<1>(next_move));
            } else {
                table.set_zero(std::get<0>(next_move), std::get<1>(next_move));
            }
            num_moves++;
        }
        std::cout << table.get_string();
        std::cout << "GAME OVER. THE WINNER IS: \n";
        int winner = table.check_endgame();
        if (winner == X_PLAYER) {
            std::cout << "PLAYER 1 (X)";
        } else if (winner == O_PLAYER) {
            std::cout << "PLAYER 2 (0)";
        } else {
            std::cout << "DRAW";
        }


    }

    std::tuple<int, int> get_move(int player) {
        while (true) {
            std::cout << "Player " << player << " please, enter coordinates of your step \n";

            int x, y;
            while (true) {
                std::cout << "Please, enter x coordinate of your step (row)\n";
                std::cin >> x;
                x--;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cout << "Invalid input\n";
                } else {
                    if (x > size || x < 0) {
                        std::cin.clear();
                        std::cout << "Invalid input\n";

                    }
                    break;

                }
            }

            while (true) {
                std::cout << "Please, enter y coordinate of your step (column)\n";
                std::cin >> y;
                y--;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cout << "Invalid input\n";
                } else {
                    if (y > size || y < 0) {
                        std::cin.clear();
                        std::cout << "Invalid input\n";

                    }
                    break;

                }
            }


            std::tuple<int, int> c{x, y};
            std::vector<std::tuple<int, int>> free_coords = table.get_free();
            if (std::count(free_coords.begin(), free_coords.end(), c) > 0) {
                return c;
            } else {
                std::cout << "Coordinates out of range\n";
            }
        }

    }


    void set_rival() {
        int option;
        while (true) {
            std::cout << "If you wish to play against AI enter 0 \n If you wish to play against a friend enter 1\n";
            std::cin >> option;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << "Invalid input\n";
            } else {
                if (option == 1 || option == 0) {
                    rival = option;
                    if (rival == AI) {
                        ai = ai_player();
                    }
                    break;
                }
                std::cin.clear();
                std::cout << "Invalid input\n";

            }
        }

    }

public:
    TicTacToe &table;
    int rival{};
    int size;

    explicit Game(TicTacToe &current_table) : table(current_table) {
        std::cout << "Welcome to TIC-TAC-TOE game\n";
        size = current_table.size;
        set_rival();
    }


    void play() {
        personalized_play();
    }

};

TicTacToe set_size() {
    int option;
    TicTacToe table;
    while (true) {
        std::cout << "We offer a n*n field game \n Please, enter size of n that you wish\n";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Invalid input\n";
        } else {
            if (option > 0) {
                //               size = option;
                table = TicTacToe(option);
                break;
            }
            std::cin.clear();
            std::cout << "Invalid input\n";

        }
    }
    return table;
}

int main() {
    auto table = set_size();
    auto g = Game(table);
    g.play();
    return 0;
}

