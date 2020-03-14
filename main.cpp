#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>
#include <map>
#include "tic_tac_toe_board.h"
#include "ai_player_random.h"
#include "ai_player_fast.h"

class Game {
private:
    std::map<int, std::function<std::tuple<int, int>(
            std::tuple<int, TicTacToeBoard>)>> ai_map{{0, ai_player_random::get_next_step},
                                                      {1, ai_player_fast::get_next_step}};
    std::function<std::tuple<int, int>(std::tuple<int, TicTacToeBoard>)> ai_next_step;

    std::tuple<int, int> get_move(int player) {
        std::cout << "Player " << player << " please, enter coordinates of your step " << std::endl;

        int x, y;
        std::vector<int> options;
        options.reserve(size);
        for (int i = 1; i <= size; ++i) {
            options.push_back(i);
        }
        std::tuple<int, int> coord{-1, -1};
        std::vector<std::tuple<int, int>> free_coords = table.get_free();
        while (std::count(free_coords.begin(), free_coords.end(), coord) <= 0) {
            std::cout << "Please, enter x coordinate of your step (row)" << std::endl;
            x = Game::get_int(options);
            x--;
            std::cout << "Please, enter y coordinate of your step (column)" << std::endl;
            y = Game::get_int(options);
            y--;
            coord = {x, y};
            if (std::count(free_coords.begin(), free_coords.end(), coord) <= 0 && table.coordinates_in_range(coord)) {
                std::cout << "Coordinates is used already" << std::endl;
            }
        }
        return coord;
    }


    void set_rival() {
        int option;
        std::cout << "If you wish to play against AI enter 0" << std::endl
                  << " If you wish to play against a friend enter 1" << std::endl;
        std::vector<int> options{AI, PERSON};
        option = get_int(options);
        rival = option;
        if (rival == AI) {
            std::cout << "Choose AI type:" << std::endl << "Type 0 to choose random AI" << std::endl
                      << "Type 1 to choose tree-strategy AI" << std::endl;
            int ai_type = get_int(options);
            ai_next_step = ai_map[ai_type];
        }
    }

public:
    TicTacToeBoard &table;
    int rival{};
    int size;

    explicit Game(TicTacToeBoard &current_table) : table(current_table) {
        std::cout << "Welcome to TIC-TAC-TOE game" << std::endl;
        size = current_table.size;
        set_rival();
    }

    static int get_int(const std::vector<int> &options) {
        std::string option;
        int option_int = -1;
        bool exception = false;
        while (std::count(options.begin(), options.end(), option_int) == 0) {
            exception = false;
            std::cin >> option;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << "Invalid input" << std::endl;
            } else {
                option.erase(std::remove(option.begin(), option.end(), '\n'), option.end());
                try {
                    option_int = std::stoi(option);
                }
                catch (std::exception &ex) {
                    exception = true;
                    std::cout << "You typed not integer value. Try again" << std::endl;
                }
            }
            if (std::count(options.begin(), options.end(), option_int) == 0 && !exception) {
                std::cout << "Your input is inappropriate in current context" << std::endl;
            }
        }
        return option_int;
    }

    void play() {

        std::cout << "Let's start" << std::endl;
        std::cout << "Player 1 will play for X" << std::endl << " Player 2 will play for 0";
        int num_moves = 0;
        while (!table.get_free().empty() && table.check_endgame() == 0) {
            std::tuple<int, int> next_move;
            std::cout << table.get_repr_string();
            if (rival == AI && num_moves % 2 != 0) {
                std::tuple<int, TicTacToeBoard> state{O_PLAYER, table};
                next_move = ai_next_step(state);
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
        std::cout << table.get_repr_string();
        std::cout << "GAME OVER. THE WINNER IS: " << std::endl;
        int winner = table.check_endgame();
        if (winner == X_PLAYER) {
            std::cout << "PLAYER 1 (X)";
        } else if (winner == O_PLAYER) {
            std::cout << "PLAYER 2 (0)";
        } else {
            std::cout << "DRAW";
        }
    }

};

TicTacToeBoard create_table() {
    int option;
    TicTacToeBoard table;

    std::cout << "We offer a n*n field game " << std::endl << "Please, enter size of n that you wish" << std::endl;
    std::vector<int> options{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    option = Game::get_int(options);
    table = TicTacToeBoard(option);
    return table;
}

int main() {
    auto table = create_table();
    auto g = Game(table);
    g.play();
    return 0;
}

