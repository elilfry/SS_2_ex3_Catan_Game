#include "catan.hpp"

using namespace std;

namespace ariel
{
    
    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        
            //initialize players
            players.push_back(&p1);
            players.push_back(&p2);
            players.push_back(&p3);

            cout << "Initializing board..." << endl;
            board = Board();
            cout << "Board initialized." << endl;

            this->ChooseStartingPlayer();
            cout << "Starting player chosen.\n" << endl;
            
        
        
        
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
        return this->board;
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

            cout << "Please enter where you want to place the settlement." << endl;
            int place;
            cin >> place;

            while (!board.placeSettlement(player, place))
            {
                cout << "Please enter again where you want to place the settlement." << endl;
                cin >> place;
            }


        }
       
        
        
        
    }




} // namespace ariel