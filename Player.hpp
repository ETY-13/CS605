// Player.hpp
// 2020.2.28
// Theng Yang

// Header file. The source file is Player.cpp.
#ifndef TIC_TAC_TOE_Player_H
#define TIC_TAC_TOE_Player_H

#include<string>
#include<vector>

extern unsigned long long board_searched; // for counting the number of board searched

class Player {
public:
    explicit Player(bool first_player);
    Player(std::string name, bool first_player);

    [[maybe_unused]] void virtual getMove(bool *board);

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

    [[maybe_unused]] void getMove(bool *board) override;
private:
    [[maybe_unused]] int _score_ = 0;
    bool _first_player_ = false;
};
#endif //TIC_TAC_TOE_BOARD_H
