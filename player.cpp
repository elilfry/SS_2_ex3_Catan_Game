#include "player.hpp"


namespace ariel
{

    
    
     Player::Player(string name)
    {
        this->name = name;
        this->points = 0;
        cout << "Player " << name << " initialized with " << points << " points." << endl;
    }

    Player::~Player()
    {
    }

    string Player::getName()
    {
        return this->name;
    }

    int Player::getPoints()
    {
        return this->points;
    }

    // void Player::placeSettelemnt(vector<string> places, vector<int> placesNum, Board &board)
    // {
    //     // check if the player has enough resources
    //     // check if the player has a road in the places
    //     // check if the places are valid
    //     // check if the places are empty
    //     // check if the places are not too close to other settlements
    //     // check if the places are not too close to other roads



    // }

} // namespace ariel
