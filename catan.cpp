#include "catan.hpp"

using namespace std;

namespace ariel
{
    
    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        try
        {
            cout << "Initializing players..." << endl;
            players.push_back(&p1);
            players.push_back(&p2);
            players.push_back(&p3);
            cout << "Players initialized." << endl;

            cout << "Initializing board..." << endl;
            board = Board();
            cout << "Board initialized." << endl;

            this->ChooseStartingPlayer();
            cout << "Starting player chosen.\n" << endl;
            
        }
        catch (const std::exception &e)
        {
            cerr << "Exception during Catan initialization: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown error during Catan initialization." << endl;
        }
    }

    Catan::~Catan()
    {
        cout << "Catan game destroyed." << endl;
    }
    
    // Catan::Catan(Player &p1,Player &p2,Player &p3)
    // {
    //     cout << "Initializing players..." << endl;
        
    //     players.push_back(&p1);
    //     players.push_back(&p2);
    //     players.push_back(&p3);
        
    //     cout << "Players initialized." << endl; 
    //    board = Board();
        

    //     cout << "Board initialized." << endl;

    //     //this->ChooseStartingPlayer();

    //     cout << "Starting player chosen." << endl;

    // }

    //Catan::~Catan(){}

    void Catan::ChooseStartingPlayer() //need to check
    {
        srand(time(0));
        currentPlayer = rand() % 3;
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

    void Catan::placeSettlement(vector<string> places, vector<int> placesNum)
    {
        // check if the player has enough resources
        // check if the player has a road in the places
        // check if the places are valid
        // check if the places are empty
        // check if the places are not too close to other settlements
        // check if the places are not too close to other roads
    }




} // namespace ariel