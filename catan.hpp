#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "board.hpp"
#include "devcard.hpp"
#include <stack>
#include <random>
#include <ctime>
#include <cstdlib> 
#include <memory>
#include <algorithm>
#include <climits>



namespace ariel
{

    class Devcard; // Forward declaration

    class Catan
    {
    private:
        Board board;
        vector<Player*> players;
       int currentPlayer;
        vector<std::unique_ptr<Devcard>> devCards;
        stack<std::unique_ptr<Devcard>> devCardsDeck;


    public:
        Catan(Player& p1, Player& p2, Player& p3);
        ~Catan();

        vector<Player *> getPlayers();

        void shuffleCards(vector<std::unique_ptr<Devcard>> &devCards);

        void ChooseStartingPlayer();
        Board& getBoard();
        Player& getCurrentPlayer();
        
        void setCurrentPlayer(int playerIndex); //for testing
        void nextPlayer();
        void previousPlayer();

        void placeSettlement(Player &player,Board &board);
        void placeRoad(Player &player,Board &board);
        void upgradeSettlementToCity(Player &player,Board &board);

        bool isGameFinished();
        void rollDice( Board &board);
        Player *getPlayerByName(string &name);
        void distributeResources(int sum);

        void intialResources(Board &board);

        void buyDevelopmentCard(Player &player);
        void playDevelopmentCard(Player &player);
        
        void trade(Player &player);
        int getValidInput(int min, int max, const string &prompt);
        void tradeResources(Player &player);
        void tradeDevelopmentCard(Player &player);
        void tradeWithBank(Player &player);
        //void trade(Player &player);
    };
} // namespace ariel




#endif // CATAN_HPP