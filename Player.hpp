// Player.hpp
// 2020.2.28
// Theng Yang

// Header file. The source file is Player.cpp.
#ifndef TIC_TAC_TOE_Player_H
#define TIC_TAC_TOE_Player_H

#include<string>
#include<vector>

int minmax(bool *board, int depth, bool mm);

class Player {
public:
    Player(bool first_player);
    Player(std::string name, bool first_player);
    void virtual getMove(bool *board);
    std::string virtual getName()const;
    void virtual increaseScore();
    int virtual getScore();

private:
    std::string _name_;
    int _score_ = 0;
    bool _first_player_ = false;
};

class BotPlayer:public Player{
public:
    BotPlayer(bool first_player);
    void getMove(bool *board);
private:
    int _score_ = 0;
    bool _first_player_ = false;
};
#endif //TIC_TAC_TOE_BOARD_H
