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
        int settlementsNum = 0;
        int citiesNum = 0;



        vector<string> resources;
        vector<int> resourcesCount;
        vector<string> settlements;
        //vector<int> settlementsNum;
        vector<string> roads;
        vector<int> roadsNum;

    public:
       
       
       
        Player(string name);

        ~Player();

        string getName();
        int getPoints();
        void addPoints(int amount);

        // void placeSettelemnt(vector<string> places, vector<int> placesNum, Board &board);
        // void placeRoad(vector<string> places, vector<int> placesNum, Board &board);
        void rollDice();
    };
} // namespace ariel






#endif // Player_HPP