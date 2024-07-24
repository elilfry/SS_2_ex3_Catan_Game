/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
using namespace std;
using namespace ariel;

//create a new game with print to the user each step and printing the map of the game in the terminal

int main()
{
    string name1="Eli", name2="Meni", name3="Hodaya";
    cout << "Welcome to Catan game right on your terminal!\n" << endl;
    // cout << "Please enter the names of the first player:" << endl;
    // cin >> name1;
    // cout << "Please enter the names of the second player:" << endl;
    // cin >> name2;
    // cout << "Please enter the names of the third player:" << endl;
    // cin >> name3;

    cout << "Creating players..." << endl;
    Player p1(name1);
    cout << "Player " << name1 << " created." << endl;
    Player p2(name2);
    cout << "Player " << name2 << " created." << endl;
    Player p3(name3);
    cout << "Player " << name3 << " created." << endl;

    cout << "Creating Catan game..." << endl;
    Catan catan(p1, p2, p3); //create a new game with the 3 players

    Board board = catan.getBoard();


    catan.ChooseStartingPlayer(); 
    catan.getBoard().printBoard(); // get the board of the game.

        cout << "Starting of the game. Every player places two settlements and two roads." << endl;
        

        for(int i = 0; i < 3; i++)
        {
            cout << "Player " << catan.getCurrentPlayer().getName() << " turn. 1st Settelment" << endl;
            
           catan.placeSettlement(catan.getCurrentPlayer(), board);

            //catan.placeRoad(catan.getCurrentPlayer(), board);
            catan.nextPlayer();
        }
        
        //place the second settlement and road now frome the last player to the first player

        catan.previousPlayer();
        for(int i = 0; i < 3; i++)
        {
            cout << "Player " << catan.getCurrentPlayer().getName() << " turn.2nd Settelment" << endl;
           catan.placeSettlement(catan.getCurrentPlayer(), board);

            //catan.placeRoad(catan.getCurrentPlayer(), board);
            catan.previousPlayer();
        }


}
    