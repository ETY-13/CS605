// main.cpp
// 2020.2.28
// Theng Yang

// A source file that drive the setup and option logic
// for a Tic Tac Toe game.

#include "TicTacToe.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;

#include<algorithm>
using std::transform;

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
        cout << "Enter Player1 name: ";
        string name;
        getline(cin, name);
        if (name.empty()) {
            BotPlayer player1{true};

            cout << "\nEnter Player2 name: ";
            getline(cin, name);
            if (name.empty()) {
                BotPlayer player2{false};
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
                BotPlayer player2{false};
                start(player1, player2);
            } else {
                Player player2{name, false};
                start(player1, player2);
            }
        }
    }
    else{
        cout << "Enter the saved file name: ";
        string filename;
        getline(cin, filename);
        std::ifstream infile(filename);
        if (!infile) {
            cout << "File Not Found"<<endl;
        }
        else{
            bool board[50]={};
            int pos = 0;
            while (true){
                char in;
                infile>>in;
                if(infile.eof())
                    break;

                if(in=='0'){
                    board[pos] = 0;
                    pos +=1;
                }
                else if(in=='1'){
                    board[pos] = 1;
                    pos +=1;
                }
                if(in==']') {
                    cout << endl;
                    for (auto i = 0; i < 25; i++) {
                        if (board[i]) {
                            cout << "|_X_|";
                        } else if (board[i + 25]) {
                            cout << "|_O_|";
                        } else {
                            cout << ("|___|");
                        }

                        if ((i + 1) % 5 == 0) {
                            printf("\n");
                        }
                    }
                    cout << endl;
                }
                if(pos==50){
                    pos =0;
                }
            }
        }
        infile.close();
    }
    return 0;
}
