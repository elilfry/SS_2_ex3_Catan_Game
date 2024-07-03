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
    string name1, name2, name3;
    cout << "Welcome to Catan game right on your terminal!\n" << endl;
    cout << "Please enter the names of the first player:" << endl;
    cin >> name1;
    cout << "Please enter the names of the second player:" << endl;
    cin >> name2;
    cout << "Please enter the names of the third player:" << endl;
    cin >> name3;

    cout << "Creating players..." << endl;
    Player p1(name1);
    cout << "Player " << name1 << " created." << endl;
    Player p2(name2);
    cout << "Player " << name2 << " created." << endl;
    Player p3(name3);
    cout << "Player " << name3 << " created." << endl;

    cout << "Creating Catan game..." << endl;
    Catan catan(p1, p2, p3); //create a new game with the 3 players

    cout << "Starting of the game. Every player places two settlements and two roads." << endl;
    catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
    //catan.getBoard().printBoard(); // get the board of the game.


}
    