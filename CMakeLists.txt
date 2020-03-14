cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

add_executable(TicTacToe
        CMakeLists.txt
        main.cpp tictactoe_board.h ai_player.cpp ai_player.h tictactoe_board.cpp ai_player_random.h ai_player_random.cpp)
