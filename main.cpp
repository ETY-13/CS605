// main.cpp
// 2020.2.28
// Theng Yang

// A source file that drive the setup and option logic
// for a Tic Tac Toe game.

#include "TicTacToe.hpp"
#include"MCTS.hpp"
#include"Player.hpp"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include<memory>
using std::pair;

#include<string>
using std::string;

#include<algorithm>
using std::transform;

#include<time.h>

template<typename P1, typename P2>
void start(P1 player1, P2 player2){
    while(true) {
        cout<<"\nDo you want to record and save the game play for later? Enter 'Y' for yes"<<endl;
        string answer;

        getline(cin,answer);
        transform(answer.begin(), answer.end(), answer.begin(),::tolower);

        if(answer=="y" || answer == "yes"){
            cout<<"\nEnter a name for the text file (exclude .txt): ";
            getline(cin, answer);
            if(answer ==""){
                answer = "TicTacToe_Game_Saved";
            }
            TicTacToe game{player1, player2,true};
            game.play();
            game.saveGame(answer +".txt");
        }
        else{
            TicTacToe game{player1, player2};
            game.play();
        }
        cout<<"\nDo you want to Play again, with the same opponent? Enter 'Y' to play or anything else to quit."<<endl;
        char ans;
        cin >> ans;
        ans = tolower(ans);

        if(ans=='y'){
            cin.ignore();
            continue;
        }
        break;
    }
}

auto getSearchAlg()->pair<char,int>{

    cout << "\nWhat search algorithm would you want for the bot?";
    cout << "\nAlpha Beta (default)\nMonte Carlo\n";
    string search_alg;
    getline(cin, search_alg);

    cout<<"What is the minimum search time (in second) you want for the algorithm? The default is 10 second."<<endl;
    cout<<"Keep in mind that alpha-beta may take 10 - 20 seconds more."<<endl;

    string search_ans;
    getline(cin,search_ans);
    int search_time;

    try{
        search_time = std::stoi(search_ans);
        }
    catch (std::invalid_argument) {
        search_time = 10;
    }

    transform(search_alg.begin(), search_alg.end(), search_alg.begin(),::tolower);
    if (search_alg =="monte carlo"){
        return {'M',search_time};
    }
    else{
        return {'A',search_time};
    }

}


int main() {
    string option;
    while (true) {
        cout << "This is a 5x5 tic tac toe game program. Your options are as below: " << endl;
        cout << "Enter: 'Play' to play " << endl;
        cout << "Enter: 'Playback' to playback a saved game " << endl;
        getline(cin, option);
        transform(option.begin(), option.end(), option.begin(),::tolower);
        if(option =="play" || option =="playback"){
            break;
        }
    }
    if(option == "play") {
        cout << "Choosing Players. Leave the player's name blank if you want to play against a bot." << endl;
        cout << "Enter Player 1 name: ";
        string name;
        getline(cin, name);
        if (name.empty()) {
            auto alg = getSearchAlg();
            BotPlayer player1{true, alg.first, alg.second};

            cout << "\nEnter Player 2 name: ";
            getline(cin, name);

            if (name.empty()) {

                auto alg = getSearchAlg();
                BotPlayer player2{false, alg.first, alg.second};
                start(player1, player2);

            } else {
                Player player2{name, false};
                start(player1, player2);
            }

        } else {
            Player player1{name, true};
            cout << "\nEnter Player2 name: ";
            getline(cin, name);
            if (name.empty()) {
                auto alg = getSearchAlg();
                BotPlayer player2{false,alg.first, alg.second};
                start(player1, player2);
            } else {
                Player player2{name, false};
                start(player1, player2);
            }
        }
    }
    else{
        cout << "Enter the saved file name (exclude .txt): ";
        string filename;
        getline(cin, filename);
        filename +=".txt";
        std::ifstream infile(filename);
        if (!infile) {
            cout << "File Not Found"<<endl;
        }
        else{
            int pos = 0;
            int moves_only = 0;
            bool player_turn = 0;
            while (true){

                char in;
                infile>>in;
                if(infile.eof())
                    break;

                if(moves_only >24){
                    switch (in) {
                        case('X'):
                            cout<<"\nX Win";
                            break;
                        case('O'):
                            cout<<"\nO Win";
                            break;
                        case('T'):
                            cout<<"\nGame Tied";
                            break;
                        default:
                            cout<<"Player "<<(player_turn?'O':'X')<<" moved.";
                            break;
                    };

                    moves_only = 0;
                    player_turn = !player_turn;
                    auto timer_start = clock()/CLOCKS_PER_SEC;
                    while(true){
                        auto timer_stop = clock()/CLOCKS_PER_SEC;
                        if((timer_stop - timer_start) > 1){
                            break;
                        }
                    }
                    continue;
                }
                if(in == NULL){
                    cout<<"|___|";
                    pos+=1;
                    moves_only +=1;
                }
                else if(!(in =='[' || in ==']')){
                    cout<<"|_"<<in<<"_|";
                    pos+=1;
                    moves_only +=1;
                }
                if(pos >4){
                    cout<<endl;
                    pos = 0;
                }
                if(in ==']' || in =='['){
                    cout<<endl;
                }
            }
        }
        infile.close();
    }
    return 0;
}
