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
        string name;
        int points;
        int knights = 0;
        int roadsNum = 0;
        int totalResources = 0;
        //int settlementsNum = 0;
        //int citiesNum = 0;


        int resources[5]; // Assuming 5 types of resources: WOOD, BRICK, SHEEP, WHEAT, IRON
       
        // vector<string> resources;
        // vector<int> resourcesCount;
        // vector<string> settlements;
        // //vector<int> settlementsNum;
        // vector<string> roads;
        // vector<int> roadsNum;

    public:
       
       
       
        Player(string name);

        ~Player();

        string getName();
        int getPoints();
        void addPoints(int amount);
        int getRoadsNum();
        void addRoadsNum(int amount);

        void addResource(int resourceType, int amount);
        void removeResource(int resourceType, int amount);
        int getResource(int resourceType);
        void setTotalResources(int totalResources);


        // void placeSettelemnt(vector<string> places, vector<int> placesNum, Board &board);
        // void placeRoad(vector<string> places, vector<int> placesNum, Board &board);
        void rollDice();
        int getTotalResources();
        void sumIs7();
        void printResources();
    };
} // namespace ariel






#endif // Player_HPP