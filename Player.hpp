// Player.hpp
// 2020.2.28
// Theng Yang

// Header file. The source file is Player.cpp.
#ifndef TIC_TAC_TOE_Player_H
#define TIC_TAC_TOE_Player_H

#include<string>
#include<vector>

extern unsigned long long board_searched; // for counting the number of board searched
auto eval(const char *board)->int;
auto checkTied(const char *board)->bool;

class Player {
public:
    explicit Player(bool first_player);
    Player(std::string name, bool first_player);

    [[maybe_unused]] void virtual getMove(char *board);

    [[maybe_unused]] [[nodiscard]] std::string virtual getName()const;

    [[maybe_unused]] void virtual increaseScore();

    [[maybe_unused]] int virtual getScore();

private:
    std::string _name_;
    int _score_ = 0;
    bool _first_player_ = false;
};

class BotPlayer:public Player{
public:
    explicit BotPlayer(bool first_player);
    BotPlayer(bool first_player, char search_alg, int search_time = 10);
    [[maybe_unused]] void getMove(char *board) override;
private:
    [[maybe_unused]] int _score_ = 0;
    bool _first_player_ = false;
    int _search_time_ = 10;  // using timer to search
    int _search_limit_ = 10; // the iteration (mcts) or depth (alpha_beta) of search
    char search_alg = 'A'; // A is alpha_beta, M is mcts
};
#endif //TIC_TAC_TOE_BOARD_H
