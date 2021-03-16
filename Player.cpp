// Player.cpp
// 2020.2.28
// Theng Yang

// A ource file that contain the defintion for class Player

#include"Player.hpp"
#include"MCTS.hpp"

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

auto eval(const char *board)->int{

    int value = 0;

    int x_win = 0;
    int o_win = 0;
    int x_taken = 0;
    int o_taken = 0;

    auto checkmove = [&x_win, &o_win](char move) {
        if (move == 'X') {
            x_win += 1;
            o_win = 0;
        }
        else if (move == 'O') {
            x_win = 0;
            o_win += 1;
        }
        else {
            x_win = 0;
            o_win = 0;
        }
    };

    auto checkPieceLine = [&value](int x_taken, int o_taken) {
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

    for (auto i = 0; i < 25; i += 5) {
        x_win = 0;
        o_win = 0;
        x_taken = 0;
        o_taken = 0;
        for (auto j = i; j < i + 5; j++) {
            checkmove(board[j]);
            // check for wins
            if (x_win >= 4) {
                return 20;
            }
            else if (o_win >= 4) {
                return -20;
            }

            if (board[j] == 'X') {
                if (j % 5 > 0 && j % 5 < 4) {
                    o_taken = -5;
                }
                x_taken += 1;
            }
            else if (board[j] == 'O') {
                if ((j % 5 > 0 && j % 5 < 4)) {
                    x_taken = -5;
                }
                o_taken += 1;
            }
        }
       checkPieceLine(x_taken, o_taken);
    }

    // Vertical Check
    for (auto i = 0; i < 5; i++) {

        x_win = 0;
        o_win = 0;
        x_taken = 0;
        o_taken = 0;

        for (auto j = 0; j < 25; j += 5) {

            // check for wins
            checkmove(board[j + i]);
            if (x_win >= 4) {
                return 20;
            }
            else if (o_win >= 4) {
                return -20;
            }

            // Check for line pieces
            if (board[j + i] == 'X') {
                x_taken += 1;
                if (j > 0 && j < 20) {
                    o_taken = -5;
                }
            }
            else if (board[j + i] == 'O') {
                o_taken += 1;
                if (j > 0 && j < 20) {
                    x_taken = -5;
                }
            }
        }
       checkPieceLine(x_taken, o_taken);
    }

    // Left diagonal Check
    x_win = 0;
    o_win = 0;
    x_taken = 0;
    o_taken = 0;

    for (auto i = 0; i < 25; i += 6) {

        // check for wins
        checkmove(board[i]);
        if (x_win >= 4) {
            return 20;
        }
        else if (o_win >= 4) {
            return -20;
        }
        if (board[i] == 'X') {
            x_taken += 1;
            if (i == 6 || i == 12 || i == 18) {
                o_taken = -5;
            }
        }
        else if (board[i] == 'O') {
            o_taken += 1;
            if (i == 6 || i == 12 || i == 18) {
                x_taken = -5;
            }
        }
    }
   checkPieceLine(x_taken, o_taken);

    // check right-daigonal
    x_win = 0;
    o_win = 0;
    x_taken = 0;
    o_taken = 0;

    for (auto i = 4; i <= 20; i += 4) {
        // check for wins
        checkmove(board[i]);
        if (x_win >= 4) {
            return 20;
        }
        else if (o_win >= 4) {
            return -20;
        }

        if (board[i] == 'X') {
            x_taken += 1;
            if (i == 8 || i == 12 || i == 16) {
                o_taken = -5;
            }
        }
        else if (board[i] == 'O') {
            o_taken += 1;
            if (i == 8 || i == 12 || i == 16) {
                x_taken = -5;
            }
        }

    }
    checkPieceLine(x_taken, o_taken);

    return value;
}
auto checkTied(const char * board)->bool{

    for(auto i = 0; i < 25; i++){
        if(board[i] ==NULL){
            return false;
        }
    }
    return true;
}


int minimax(char *board, bool first_player, int depth, bool mm){
    board_searched +=1;
    int value = eval(board);
    if(!first_player){
        value = value *-1;
    }
    if (value >= 20 || value <= -20) {
        return value + depth;
    }

    if (depth == 0) {
        return value;
    }

    if (mm) {
        for (auto i = 0; i <25; i++) {
            if (!(board[i] =='X' || board[i] =='O')) {

                if(first_player){
                    board[i] ='X';
                }else {
                    board[i] = 'O';
                }
                int score = minimax(board, !first_player, depth - 1, !mm) ;
                value = max(value, score);
                board[i] = NULL;
            }
        }
        return value;
    }
    else {

        for (auto i = 0; i <25; i++) {
            if (!(board[i] =='X' || board[i] =='O')) {

                if(first_player){
                    board[i] = 'X';
                }else {
                    board[i] = 'O';
                }
                int score = minimax(board, !first_player, depth - 1, !mm);
                value = min(value, score );
                board[i] = NULL;
            }

        }
        return value;
    }
}

int alpha_beta(char *board, bool first_player, int reverse_score, int depth, bool mm, int alpha, int beta){
    board_searched +=1;
    int value = eval(board) * reverse_score;

    if (value >=20 || value <=-20) {
        return value +depth;
    }
    if (depth == 0) {
        return value;
    }
    if (mm) {

        for (auto i = 0; i <25; i++) {
            if (!(board[i] =='X' || board[i] =='O')) {
                if(first_player){
                    board[i] = 'X';
                }
                else{
                    board[i] ='O';
                }

                value = max(value, alpha_beta(board, !first_player, reverse_score, depth-1,!mm, alpha, beta));
                alpha = max(alpha, value);
                board[i] = NULL;
                if(alpha >=beta){
                    break;
                }
            }
        }
        return value;
    }
    else {

        for (auto i = 0; i <25; i++) {
            if (!(board[i] =='X' || board[i] =='O')) {
                if(first_player){
                    board[i] = 'X';
                }else{
                    board[i] ='O';
                }

                value = min(value, alpha_beta(board, !first_player, reverse_score,depth-1, !mm, alpha, beta) );
                beta = min(beta, value);
                board[i] = NULL;
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

[[maybe_unused]] void Player::getMove(char *board) {

    bool tied = checkTied(board);

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

        int move = 5 * (row - 1) + (col - 1);

        if (!(board[move] =='X' || board[move] =='O')) {
            if(_first_player_) {
                board[move] = 'X';
            }
            else {
                board[move] = 'O';
            }
            break;
        }
    }

    int score = eval(board);

    if(score >=20){
       board[25] = 'X';
    }else if(score <=-20){
        board[25] = 'O';
    }
    else if(tied){
        board[25] = 'T';
    }
}

[[maybe_unused]] void Player::increaseScore() {
    _score_ += 1;
}

[[maybe_unused]] int Player::getScore() {
    return _score_;
}

BotPlayer::BotPlayer(bool first_palyer):Player(first_palyer),_first_player_(first_palyer) {}
BotPlayer::BotPlayer(bool first_palyer, char search_alg, int search_time):Player(first_palyer),
            _first_player_(first_palyer),search_alg(search_alg),_search_time_(search_time) {}

void do_alpha_beta_search(char *board, bool first_player, int search_time){

    int best = -100;
    int r = -1;
    int reverse_score = 1;
    auto search_start= clock()/CLOCKS_PER_SEC;
    auto search_end= clock()/CLOCKS_PER_SEC;
    int search_depth = 7;

    while((search_end - search_start) < search_time) {
        board_searched = 0;
        for (auto i = 0; i < 25; i++) {

            if (!(board[i] == 'X' || board[i] == 'O')) {
                if (first_player) {
                    board[i] = 'X';
                } else {
                    board[i] = 'O';
                    reverse_score = -1;
                }
                int mov_val = max(mov_val, alpha_beta(board, !first_player, reverse_score,
                                search_depth, false, -1000, 1000));
                if (mov_val > best) {
                    r = i;
                    best = mov_val;
                }
                board[i] = NULL;
            }
        }
        search_depth +=1;
        search_end= clock()/CLOCKS_PER_SEC;
    }

    cout<<"Number of Board Evaluated (Minimax-Alpha-Beta): "<<board_searched<<", Search Time: "
        <<(search_end - search_start)<<" sec"<<endl;

    if(best >=20){
        if(first_player){
            board[25] = 'X';
        }
        else {
            board[25] = 'O';
        }
    }
    if (r==-1) {
        board[25] = 'T';
    }
    else{
        if(first_player) {
            board[r] = 'X';
        }else{
            board[r] ='O';
        }
    }
}

void do_mcts(char *board, bool first_player, int search_time){

    board_searched = 0;
    if(checkTied(board)){
        board[25] ='T';
    }
    else {
        MCTS mcts(board, first_player, true);
        int move = mcts.getmove(0,search_time);
        if (first_player) {
            board[move] = 'X';
        } else {
            board[move] = 'O';
        }

        cout<<"Number of Board Evaluated (MCTS): "<<board_searched<<", Search Time: "
            <<search_time<<" sec"<<endl;

        int score = eval(board);
        if (score >= 20) {
            board[25] = 'X';
        } else if (score <= -20) {
            board[25] = 'O';
        }
    }
}

[[maybe_unused]] void BotPlayer::getMove(char *board) {
    if(search_alg == 'A'){
        do_alpha_beta_search(board, _first_player_, _search_time_);
    }

    if(search_alg =='M'){
        do_mcts(board, _first_player_, _search_time_);
    }

}

