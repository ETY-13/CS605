// Player.cpp
// 2020.2.28
// Theng Yang

// A ource file that contain the defintion for class Player

#include"Player.hpp"
#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;
using std::cin;

#include<algorithm>
using std::max;
using std::min;


auto eval(const bool *b)->int{

    int value = 0;

    for (auto i = 0; i < 50; i+=5) {

        int win = 0;
        int x_taken = 0;
        int o_taken = 0;

        // Horizontal Win
        for (auto j = i; j < i+5; j++) {
            if (b[j]) {
                win += 1;
            }
            else {
                win = 0;
            }
            if (j<25 &&b[j]) {

                if ((j % 5 > 0 && j % 5 < 4)) {
                    o_taken = -5;
                }

                x_taken += 1;
            }
            else if (j < 25 && b[j+25]) {
                if ((j % 5 > 0 && j % 5 < 4)) {
                    x_taken -= 5;
                }
                o_taken += 1;
                win = 0;
            }

            if (i < 25 && win >= 4) {
                return 20;
            }

            else if (i >= 25 && win >= 4) {
                return -20;
            }
        }
        if (x_taken >= 3) {
            value += 3;
        }
        else if (x_taken >= 2 && o_taken < 2) {
            value += 1;
        }
        else if (x_taken >= 1 && o_taken <= 1) {
            value += 1;
        }
        if (o_taken >= 3) {
            value -= 3;
        }
        else if (o_taken >= 2 && x_taken < 2) {
            value -= 1;
        }

        else if (o_taken >= 1 && x_taken <= 1) {
            value -= 1;
        }

    }

    for (auto i = 0; i < 5; i++) {

        int ver_win = 0;
        int ver_wino = 0;

        int x_taken = 0;
        int o_taken = 0;

        for (auto j = 0; j < 25; j += 5) {

            if (b[j + i]) {
                ver_win += 1;
                x_taken += 1;

                if (ver_win >= 4) {
                    return 20;
                }
                if (j > 0 && j < 20) {
                    o_taken -= 5;

                }
            }

            else {
                ver_win = 0;
            }

            if (b[25 + j + i]) {
                ver_wino += 1;
                o_taken += 1;

                if (ver_wino >= 4) {
                    return -20;
                }
                if (j > 0 && j < 20) {

                    x_taken -= 5;
                }
            }

            else {
                ver_wino = 0;
            }

        }
        if (x_taken >= 3) {
            value += 3;
        }
        else if (x_taken >= 2 && o_taken < 2) {
            value += 1;
        }
        else if (x_taken >= 1 && o_taken <= 1) {
            value += 1;
        }
        if (o_taken >= 3) {
            value -= 3;
        }
        else if (o_taken >= 2 && x_taken < 2) {
            value -= 1;
        }

        else if (o_taken >= 1 && x_taken <= 1) {
            value -= 1;
        }
    }

    int di_win = 0;
    int di_wino = 0;
    int x_taken = 0;
    int o_taken = 0;

    for (auto i = 0; i < 25; i += 6) {

        if (b[i]) {
            di_win += 1;
            x_taken += 1;
            if (di_win >= 4) {
                return 20;
            }
            if (i == 6 || i == 12 || i == 18) {
                o_taken -= 5;
            }
        }
        else {
            di_win = 0;
        }

        if (b[49 - i]) {
            di_wino += 1;
            o_taken += 1;
            if (di_wino >= 4) {
                return -20;
            }
            if (i ==6||i==12||i==18) {
                x_taken -= 5;
            }
        }
        else {
            di_wino = 0;
        }
    }
    if (x_taken >= 3) {
        value += 3;
    }
    else if (x_taken >= 2 && o_taken < 2) {
        value += 1;
    }
    else if (x_taken >= 1 && o_taken <= 1) {
        value += 1;
    }
    if (o_taken >= 3) {
        value -= 3;
    }
    else if (o_taken >= 2 && x_taken < 2) {
        value -= 1;
    }

    else if (o_taken >= 1 && x_taken <= 1) {
        value -= 1;
    }

    int op_di_win = 0;
    int op_di_wino = 0;

    x_taken = 0;
    o_taken = 0;

    for (auto i = 4; i <= 20; i += 4) {
        if (b[i]) {
            op_di_win += 1;
            x_taken += 1;
            if (op_di_win >= 4) {
                return 20;
            }
            if (i == 8 || i == 12 || i == 16) {
                o_taken -= 5;
            }
        }
        else {
            op_di_win = 0;
        }

        if (b[49 - i]) {
            op_di_wino += 1;
            o_taken += 1;

            if (op_di_wino >= 4) {
                return -20;
            }
            if (i == 8 || i == 12 || i == 16) {
                x_taken -= 5;
            }
        }
        else {
            op_di_wino = 0;
        }
    }
    if (x_taken >= 3) {
        value += 3;
    }
    else if (x_taken >= 2 && o_taken < 2) {
        value += 1;
    }
    else if (x_taken >= 1 && o_taken <= 1) {
        value += 1;
    }
    if (o_taken >= 3) {
        value -= 3;
    }
    else if (o_taken >= 2 && x_taken < 2) {
        value -= 1;
    }

    else if (o_taken >= 1 && x_taken <= 1) {
        value -= 1;
    }

    return value;
}

int minmax(bool *board, int turn, int depth, bool mm){

    int value = eval(board) * turn;
    if (value >= 20 || value <= -20) {
        return value = depth;
    }

    if (depth == 0) {
        return value;
    }
    if (mm) {
        int start = 0;
        int end = 25;
        int op_start = 25;
        if (turn == -1) {
            start = 25;
            end = 50;
            op_start = -25;
        }
        for (auto i = start; i <end; i++) {

            if (!(board[i] || board[i+op_start])) {
                board[i] = 1;
                int score = minmax(board,turn, depth - 1, !mm) ;
                value = max(value, score);
                board[i] = 0;

            }
        }
        return value;
    }
    else {

        int start = 25;
        int end = 50;
        int op_start = -25;
        if (turn == -1) {
            start = 0;
            end = 25;
            op_start = 25;
        }

        for (auto i = start; i <end; i++) {
            if (!(board[i] || board[i+op_start])) {

                board[i] = 1;
                int score = minmax(board, turn, depth - 1, !mm);
                value = min(value, score );
                board[i] = 0;

            }

        }
        return value;
    }
}

int alpha_beta(bool *board, int f_or_s, int depth, bool mm, int alpha, int beta){
    int value = eval(board) * f_or_s;
    if (value >=20 || value <=-20) {
        return value + depth;
    }
    if (depth == 0) {
        return value;
    }
    if (mm) {
        int start = 0;
        int end = 25;
        int op_start = 25;
        if (f_or_s == -1) {
            start = 25;
            end = 50;
            op_start = -25;
        }
        for (auto i = start; i <end; i++) {

            if (!(board[i] || board[i+op_start])) {
                board[i] = 1;
                value = max(value, alpha_beta(board, f_or_s, depth - 1, !mm, alpha, beta));
                alpha = max(alpha, value);
                board[i] = 0;

                if(alpha >=beta){
                    break;
                }
            }
        }
        return value;
    }
    else {
        int start = 25;
        int end = 50;
        int op_start = -25;
        if (f_or_s == -1) {
            start = 0;
            end = 25;
            op_start = 25;
        }
        for (auto i = start; i <end; i++) {

            if (!(board[i] || board[i+op_start])) {
                board[i] = 1;
                value = min(value, alpha_beta(board, f_or_s, depth - 1, !mm, alpha, beta) );
                beta = min(beta, value);
                board[i] = 0;
                if(alpha >=beta){
                    break;
                }
            }
        }
        return value;
    }
}


Player::Player(bool first_player):_first_player_(first_player) {}
Player::Player(string name, bool first_player): _name_(name), _first_player_(first_player){}

string Player::getName()const {
    return _name_;
}

void Player::getMove(bool *board) {
    while (true) {
        cout << "Make a move Row: ";
        int row;
        cin >> row;
        int col;
        cout << "Make a move col: ";
        cin >> col;

        if (!row || !col) {
            cin.clear();
            cin.ignore();
            cout << endl;
        }

        if (row > 5 || col > 5 || row * col <= 0) {
            continue;
        }

        int o_pos = 49 - 24 + (row - 1) * 4 + (row - 1) + (col - 1);
        int x_pos = (row - 1) * 4 + (row - 1) + (col - 1);

        if (!board[o_pos] && !board[x_pos]) {
            if(_first_player_)
                board[x_pos] = 1;
            else
                board[o_pos] = 1;
            break;
        }
    }
    int score = eval(board);
    if(score >=20){
       board[50] = 1;
    }else if(score <=-20){
        board[51] = 1;
    }

}

void Player::increaseScore() {
    _score_ += 1;
}
int Player::getScore() {
    return _score_;
}

BotPlayer::BotPlayer(bool first_palyer):Player(first_palyer),_first_player_(first_palyer) {}

void BotPlayer::getMove(bool *board) {
    int best = -100;
    int r = -1;
    int turn = 1;
    int start = 0;
    int end = 25;
    int op_start = 25;

    if (!_first_player_) {
        turn = -1;
        start = 25;
        op_start = -25;
        end = 50;
    }

    for (auto i =start; i < end; i++) {

        if (!(board[i] || board[op_start + i])) {
            board[i] = 1;
            int mov_val = max(mov_val,alpha_beta(board, turn, 3, false,-1000,1000));
            if (mov_val > best) {
                r = i;
                best = mov_val;
            }
            board[i] = 0;
        }
    }
    if(best >=20){
        if(_first_player_){
            board[50] = 1;
        }
        else {
            board[51] = 1;
        }
    }
    if (r==-1) {
        board[52] = 1;
    }
    else{
        board[r] = 1;
    }
}

