cmake_minimum_required(VERSION 3.16)
project(Tic_Tac_Toe)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tic_Tac_Toe main.cpp TicTacToe.cpp TicTacToe.hpp Player.cpp Player.hpp)