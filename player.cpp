#include "player.hpp"
#include "board.hpp"


namespace ariel
{

    int Player::playerCount = 0;
    
     Player::Player(string name)
    {
        this->name = name;
        this->points = 0;
        for(int i = 0; i < 5; i++)
        {
            resources[i] = 0;
        }
        this->playerNumber = ++playerCount;
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

    int Player::getDevCardsSum()
    {
        devCardsSum = knights + victoryPointCard + monopolyCard + yearOfPlentyCard + roadBuildingCard;
        return devCardsSum;
        
    }

    void Player::addKnights(int amount)
    {
        this->knights += amount;
    }

    void Player::subKnights(int amount)
    {
        this->knights -= amount;
    }

    int Player::getMonopolyCard()
    {
        return this->monopolyCard;
    }
    void Player::subMonopolyCard(int amount)
    {
        this->monopolyCard -= amount;
    }

    int Player::getYearOfPlentyCard()
    {
        return this->yearOfPlentyCard;
    }
    void Player::subYearOfPlentyCard(int amount)
    {
        this->yearOfPlentyCard -= amount;
    }

    int Player::getRoadBuildingCard()
    {
        return this->roadBuildingCard;
    }
    void Player::subRoadBuildingCard(int amount)
    {
        this->roadBuildingCard -= amount;
    }

    int Player::getKnightsNum()
    {
        return this->knights;
    }

    int Player::getVictoryPointCard()
    {
        return this->victoryPointCard;
    }

    void Player::subVictoryPointCard(int amount)
    {
        this->victoryPointCard -= amount;
    }

    void Player::bigArmyCard()
    {
        if(knights > 3)
        {
            points += 2;
        }
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
           // cout << "Player " << name << " received " << amount << " " << resourceType << " resources." << endl;

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

    void Player::addDevCard(string devCardType)
    {

        if(devCardType == "Knight")
        {
            knights++;
        }
        else if(devCardType == "Victory Point")
        {
            victoryPointCard++;
        }
        else if(devCardType == "Monopoly")
        {
            monopolyCard++;
        }
        else if(devCardType == "Year Of Plenty")
        {
            yearOfPlentyCard++;
        }
        else if(devCardType == "Road Building")
        {
            roadBuildingCard++;
        }
        else
        {
            cout << "Invalid development card type." << endl;
            return;
        }
       devCardsSum++;

    }

    string Player::getColor()
    {
        switch(playerNumber)
        {
            case 1:
                return "\033[1;33m"; //yellow
                break;

            case 2:
                return "\033[1;34m"; //blue
                break;
                
            case 3:
                return "\033[1;31m"; //red
                break;
        
            default:
                return "\033[0m"; //default color
                break;
        }

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
