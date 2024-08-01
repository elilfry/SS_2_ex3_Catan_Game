#include "player.hpp"
#include "board.hpp"


namespace ariel
{

    
    
     Player::Player(string name)
    {
        this->name = name;
        this->points = 0;
        for(int i = 0; i < 5; i++)
        {
            resources[i] = 0;
        }
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

    void Player::addPoints(int amount)
    {
        this->points += amount;
    }

    int Player::getRoadsNum()
    {
        return this->roadsNum;
    }

    void Player::addRoadsNum(int amount)
    {
        this->roadsNum += amount;
    }

    void Player::printResources()
    {
        cout << "Player " << name << " resources:" << endl;
        cout << "Wood: " << resources[WOOD] << endl;
        cout << "Brick: " << resources[BRICK] << endl;
        cout << "Sheep: " << resources[SHEEP] << endl;
        cout << "Wheat: " << resources[WHEAT] << endl;
        cout << "Iron: " << resources[IRON] << endl;
    }

    void Player::addResource(int resourceType, int amount)
    {
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Invalid resource type." << endl;
            return;
        }
        else
        {
            resources[resourceType] += amount;
            cout << "Player " << name << " received " << amount << " " << resourceType << " resources." << endl;

        }
    }

    void Player::removeResource(int resourceType, int amount)
    {
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Invalid resource type." << endl;
            return;
        }
        else if(resources[resourceType] < amount)
        {
            cout << "Not enough resources." << endl;
            return;
        }
        else
        {
            resources[resourceType] -= amount;
        }
    } 

    int Player::getResource(int resourceType)
    {
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Invalid resource type." << endl;
            return -1;
        }
        else
        {
            return resources[resourceType];
        }
    }

           // int getTotalResources();
    int Player::getTotalResources()
    {
        for(int i = 0; i < 5; i++)
        {
            totalResources += resources[i];
        }
        return totalResources;
    }

    // void Player::sumIs7()
    // {
    //     int total = getTotalResources();
    //  if(total <8)
    //  {
    //     return;
    //  }else//pick random 1/2 of the resources and return them to the bank
    //  {

    //  }
    // }  

} // namespace ariel
