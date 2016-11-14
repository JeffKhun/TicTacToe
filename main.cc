#include "player.h"

#include <functional>

int main() {

    std::ios_base::sync_with_stdio(false);

    Board board;
    Board::PositionState current_player; 
    
    Player::getFirstToMove(current_player);

    std::array<std::function<void(Board&)>, 2> fptr_moves={Player::humanMove, Player::algoMove};
    // void (*fptr_moves[2])(Board&) = {Player::humanMove, Player::algoMove};

    do {
        (fptr_moves[current_player])(board);
        Board::GameStatus status=board.gameStatus(current_player);
        if (Board::GameStatus::WON==status || Board::GameStatus::DRAW==status) {
            std::cout << board << std::endl;
            break;
        } else {
            current_player=static_cast<Board::PositionState>((current_player+1)%2);
        }
    } while (1);

    return 0;
}