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

#include<time.h>
using ::clock;

unsigned long long board_searched = 0;

auto eval(const bool *b)->int{

    int value = 0;

    auto checkPieceLine = [&value](int x_taken, int o_taken){
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
    };

    for (auto i = 0; i < 50; i+=5) {

        int win = 0;
        int x_taken = 0;
        int o_taken = 0;

        // Horizontal check
        for (auto j = i; j < i+5; j++) {
            if (b[j]) {
                win += 1;
            }
            else {
                win = 0;
            }

            // Check the number of X and O pieces
            // in each horizontal line
            if (j<25 && b[j]) {
                if (j % 5 > 0 && j % 5 < 4) {
                    o_taken = -5;
                }
                x_taken += 1;
            }
            else if (j<25 && b[j+25]) {
                if ((j % 5 > 0 && j % 5 < 4)) {
                    x_taken = -5;
                }
                o_taken += 1;
            }

            // check for wins
            if (i < 25 && win >= 4) {
                return 20;
            }
            else if (i >= 25 && win >= 4) {
                return -20;
            }
        }
        checkPieceLine(x_taken, o_taken);
    }

    // Vertical Check
    for (auto i = 0; i < 5; i++) {

        int ver_x_win = 0;
        int ver_o_win = 0;

        int x_taken = 0;
        int o_taken = 0;

        for (auto j = 0; j < 25; j += 5) {

            if (b[j + i]) {
                ver_x_win += 1;
                x_taken += 1;

                if (ver_x_win >= 4) {
                    return 20;
                }
                if (j > 0 && j < 20) {
                    o_taken = - 5;
                }
            }
            else {
                ver_x_win = 0;
            }

            if (b[25 + j + i]) {
                ver_o_win += 1;
                o_taken += 1;

                if (ver_o_win >= 4) {
                    return -20;
                }
                if (j > 0 && j < 20) {

                    x_taken = -5;
                }
            }
            else {
                ver_o_win = 0;
            }
        }
        if (x_taken >= 3) {
            value += 3;
        }
        checkPieceLine(x_taken, o_taken);
    }

    // Left diagonal Check
    int left_di_x_win = 0;
    int left_di_o_win = 0;
    int x_taken = 0;
    int o_taken = 0;

    for (auto i = 0; i < 25; i += 6) {

        if (b[i]) {
            left_di_x_win += 1;
            x_taken += 1;
            if (left_di_x_win >= 4) {
                return 20;
            }
            if (i == 6 || i == 12 || i == 18) {
                o_taken = -5;
            }
        }
        else {
            left_di_x_win = 0;
        }

        if (b[49 - i]) {
            left_di_o_win += 1;
            o_taken += 1;
            if (left_di_o_win >= 4) {
                return -20;
            }
            if (i ==6||i==12||i==18) {
                x_taken = -5;
            }
        }
        else {
            left_di_o_win = 0;
        }
    }
    checkPieceLine(x_taken, o_taken);

    // Right diagonal check
    int right_di_x_win = 0;
    int right_di_o_win = 0;

    x_taken = 0;
    o_taken = 0;

    for (auto i = 4; i <= 20; i += 4) {
        if (b[i]) {
            right_di_x_win += 1;
            x_taken += 1;
            if (right_di_x_win >= 4) {
                return 20;
            }
            if (i == 8 || i == 12 || i == 16) {
                o_taken = -5;
            }
        }
        else {
            right_di_x_win = 0;
        }
        if (b[49 - i]) {
            right_di_o_win += 1;
            o_taken += 1;

            if (right_di_o_win >= 4) {
                return -20;
            }
            if (i == 8 || i == 12 || i == 16) {
                x_taken = -5;
            }
        }
        else {
            right_di_o_win = 0;
        }
    }
    checkPieceLine(x_taken, o_taken);
    return value;
}

int minmax(bool *board, int f_or_s, int depth, bool mm){
    board_searched +=1;
    int value = eval(board) * f_or_s;
    if (value >= 20 || value <= -20) {
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
                int score = minmax(board, f_or_s, depth - 1, !mm) ;
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
        if (f_or_s == -1) {
            start = 0;
            end = 25;
            op_start = 25;
        }

        for (auto i = start; i <end; i++) {
            if (!(board[i] || board[i+op_start])) {
                board[i] = 1;
                int score = minmax(board, f_or_s, depth - 1, !mm);
                value = min(value, score );
                board[i] = 0;
            }

        }
        return value;
    }
}

int alpha_beta(bool *board, int f_or_s, int depth, bool mm, int alpha, int beta){
    board_searched +=1;
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

[[maybe_unused]] string Player::getName()const {
    return _name_;
}

[[maybe_unused]] void Player::getMove(bool *board) {

    bool tied = true;
    for(auto i = 0; i < 25; i ++){
        if(!(board[i] || board[25+i])){
            tied = false;
            break;
        }
    }

    while (!tied) {
        cout<<_name_<<" Turn."<<endl;
        cout << "Make a move (Row): ";
        int row;
        cin >> row;
        int col;
        cout << "\nMake a move (Col): ";
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
            if(_first_player_) {
                cout << x_pos << endl;
                board[x_pos] = 1;
            }
            else {
                cout << o_pos << endl;
                board[o_pos] = 1;
            }
            break;
        }
    }

    int score = eval(board);

    if(score >=20){
       board[50] = 1;
    }else if(score <=-20){
        board[51] = 1;
    }
    else if(tied){
        board[52] = 1;
    }
}

[[maybe_unused]] void Player::increaseScore() {
    _score_ += 1;
}

[[maybe_unused]] int Player::getScore() {
    return _score_;
}

BotPlayer::BotPlayer(bool first_palyer):Player(first_palyer),_first_player_(first_palyer) {}

[[maybe_unused]] void BotPlayer::getMove(bool *board) {
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

    auto search_start= clock();

    for (auto i =start; i < end; i++) {

        if (!(board[i] || board[op_start + i])) {
            board[i] = 1;
            int mov_val = max(mov_val,minmax(board, turn, 6, false));
            if (mov_val > best) {
                r = i;
                best = mov_val;
            }
            board[i] = 0;
        }
    }

    auto search_end= clock();
    cout<<"Number of Board Searched: "<<board_searched<<" Search Time: "
    <<(search_end - search_start)/CLOCKS_PER_SEC<<" sec"<<endl;

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

