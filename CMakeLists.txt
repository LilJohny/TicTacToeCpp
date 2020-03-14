cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

add_executable(TicTacToe
        CMakeLists.txt
        main.cpp tictactoe_board.h ai_players.cpp ai_players.h tictactoe_board.cpp)
