/*
Catan in the Terminal
This is a simple implementation of the board game Catan in the terminal. It is written in c++.

The game is played by 3 players. The players take turns to build settlements and cities, roads, and buy development cards. The game ends when a player reaches 10 points.

My game roles
The game is played by 3 players.
The game starts in the first round, where each player places 2 settlements and 2 roads - the first player places 1 settlement and 1 road, then the second player places 1 settlement and 1 road, and then the third player places 2 settlements and 2 road, and then the second player places 1 settlement and 1 road, and then the first player places 1 settlement and 1 road. The last settlement that each player places give them the resources of the vertices that the settlement connects to.
Next, the game starts the normal rounds. Each player plays his turn can roll dice, build settlements, cities, roads, buy development cards, play development cards, and make trades. The player can use the development card before or after the dice roll, but when he uses the card, his turn ends.
When a player rolls the dice, the game gives resources to the players that have settlements or cities in the vertices that have the number rolled. if the sum of the dices is 7, a player that have more than 7 resources has to discard half of his resources.
there is 3 type of development cards:
Knight - if a player have 3 knights, he gets 2 victory points (a robber is not part of the game).
Victory Point - gives the player 1 victory point (he don't need to use the card to get the point).
Promotions cards - there are 3 types of promotions cards:
Road Building - the player can build 2 roads. when a player use the card, we ask him to give us 2 coordinates of the edges where he wants to build the roads.
Monopoly - the player can take all the resources of a specific type from all the players. when a player uses the card, we ask him to give us the type of the resource that he wants to take, and then we take the resources from all the players.
Year of Plenty - the player can take 2 resources of his choice. when a player uses the card, we ask him to give us 2 types of resources that he wants to get, and then we give him the resources.
player can trade with other players. The player can trade resource cards and development cards. The player can make a trade offer, and then the other players can accept or reject the offer.
How to run the game
Clone the repository.
Run the command make catan - the game should compile and run in the terminal.
How to play the game
The game run in the terminal, and for each step a menu will be displayed to the user. The user can choose the action that he wants to do by typing the number or character that is next to the action.

Vertex and Edge coordinates
The vertices and edges are represented by numbers. The vertices are represented by numbers from 0 to 53, and the edges are represented by numbers from 0 to 71. You can see the coordinates of the vertices and edges in the next images.

*/

#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"



//#include "catan.hpp"

using namespace std;

namespace ariel {

    class Vertex
    {   
        public:
            int number;
            string owner; 
            string type; // "settlement" or "city"
            vector<int> neighbors_edges;
            vector<int> neighbors_vertice;
    
            Vertex(int number)
            {
                this->number = number;
                this->type = "empty";
                this->owner = "none";
            }

           
    };


    class Edge
    {
        public:
            int number;
            string owner; 
            vector<int> neighbors_edges;
            vector<int> neighbors_vertice;

            Edge(int number)
            {
                this->number = number;
                this->owner = "none";
               
            }
    };

    class Tile
    {
        public:
            int number;
            string type; // "desert", "wood", "brick", "sheep", "wheat", "ore"
            vector<ariel::Edge> edges;
            vector<ariel::Vertex> vertices;

            
            //set default ctor
            Tile() = default;

            Tile (int number, string type)
            {
                this->number = number;
                this->type = type;
            }

            string getType()
            {
                return this->type;
            }

            friend ostream& operator<<(ostream& os, const Tile& t)
            {
                os << t.type << ","  << t.number;
                return os;
            }

    };

    class Board
    {
        private:
            vector<Vertex> vertices;
            vector<Edge> edges;
            vector<vector<Tile>> tiles;

        public:
            char getVertexState(int vertex);
            char getEdgeState(int edge);
            void setVertexState(int vertex, char state);
            void setEdgeState(int edge, char state);
            Board();
            void initializeVerticesNeighbors(); ///////---------------------------------
            void initializeEdgesNeighbors(); ///---------------------------------
            void assignVerticesAndEdgesToTiles();////-----------------------------
            ~Board();

            void initBoard();
            void placeSettlement(Vertex &v, Player &p);
            void placeRoad(Edge &e, Player &p);
            void placeCity(Vertex &v, Player &p);


            void printBoard();
            void printVertices();
            void printEdges();
            void printTiles();


    };





















} // namespace ariel
#endif // BOARD_HPP