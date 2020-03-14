#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "ai_players.h"
#include "TicTacToe.h"

class Game {
private:
    ai_player ai;

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
    TicTacToeBoard &table;
    int rival{};
    int size;

    explicit Game(TicTacToeBoard &current_table) : table(current_table) {
        std::cout << "Welcome to TIC-TAC-TOE game\n";
        size = current_table.size;
        set_rival();
    }


    void play() {

        std::cout << "Let's start\n";
        std::cout << "Player 1 will play for X\n Player 2 will play for 0";
        int num_moves = 0;
        while (!table.get_free().empty()) {//ENDGAME ???????????????????/ check is invalid for draw ???
            if (table.check_endgame() != 0)
                break;
            std::tuple<int, int> next_move;
            std::cout << table.get_repr_string();
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
        std::cout << table.get_repr_string();
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

};

TicTacToeBoard create_table() {
    int option;
    TicTacToeBoard table;
    while (true) {
        std::cout << "We offer a n*n field game \n Please, enter size of n that you wish\n";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Invalid input\n";
        } else {
            if (option > 0) {
                table = TicTacToeBoard(option);
                break;
            }
            std::cin.clear();
            std::cout << "Invalid input\n";

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

