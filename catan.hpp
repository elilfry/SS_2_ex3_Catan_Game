#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "board.hpp"
#include <random>
#include <ctime>
#include <cstdlib> 


namespace ariel
{
    class Catan
    {
    private:
        Board board;
        vector<Player*> players; ///------
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
        void placeRoad(Player &player,Board &board);
        void upgradeSettlementToCity(Player &player,Board &board);

        bool isGameFinished();
        void rollDice( Board &board);
        Player *getPlayerByName(string &name);
        void distributeResources(int sum);
    };
} // namespace ariel




#endif // CATAN_HPP