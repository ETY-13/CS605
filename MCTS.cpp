// MCTS.hpp
// 2020.3.07
// Theng Yang

// A simple implementation of MCTS.

#include "MCTS.hpp"
#include "Player.hpp"

#include<time.h>

// Check game state for a win or a tie
int checkGame(char* board) {

    int x_win = 0;
    int o_win = 0;

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

    for (auto i = 0; i < 25; i += 5) {
        x_win = 0;
        o_win = 0;
        for (auto j = i; j < i + 5; j++) {
            checkmove(board[j]);
            // check for wins
            if (x_win >= 4) {
                return 20;
            }
            else if (o_win >= 4) {
                return -20;
            }
        }

    }

    // Vertical Check
    for (auto i = 0; i < 5; i++) {

        x_win = 0;
        o_win = 0;

        for (auto j = 0; j < 25; j += 5) {

            checkmove(board[j + i]);
            // check for wins
            if (x_win >= 4) {
                return 20;
            }
            else if (o_win >= 4) {
                return -20;
            }
        }
    }

    // Left diagonal Check
    x_win = 0;
    o_win = 0;

    for (auto i = 0; i < 25; i += 6) {

        checkmove(board[i]);
        // check for wins
        if (x_win >= 4) {
            return 20;
        }
        else if (o_win >= 4) {
            return -20;
        }
    }

    x_win = 0;
    o_win = 0;

    for (auto i = 4; i <= 20; i += 4) {
        checkmove(board[i]);
        // check for wins
        if (x_win >= 4) {
            return 20;
        }
        else if (o_win >= 4) {
            return -20;
        }

    }

    bool tied = true;

    for (auto i = 0; i < 25; i++) {
        if (board[i] == '\0') {
            tied = false;
            break;
        }
    }

    if (tied) {
        return -1;
    }
    return 0;
}

MCTS::MCTS(char* board, bool first_player, bool rolled, float c):
        _first_player_(first_player), _rolled_(rolled),_c_(c) {
            for (auto i = 0; i < 25; i++) {
                _board_[i] = board[i];
            }
        }

// Select the node with the best UCT score, and
// add new node (board state) to the search tree.
void MCTS::select(){
    auto mcts_node = this;
    while (!mcts_node->childs.empty()) {
        float best_child_uct = -1000;
        int best_child_index = 0;
        for (auto i = 0; i < mcts_node->childs.size(); i++) {
            if (mcts_node->childs[i]._uct_ > best_child_uct) {
                best_child_index = i;
                best_child_uct = mcts_node -> childs[i]._uct_;
            }
        }
        mcts_node = &mcts_node->childs[best_child_index];
    }

    if (mcts_node->_rolled_) {
        for (auto i = 0; i < 25; i++) {
            if (mcts_node->_board_[i] == NULL) {

                if (!mcts_node->_first_player_) {
                    mcts_node->_board_[i] = 'X';
                }
                else {
                    mcts_node->_board_[i] = 'O';
                }
                MCTS child_node(mcts_node->_board_);
                child_node._move_ = i;
                child_node.parent = mcts_node;

                child_node._first_player_ = !mcts_node->_first_player_;
                mcts_node->childs.push_back(child_node);

                mcts_node->_board_[i] = '\0';
            }
        }
    }
    else {
        board_searched +=1;
        mcts_node->rollout();
    }
}

// Do a random play
void MCTS::rollout() {

    char playboard[25];
    for (auto i = 0; i < 25; i++) {
        playboard[i] = _board_[i];
    }

    auto turn = _first_player_;

    std::vector<int> possible_moves;
    for (auto i = 0; i < 25; i++) {
        if (playboard[i] == NULL) {
            possible_moves.push_back(i);
        }
    }

    while (true) {
        auto game_state = checkGame(playboard);

        if (game_state >= 20) {
            _total_roll_out_ += 1;
            _rolled_ = true;;
            backprog('X');
            break;
        }
        else if (game_state <= -20) {
            _total_roll_out_ += 1;
            _rolled_ = true;
            backprog('O');
            break;
        }
        else if (game_state ==-1) {

            _total_roll_out_ += 1;
            _rolled_ = true;
            backprog();
            break;
        }

        int index = rand() % possible_moves.size();
        int move = possible_moves[index];
        possible_moves[index] = NULL;

        if (playboard[move] == NULL) {
            if (!turn) {
                playboard[move] = 'X';
                turn = !turn;
            }
            else {
                playboard[move] = 'O';
                turn = !turn;
            }
        }
    }
}

// Update statistic of each node in a search path
void MCTS::backprog(char winner) {
    auto mcts_node = this;

    while (mcts_node->parent != nullptr) {
        if (winner == 'O') {
            if (!mcts_node->_first_player_) {
                mcts_node->_win_ += 1;
            }
        }
        if (winner == 'X') {
            if (mcts_node->_first_player_) {
                mcts_node->_win_ += 1;
            }
        }
        mcts_node->parent->_total_roll_out_ += 1;
        mcts_node->_uct_ = (mcts_node->_win_ / mcts_node->_total_roll_out_) +
                            mcts_node->_c_ * sqrt(log(mcts_node->parent->_total_roll_out_) /
                            mcts_node->_total_roll_out_);
        mcts_node = mcts_node->parent;
    }
}

// Use select, rollout, and backpropagtion to
// get the best move for the current board state.
int MCTS::getmove(int iter, int think_time) {

    if (iter > 0) {
        while (iter > 0) {
            select();
            iter -= 1;
        }
    }
    else {
        float start = (float)clock() / CLOCKS_PER_SEC;
        float end = (float)clock() / CLOCKS_PER_SEC;
        while ((end - start) < think_time) {
            select();
            end = (float)clock() / CLOCKS_PER_SEC;
        }
    }

    float count = -10000;
    int move = -1;
    float check_uct = 0;
    for (auto const& c : childs) {
        if (c._total_roll_out_ > count) {
            move = c._move_;
            count = c._total_roll_out_;
            check_uct = c._uct_;
        }
        else if (c._total_roll_out_ == count) {
            if (c._uct_ > check_uct) {
                count = c._total_roll_out_;
                check_uct = c._uct_;
                move = c._move_;
            }
        }
    }
    return move;
}