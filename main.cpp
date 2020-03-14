#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "ai_player.h"
#include "tic_tac_toe_board.h"
#include "ai_player_random.h"

class Game {
private:
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


    void set_rival() {
        int option;
        while (true) {
            std::cout << "If you wish to play against AI enter 0" << std::endl
                      << " If you wish to play against a friend enter 1" << std::endl;
            std::cin >> option;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << "Invalid input" << std::endl;
            } else {
                if (option == 1 || option == 0) {
                    rival = option;
                    break;
                }
                std::cin.clear();
                std::cout << "Invalid input" << std::endl;

            }
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
        while (!table.get_free().empty()) {//ENDGAME ???????????????????/ check is invalid for draw ???
            if (table.check_endgame() != 0)
                break;
            std::tuple<int, int> next_move;
            std::cout << table.get_repr_string();
            if (rival == AI && num_moves % 2 != 0) {
                next_move = ai_player_random::get_next_step_naive(table);
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

