#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>
#include <map>
#include "ai_player.h"
#include "tic_tac_toe_board.h"
#include "ai_player_random.h"

class Game {
private:
    std::map<int, std::function<std::tuple<int, int>(
            std::tuple<int, TicTacToeBoard>)>> ai_map{{0, ai_player_random::get_next_step},
                                                      {1, ai_player::get_next_step}};
    std::function<std::tuple<int, int>(std::tuple<int, TicTacToeBoard>)> ai_next_step;

    std::tuple<int, int> get_move(int player) {
        while (true) {
            std::cout << "Player " << player << " please, enter coordinates of your step " << std::endl;

            int x, y;
            while (true) {
                std::cout << "Please, enter x coordinate of your step (row)" << std::endl;
                std::cin >> x;
                x--;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cout << "Invalid input" << std::endl;
                } else {
                    if (x > size || x < 0) {
                        std::cin.clear();
                        std::cout << "Invalid input" << std::endl;
                    }
                    break;

                }
            }

            while (true) {
                std::cout << "Please, enter y coordinate of your step (column)" << std::endl;
                std::cin >> y;
                y--;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cout << "Invalid input" << std::endl;
                } else {
                    if (y > size || y < 0) {
                        std::cin.clear();
                        std::cout << "Invalid input" << std::endl;
                    }
                    break;
                }
            }


            std::tuple<int, int> c{x, y};
            std::vector<std::tuple<int, int>> free_coords = table.get_free();
            if (std::count(free_coords.begin(), free_coords.end(), c) > 0) {
                return c;
            } else if (!table.coordinates_in_range(c)) {
                std::cout << "Coordinates out of range" << std::endl;
            } else {
                std::cout << "Coordinates is used already" << std::endl;
            }
        }

    }

    static int get_int(const std::vector<int> &options) {
        std::string option;
        int option_int = 2;
        while (std::count(options.begin(), options.end(), option_int) == 0) {
            std::getline(std::cin, option);
            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << "Invalid input" << std::endl;
            } else {
                option.erase(std::remove(option.begin(), option.end(), '\n'), option.end());
                try {
                    option_int = std::stoi(option);
                }
                catch (std::exception ex) {
                    std::cout << "You typed not integer value. Try again" << std::endl;
                }
            }
        }
        return option_int;
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


    void play() {

        std::cout << "Let's start" << std::endl;
        std::cout << "Player 1 will play for X" << std::endl << " Player 2 will play for 0";
        int num_moves = 0;
        while (!table.get_free().empty()) {
            if (table.check_endgame() != 0)
                break;
            std::tuple<int, int> next_move;
            std::cout << table.get_repr_string();
            if (rival == AI && num_moves % 2 != 0) {
                std::tuple<int, TicTacToeBoard> state{2, table};
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
    while (true) {
        std::cout << "We offer a n*n field game " << std::endl << "Please, enter size of n that you wish" << std::endl;
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Invalid input" << std::endl;
        } else {
            if (option > 0) {
                table = TicTacToeBoard(option);
                break;
            }
            std::cin.clear();
            std::cout << "Invalid input" << std::endl;

        }
    }
    return table;
}

int main() {
    auto table = create_table();
    auto g = Game(table);
    g.play();
    return 0;
}

