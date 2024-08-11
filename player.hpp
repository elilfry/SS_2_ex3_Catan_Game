#ifndef Player_HPP
#define Player_HPP

#include <iostream> 
#include <vector>

using namespace std;

namespace ariel
{
    
    class Player
    {
    private:

        int playerNumber;
        static int playerCount ;


        string name;
        int points;
        int knights = 0;
        int activeKnights=0;
        int roadsNum = 0;

        int victoryPointCard = 0;
        int monopolyCard = 0;
        int yearOfPlentyCard = 0;
        int roadBuildingCard = 0;

        int devCardsSum = 0;
        int totalResources = 0;
       


        int resources[5]; // Assuming 5 types of resources: WOOD, BRICK, SHEEP, WHEAT, IRON
       
       

    public:
       
       
       
        Player(string name);

        ~Player();

        string getName();
        int getPoints();
        void addPoints(int amount);
        int getRoadsNum();
        void addRoadsNum(int amount);

        int getDevCardsSum();

        void addKnights(int amount);

        void subKnights(int amount);

        void addActiveKnights(int amount);

        int getActiveKnightSum();

        int getMonopolyCard();

        void subMonopolyCard(int amount);

        int getYearOfPlentyCard();

        void subYearOfPlentyCard(int amount);

        int getRoadBuildingCard();

        void subRoadBuildingCard(int amount);

        int getKnightsNum();

        int getVictoryPointCard();

        void subVictoryPointCard(int amount);

        void bigArmyCard();

        void addResource(int resourceType, int amount);
        void removeResource(int resourceType, int amount);
        int getResource(int resourceType);


      
        int getTotalResources();
        void sumIs7();
        void printResources();

        void addDevCard(string devCardType);

        string getColor();
        
        void tradeResources(Player &otherPlayer, int giveResource, int giveAmount, int takeResource, int takeAmount);
        void tradeDevelopmentCards(Player &otherPlayer, int knightAmount, int woodAmount, int brickAmount, int sheepAmount, int wheatAmount, int ironAmount);
        void tradeWithBank(int resource, int amount, int giveResource);
        void printDetails();
    };
} // namespace ariel






#endif // Player_HPP