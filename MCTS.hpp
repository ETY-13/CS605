// MCTS.hpp
// 2020.3.07
// Theng Yang

// Header file for MCTS.

#ifndef TIC_TAC_TOE_MCTS_H
#define TIC_TAC_TOE_MCTS_H

#include<vector>

class MCTS {

public:
    MCTS(char* board, bool first_player = true, bool rolled = false, float c = 1.0);

    void select();

    void rollout();

    void backprog(char winner = NULL);

    int getmove(int iter = 0, int think_time = 10);

    // data variable
    std::vector<MCTS> childs;
    MCTS *parent = nullptr;

    char _board_[25] = {};
    float _uct_ = 10000;
    float _win_ = 0;
    float _total_roll_out_ = 0;
    float _c_ = 1.5;
    int _move_ = 0;
    bool _rolled_ = false;
    bool _first_player_ = true;

};


#endif //TIC_TAC_TOE_MCTS_H
