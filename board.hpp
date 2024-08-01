

#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"
#define WOOD 0
#define BRICK 1
#define SHEEP 2
#define WHEAT 3
#define IRON 4
#define DESERT -1


//#include "catan.hpp"

using namespace std;

namespace ariel {

    class Vertex
    {   
        
        private:
        string owner;
        string type; // "settlement" or "city"
        int number;
        
        
        
        public:
            
            vector<int> neighbors_edges;
            vector<int> neighbors_vertice;
    
            Vertex(int number)
            {
                this->number = number;
                this->type = "empty";
                this->owner = "none";
            }

            string getOwner() const
            {
                return this->owner;
            }
            void setOwner(string newOwner)
            {
                this->owner = newOwner;
            }
            string getType() const
            {
                return this->type;
            }
            void setType(const string newType)
        {
            type = newType;
        }
        int getNumber() const
        {
            return number;
        }

        void setNumber(int newNumber)
        {
            number = newNumber;
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
        private:
        int number;
        int type; // "desert", "wood", "brick", "sheep", "wheat", "ore"

        public:
            vector<ariel::Edge> edges;
            vector<ariel::Vertex> vertices;

            
            //set default ctor
            Tile() = default;

            Tile (int number, int type)
            {
                this->number = number;
                this->type = type;
            }

            int getNumber()
            {
                return this->number;
            }
            

            int getType()
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
         
            Board();
            void initializeVerticesNeighbors(); ///////---------------------------------
            void initializeEdgesNeighbors(); ///---------------------------------
            void assignVerticesAndEdgesToTiles();////-----------------------------
            ~Board();

            //void initBoard();
            bool placeSettlement(Player &p, int vertexId);
            bool placeRoad(Player &p, int edgeId);
            bool upgradeSettlementToCity(Player &p, int vertexId);
            
            string printVertex(Vertex vertex);
            // void placeCity(Vertex &v, Player &p);

            void distributeResources(Player &p, int sum);
            Tile &getTile(int i);

            Vertex &getVertex(int i);

            void printBoard();
            // void printVertices();
            // void printEdges();
            // void printTiles();


    };





















} // namespace ariel

#endif // BOARD_HPP
