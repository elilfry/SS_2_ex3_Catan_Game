#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "board.hpp"

namespace ariel
{
    class Catan
    {
    private:
        Board board;
        vector<Player*> players;
        int currentPlayer;

    public:
        Catan(Player& p1, Player& p2, Player& p3);
        ~Catan();

        void ChooseStartingPlayer();
        Board& getBoard();
        Player& getCurrentPlayer();
        void nextPlayer();
        void previousPlayer();

        void placeSettlement(Player &player,Board &board);
    };
} // namespace ariel




#endif // CATAN_HPP