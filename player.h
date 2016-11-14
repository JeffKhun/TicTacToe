#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Board.h"

class Player {

public:

    static void algoMove(Board &board) {
        int8_t best_value=-1;
        uint8_t best_move;
        for (uint8_t i=0; i<9; ++i) {
            if (board.addMove(i, Board::Algo_Player)) {
                int8_t value=minimax(board, Board::Algo_Player);
                if (best_value<value) {
                    best_value=value;
                    best_move=i;
                }
                board.removeMove(i);
            }
        }
        board.addMove(best_move, Board::Algo_Player);
    }
    
    static int8_t minimax(Board board, const Board::PositionState player) {
        Board::GameStatus status=board.gameStatus(Board::Algo_Player);
        if (Board::GameStatus::WON==status) return 1;
        if (Board::GameStatus::DRAW==status) return 0;
        if (Board::GameStatus::WON==board.gameStatus(Board::Human_Player)) return -1;
        
        int8_t best_value;
        for (uint8_t i=0; i<9; ++i) {
            if (Board::Algo_Player==player) {
                best_value=-1;
                if (board.addMove(i, Board::Human_Player))
                    best_value=std::max(best_value, minimax(board, Board::Human_Player));
            } else {
                best_value=1;
                if (board.addMove(i, Board::Algo_Player))
                    best_value=std::min(best_value, minimax(board, Board::Algo_Player));
            }
        }
        return best_value;
    }

    static void getFirstToMove(Board::PositionState &first_to_move) {
        char response;
        std::cout<<"Human Player moves first? (N for No. Default: Yes): ";
        std::cin>>response;
        if (response=='N' || response=='n')
            first_to_move=Board::PositionState::ALGO;
    }

    static void humanMove(Board &board) {
        uint8_t position;
        do {
            std::cout<<board<<"\nEnter move (0-8)|>8 to quit): ";
            std::cin>>position;
            position-='0';
            if (position>8)
                continue;
        } while (!board.addMove(position, Board::Human_Player));
    }
};

#endif //__PLAYER_H__