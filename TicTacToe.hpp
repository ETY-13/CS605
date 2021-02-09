// TicTacToe.hpp
// 2020.2.28
// Theng Yang

// A header file that contains the definition for a simple TicTacToe game logic.
// No corresponding source file.
#ifndef TIC_TAC_TOE_TICTACTOE_H
#define TIC_TAC_TOE_TICTACTOE_H
#include"Player.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include<algorithm>

#include<fstream>

template<typename Player1, typename  Player2>
class TicTacToe{
public:
    TicTacToe(const Player1 &p1, const Player2 &p2):_p1_(p1), _p2_(p2){}
    TicTacToe(const Player1 &p1, const Player2 & p2, bool save):_p1_(p1), _p2_(p2),_saveGame_(save),_saveIter_(0){}
    void saveGame(std::string file_name){

        std::ofstream outfile(file_name);
        bool end = false;
        for(auto i = 0 ; i < 32; i++){
            outfile<<"[";
            for(auto j = 0; j < 50; j++){
                outfile<<_savedBoard_[i][j];
            }
            outfile<<"]"<<endl;

            if(_savedBoard_[i][50] || _savedBoard_[i][51]){
                break;
            }
        }
        outfile.close();

    }

    void printBoard(){
        cout << endl;
        for (auto i = 0; i < 25; i++) {
            if ( _board_[i]) {
                cout<<"|_X_|";
            }
            else if ( _board_[i + 25]) {
                cout<<"|_O_|";
            }
            else
            {
                cout<<("|___|");
            }

            if ((i+1) % 5 == 0) {
                printf("\n");
            }
        }
        cout << endl;

    }
    void play() {
        printBoard();
        while (true) {

            _p1_.getMove(_board_);
            printBoard();
            if(_saveGame_){
                std::copy(std::begin(_board_), std::end(_board_), std::begin(_savedBoard_[_saveIter_]));
                _saveIter_ +=1;
            }

            if (_board_[50]) {
                cout << "Player 1: " << _p1_.getName() << " Won" << endl;
                break;
            } else if (_board_[51]) {

                cout << "Player 2: " << _p2_.getName() << " Won" << endl;
                break;
            } else if (_board_[52]) {

                cout << "Game Tied" << endl;
                break;
            }
            _p2_.getMove(_board_);
            printBoard();
            if(_saveGame_){
                std::copy(std::begin(_board_), std::end(_board_), std::begin(_savedBoard_[_saveIter_]));
                _saveIter_ +=1;
            }

            if (_board_[50]) {
                cout << "Player 1: " << _p1_.getName() << " WON" << endl;
                _p1_.increaseScore();
                break;
            } else if (_board_[51]) {
                cout << "Player 2: " << _p2_.getName() << " WON" << endl;
                _p2_.increaseScore();
                break;
            } else if (_board_[52]) {
                cout << "Game Tied" << endl;
                break;
            }
        }
    }
private:
    Player1 _p1_;
    Player2 _p2_;
    bool _board_[64] = {};
    bool _savedBoard_[32][64] ={};
    bool _saveGame_ = false;
    int _saveIter_ = 0;
};



#endif //TIC_TAC_TOE_TICTACTOE_H
