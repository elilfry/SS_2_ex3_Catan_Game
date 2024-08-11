

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
        int number; //id
        string color ;
        
       
    
        
        
        public:
            vector<int> neighbors_edges;
            vector<int> neighbors_vertice;
            vector<int> tiles;
            
            Vertex(int number)
            {
                this->number = number;
                this->type = "empty";
                this->owner = "none";
            }

            string getOwner() const
            {
                return owner;
            }
            void setOwner(string newOwner)
            {
                owner = newOwner;
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
        
        void addTile(int tileId)
        {
        tiles.push_back(tileId);
        }

        string getColor() const
        {
            return color;
        }

        void setColor(string newColor)
        {
            this->color = newColor;
        }

           
    };


    class Edge
    {
        private:
            string owner;
            int number;
            string color ;

            

        public:
            
            vector<int> neighbors_edges;
            vector<int> neighbors_vertice;

            Edge(int number)
            {
                this->number = number;
                this->owner = "none";
               
            }

            string getOwner() const
            {
                return owner;
            }

            void setOwner(string newOwner)
            {
                owner = newOwner;
            }

            int getNumber() const
            {
                return number;
            }

            void setNumber(int newNumber)
            {
                number = newNumber;
            }

            string getColor() const
            {
                return color;
            }

            void setColor(string newColor)
            {
                this->color = newColor;
            }
    };

    class Tile
    {
        private:
        int number; // 2-12 the roll number
        int type; // "desert", "wood", "brick", "sheep", "wheat", "ore"
        int index; //id

        public:
            vector<int> edges;
            vector<int> vertices;

            
            
            Tile() = default;

            Tile (int number, int type,int index)
            {
                this->number = number;
                this->type = type;
                this->index = index;
            }
            int getIndex()
            {
                return this->index;
            }
            int getNumber()
            {
                return this->number;
            }
            

            int getType()
            {
                return this->type;
            }


            string getResourceType(int resource);
    };

    class Board
    {
        private:
            vector<Vertex> vertices;
            vector<Edge> edges;
            vector<vector<Tile>> tiles;
           
            void initializeVerticesNeighbors(); 
            void initializeEdgesNeighbors(); 
            void assignVerticesAndEdgesToTiles();
            

        public:
             

            Board();
            
            ~Board();

          

           
            bool placeSettlement(Player &p, int vertexId);
            bool placeRoad(Player &p, int edgeId);
            bool upgradeSettlementToCity(Player &p, int vertexId);

            string printVertex(Vertex &vertex);

            

            void distributeResources(Player &p, int sum);
            void intialDistributeResources(Player &p);
            
            Tile &getTile(int i);

            int getTileIndex(Tile &tile);

            Vertex &getVertex(int i);

            void printBoard();
            
            


    };





















} // namespace ariel

#endif // BOARD_HPP
