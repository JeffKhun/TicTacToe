#ifndef __BOARD_H__
#define __BOARD_H__

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <array>

class Board {

    friend std::ostream& operator<<(std::ostream &out, const Board &rhs) {
        out<<"\nCurrent Board\n";
        for (int i=8; i>=0; --i) {
            switch (rhs.board_[i]) {
                case PositionState::HUMAN:      out<<"X "; break;
                case PositionState::ALGO:       out<<"O "; break;
                case PositionState::UNOCCUPIED: out<<i<<' '; break;
            }
            if (!(i%3))
                out<<'\n';
        }
        out<<std::endl;
        return out;
    }

public:

    enum class GameStatus : uint8_t {
        WON,
        DRAW,
        IN_PROGRESS
    };

    enum PositionState : uint8_t {
            HUMAN,
            ALGO,
            UNOCCUPIED
    };
    
    static const PositionState Human_Player = PositionState::HUMAN;
    static const PositionState Algo_Player = PositionState::ALGO;

    Board() {
        board_.fill(PositionState::UNOCCUPIED);
    }

    GameStatus gameStatus(const PositionState player) const {
        if (board_[0]==player) {
            if ((board_[0]==board_[1] && board_[0]==board_[2]) ||
                (board_[0]==board_[3] && board_[0]==board_[6]))
                    return GameStatus::WON;
        }
        if (board_[8]==player) {
            if ((board_[6]==board_[8] && board_[7]==board_[8]) ||
                (board_[2]==board_[8] && board_[5]==board_[8]))
                    return GameStatus::WON;
        }
        if (board_[4]==player) {
            if ((board_[3]==board_[4] && board_[4]==board_[5]) ||
                (board_[1]==board_[4] && board_[4]==board_[7]) ||
                (board_[0]==board_[4] && board_[4]==board_[8]) ||
                (board_[2]==board_[4] && board_[4]==board_[6]))
                    return GameStatus::WON;
        }
        if (std::find(board_.begin(), board_.end(), PositionState::UNOCCUPIED)==board_.end())
            return GameStatus::DRAW;
        return GameStatus::IN_PROGRESS;
    }
    
    bool addMove(const uint8_t position, const PositionState player) {
        if (board_[position]!=PositionState::UNOCCUPIED)
            return false;
        board_[position]=player;
        return true;
    }

    void removeMove(const uint8_t position) {
        board_[position]=PositionState::UNOCCUPIED;
    }

private:

    std::array<PositionState, 9> board_;
};

#endif //__BOARD_H__