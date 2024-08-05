#include "catan.hpp"

using namespace std;

namespace ariel
{
    
    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        // static int boardInIt = 0;
        // boardInIt++;
            //initialize players
            players.push_back(&p1);
            players.push_back(&p2);
            players.push_back(&p3);
        
         for (int i = 0; i < 4; ++i) {
            devCards.push_back(std::make_unique<VictoryPoint>());
        }
        for (int i = 0; i < 3; ++i) {
            devCards.push_back(std::make_unique<Knight>());
        }
        for (int i = 0; i < 2; ++i) {
        devCards.push_back(std::make_unique<Monopoly>());
        devCards.push_back(std::make_unique<YearOfPlenty>());
        devCards.push_back(std::make_unique<RoadBuilding>());
        }

        //suffle the dev cards
        shuffleResources(devCards);

         //push the dev cards to the stack
        for (size_t i = 0; i < devCards.size(); i++)
        {
            devCardsDeck.push(move(devCards[i]));
        }
        
            this->ChooseStartingPlayer();
            
    
        
        
    }

    Catan::~Catan()
    {
        cout << "Catan game destroyed." << endl;
    }
    

    vector<Player*> Catan::getPlayers()
    {
        return players;
    }
    void Catan::shuffleResources(vector<std::unique_ptr<Devcard>> &devCards)
    {
        random_device rd;
        mt19937 g(rd());

        // Shuffle the resources vector using the random number generator
        shuffle(devCards.begin(), devCards.end(), g);

       

    }

    void Catan::ChooseStartingPlayer() //need to check
    {
        srand(time(0));
        currentPlayer = rand() % 3; // choose a random player to start
    }

    Board& Catan::getBoard()
    {
        return board;
    }

    Player& Catan::getCurrentPlayer()
    {
        return *players[(size_t)currentPlayer];
    }

    void Catan::nextPlayer()
    {
        currentPlayer = (currentPlayer + 1) % 3;
    }

    void Catan::previousPlayer()
    {
        currentPlayer = (currentPlayer + 2) % 3;
    }

    void Catan::placeSettlement(Player &player, Board &board    )
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }


        //if it is the 1st round of the game

        if(player.getPoints() < 2) 
        {
            cout << "Please enter where you want to place the settlement." << endl;
            int place;
            cin >> place;
            
            while(!board.placeSettlement(player, place))
            {
                cout << "Please enter again where you want to place the settlement." << endl;
                cin >> place;
            }
            player.addPoints(1);
        }
        else //if it is the 2nd round of the game or more
        {
            //check if the player has enough resources

            if(player.getResource(WOOD) < 1 || player.getResource(BRICK) < 1 || player.getResource(SHEEP) < 1 || player.getResource(WHEAT) < 1)
            {
                cout << "You don't have enough resources to place a settlement." << endl;
                return;
            }

            cout << "Please enter where you want to place the settlement." << endl;
            int place;
            cin >> place;

            while (!board.placeSettlement(player, place))
            {
                cout << "Please enter again where you want to place the settlement." << endl;
                cin >> place;
            }
            // Deduct the resources from the player
            player.removeResource(WOOD, 1);
            player.removeResource(BRICK, 1);
            player.removeResource(SHEEP, 1);
            player.removeResource(WHEAT, 1);


        }
       
    }

    void Catan::placeRoad(Player &player, Board &board)
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }

       //if we are in the 1st round of the game
        if(player.getPoints() <= 2 && player.getRoadsNum() < 2 )
        {
            cout << "Please enter where you want to place the road." << endl;
            int place;
            cin >> place;

            while(!board.placeRoad(player, place))
            {
                cout << "Please enter again where you want to place the road." << endl;
                cin >> place;
            }
        }else //if it is the 2nd round of the game or more
        {
            //check if the player has enough resources
            if(player.getResource(WOOD) < 1 || player.getResource(BRICK) < 1)
            {
                cout << "You don't have enough resources to place a road." << endl;
                return;
            }

            cout << "Please enter where you want to place the road." << endl;
            int place;
            cin >> place;

            while (!board.placeRoad(player, place))
            {
                cout << "Please enter again where you want to place the road." << endl;
                cin >> place;
            }
        }
    }

    void Catan::upgradeSettlementToCity(Player &player, Board &board)
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }

        //check if the player has enough resources
        if(player.getResource(IRON) < 3 || player.getResource(WHEAT) < 2)
        {
            cout << "You don't have enough resources to upgrade a settlement to a city." << endl;
            return;
        }

        cout << "Please enter where you want to upgrade the settlement to a city." << endl;
        int place;
        cin >> place;

        while (!board.upgradeSettlementToCity(player, place))
        {
            cout << "Please enter again where you want to upgrade the settlement to a city." << endl;
            cin >> place;
        }
        // Deduct the resources from the player
        player.removeResource(IRON, 3);
        player.removeResource(WHEAT, 2);
    }

    void Catan::intialResources(Board &board)
    {
         for(int i=0; i<players.size(); i++)
        {
            //distribute initial resources
            
        board.intialDistributeResources(*players[(size_t)i]);
        }
    }




    bool Catan::isGameFinished()
            {
                for (size_t i = 0; i < players.size(); i++)
                {
                    if (players[i]->getPoints() >= 10)
                    {
                        cout << "The game is finished. The winner is: " << players[i]->getName() << endl;
                        return true;
                    }
                }
                return false;
            }

    void Catan::rollDice( Board &board)
    {
        
        srand(time(0));
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int sum = dice1 + dice2;
        cout << "The sum of the dice is: " << sum << endl;

        if(sum == 7)
        {
            cout << "The sum of the dice is 7. All players with more than 7 resources will lose half of their resources." << endl;
            for(int i=0; i<players.size(); i++)
            {
                //players[i]->sumIs7();
            }
            return;
                
        }



        for(int i=0; i<players.size(); i++)
        {
            //distribute resources
            
        board.distributeResources(*players[(size_t)i], sum);
        }

    }
    Player* Catan::getPlayerByName( string &name)
    {
        for (Player* player : players)
    {
        if (player->getName() == name)
            return player;
    }
    return nullptr; // Player not found
    }

    
//     Catan::buyDevelopmentCard:

// Checks if the player has enough resources to buy a development card.
// Deducts the resources from the player if they have enough.
// Checks if there are development cards left in the deck.
// Gives the player a development card from the deck.
// Prints the action summary.

void Catan::buyDevelopmentCard(Player &player)
{
    //check if it is the player's turn
    if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
    {
        cout << "It is not your turn." << endl;
        return;
    }

    //check if there is a development card left in the deck
    if(devCardsDeck.empty())
    {
        cout << "There are no development cards left in the deck." << endl;
        return;
    }

    //check if the player has enough resources
    if(player.getResource(WHEAT) < 1 || player.getResource(IRON) < 1 || player.getResource(SHEEP) < 1)
    {
        cout << "You don't have enough resources to buy a development card." << endl;
        return;
    }

    // Deduct the resources from the player
    player.removeResource(WHEAT, 1);
    player.removeResource(IRON, 1);
    player.removeResource(SHEEP, 1);

    // Give the player a development card from the deck
    std::unique_ptr<Devcard> devCard = move(devCardsDeck.top());
    devCardsDeck.pop(); // remove the development card from the deck
    cout << "The development card you got is: " << devCard->getType() << endl;
    player.addDevCard(devCard->getType()); // add the development card to the player's hand
}

//     Catan::playDevelopmentCard:
void Catan::playDevelopmentCard(Player &player)
{
    //check if it is the player's turn
    if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
    {
        cout << "It is not your turn." << endl;
        return;
    }

    //check if the player has any development cards
    if(player.getDevCardsSum()<1)
    {
        cout << "You don't have any development cards to play." << endl;
        return;
    }

    cout << "Please enter the development card you want to play as a String:" << endl;
    cout << "1. Victory Point" << endl;
    cout << "2. Knight" << endl;
    cout << "3. Monopoly" << endl;
    cout << "4. Year of Plenty" << endl;
    cout << "5. Road Building" << endl;

    string devCardType;
    cin >> devCardType;

    bool valid = false;
    while (!valid) // loop until the player enters a valid development card type
    {
        if (devCardType == "Victory Point" || devCardType == "Knight" || devCardType == "Monopoly" || devCardType == "Year of Plenty" || devCardType == "Road Building")
        {
            valid = true;
        }else if (devCardType == "exit"){
            return;
        }
        else
        {
            cout << "Invalid development card type. Please enter again." << endl;
            cout<< "if you want to exit enter 'exit'." << endl;
            cin >> devCardType;
        }
    }

    //check if the player has the development card
    if(devCardType == "Victory Point" )
    {
        if(player.getVictoryPointCard() < 1)
        {
            cout << "You don't have a Victory Point development card to play." << endl;
            return;
        }else
        {
            //play this card
            VictoryPoint().playCard(player, *this);

        }


    }
    
    

}

    //print the 





} // namespace ariel