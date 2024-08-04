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
        
        // if(boardInIt == 0){
        //      board = Board();

        // }else{
        //     cout << "The board is already initialized." << endl;
            
        // }

            this->ChooseStartingPlayer();
            
        
        
        
    }

    Catan::~Catan()
    {
        cout << "Catan game destroyed." << endl;
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

    









} // namespace ariel