#include "board.hpp"

namespace ariel
{

    //vector <int> numbers = {2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 8 ,8 , 9 , 9 , 10 , 10 , 11 , 11 , 12}; //numbers for the tiles
    vector<int> numbers = {
        10, 2, 9,
        12, 6, 4, 10,
        9, 11, 0, 3, 8,
        8, 3, 4, 5,
        5, 6, 11
    };

    vector<string> resources = {
        "Ore", "Wool", "Wheat",
        "Wheat", "Brick", "Wood", "Wheat",
        "Brick", "Wool", "Desert", "Wood", "Ore",
        "Wheat", "Wood", "Wool", "Wood",
        "Brick", "Wheat", "Ore"
    };
    // Initialize the 2D vector of tiles with the appropriate layer sizes 3 4 5 4 3 
    // and fill it with the appropriate tiles.
vector<vector<Tile>> tiles = {
        vector<Tile>(3),
        vector<Tile>(4),
        vector<Tile>(5),
        vector<Tile>(4),
        vector<Tile>(3)
    };    

      


/*
Resources and Numbers Layout:
Top row: 10 (Stone), 2 (SHEEP), 9 (Wheat)
Second row: 12 (Wheat), 6 (Brick), 4 (Wood), 10 (Wheat)
Third row: 9 (Brick), 11 (SHEEP), Desert, 3 (Wood), 8 (Stone)
Fourth row: 8 (Wheat), 3 (Wood), 4 (SHEEP), 5 (Wood)
Bottom row: 5 (Brick), 6 (Wheat), 11 (Stone)
*/
    

    
    Board::Board()
    {

        // Initialize tiles with resources and numbers
        size_t resourceIndex = 0;
        size_t numberIndex = 0;
        for (size_t layer = 0; layer < tiles.size(); ++layer) {
            for (size_t i = 0; i < tiles[layer].size(); ++i) {
                if (resources[resourceIndex] == "Desert") {
                    tiles[layer][i] = Tile(0, "Desert"); // Desert tiles have no number
                } else {
                    tiles[layer][i] = Tile(numbers[numberIndex], resources[resourceIndex]);
                    ++numberIndex;
                }
                ++resourceIndex;
            }
        }
        
        // Initialize the board with 19 tiles.
        
        // Initialize the board with 54 vertices.
        cout << "Initializing vertices..." << endl;
        for(int i = 0; i < 54; i++)
        {
            vertices.push_back(Vertex(i));
        }
        cout << "Vertices initialized." << endl;
        initializeVerticesNeighbors(); // -------------------------------------------

        cout << "Initializing edges..." << endl;
        // Initialize the board with 72 edges.
        for(int i = 0; i < 72; i++)
        {
            edges.push_back(Edge(i));
        }
        initializeEdgesNeighbors(); // -------------------------------------------
        cout << "Edges initialized." << endl;
        // Assign vertices and edges to the tiles -------------------------------------------
        cout << "Assigning vertices and edges to tiles..." << endl;
        assignVerticesAndEdgesToTiles();// -------------------------------------------
        cout << "Vertices and edges assigned to tiles." << endl;
        // Initialize the neighbors of the vertices and edges. -------------------------------------------

    }
    Board::~Board() {    }         // Destructor implementation



// void Board::printBoard() {

//     for(int i=0;i<53;i++){
//          cout << "              " << vertices[0].number  << "       " << endl;
//     }


//     cout << "              " << vertices[0].number  << "       " << vertices[1].number << "       " << vertices[2].number << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "         (" << vertices[3].number << ") | " << tiles[0][0].getType() << "," << tiles[0][0].number << " | (" << vertices[4].number << ") | " << tiles[0][1].getType() << "," << tiles[0][1].number << " | (" << vertices[5].number << ") | " << tiles[0][2].getType() << "," << tiles[0][2].number << " | (" << vertices[6].number << ")" << endl;
//     cout << "               \\ /       \\ /       \\ /" << endl;
//     cout << "         (" << vertices[7].number << ")       (" << vertices[8].number << ")       (" << vertices[9].number << ")" << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "   (" << vertices[10].number << ") | " << tiles[1][0].getType() << "," << tiles[1][0].number << " | (" << vertices[11].number << ") | " << tiles[1][1].getType() << "," << tiles[1][1].number << " | (" << vertices[12].number << ") | " << tiles[1][2].getType() << "," << tiles[1][2].number << " | (" << vertices[13].number << ")" << endl;
//     cout << "               \\ /       \\ /       \\ /" << endl;
//     cout << "         (" << vertices[14].number << ")       (" << vertices[15].number << ")       (" << vertices[16].number << ")" << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "   (" << vertices[17].number << ") | " << tiles[2][0].getType() << "," << tiles[2][0].number << " | (" << vertices[18].number << ") | " << tiles[2][1].getType() << "," << tiles[2][1].number << " | (" << vertices[19].number << ") | " << tiles[2][2].getType() << "," << tiles[2][2].number << " | (" << vertices[20].number << ") | " << tiles[2][3].getType() << "," << tiles[2][3].number << " | (" << vertices[21].number << ")" << endl;
//     cout << "               \\ /       \\ /       \\ /" << endl;
//     cout << "         (" << vertices[22].number << ")       (" << vertices[23].number << ")       (" << vertices[24].number << ")" << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "   (" << vertices[25].number << ") | " << tiles[3][0].getType() << "," << tiles[3][0].number << " | (" << vertices[26].number << ") | " << tiles[3][1].getType() << "," << tiles[3][1].number << " | (" << vertices[27].number << ") | " << tiles[3][2].getType() << "," << tiles[3][2].number << " | (" << vertices[28].number << ") | " << tiles[3][3].getType() << "," << tiles[3][3].number << " | (" << vertices[29].number << ")" << endl;
//     cout << "               \\ /       \\ /       \\ /" << endl;
//     cout << "         (" << vertices[30].number << ")       (" << vertices[31].number << ")       (" << vertices[32].number << ")" << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "   (" << vertices[33].number << ") | " << tiles[4][0].getType() << "," << tiles[4][0].number << " | (" << vertices[34].number << ") | " << tiles[4][1].getType() << "," << tiles[4][1].number << " | (" << vertices[35].number << ") | " << tiles[4][2].getType() << "," << tiles[4][2].number << " | (" << vertices[36].number << ")" << endl;
//     cout << "               \\ /       \\ /       \\ /" << endl;
//     cout << "         (" << vertices[37].number << ")       (" << vertices[38].number << ")       (" << vertices[39].number << ")" << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "         (" << vertices[40].number << ")       (" << vertices[41].number << ")       (" << vertices[42].number << ")" << endl;
//     cout << "               / \\       / \\       / \\" << endl;
//     cout << "               (" << vertices[43].number << ")       (" << vertices[44].number << ")       (" << vertices[45].number << ")" << endl;
// }

    

     void Board::initializeVerticesNeighbors()
    {
        cout << "Initializing vertices neighbors..." << endl;
        // Manually setting neighbors based on a Catan-like hexagonal layout
        vertices[0].neighbors_vertice = {1, 8};
        vertices[1].neighbors_vertice = {0, 2};
        vertices[2].neighbors_vertice = {1, 3, 10};
        vertices[3].neighbors_vertice = {2, 4};
        vertices[4].neighbors_vertice = {3, 5, 12};
        vertices[5].neighbors_vertice = {4, 6};
        vertices[6].neighbors_vertice = {5, 14};
        vertices[7].neighbors_vertice = {8, 17};
        vertices[8].neighbors_vertice = {0, 7, 9};
        vertices[9].neighbors_vertice = {8, 10, 19};
        vertices[10].neighbors_vertice = {2, 9, 11};
        vertices[11].neighbors_vertice = {10, 12, 21};
        vertices[12].neighbors_vertice = {4, 11, 13};
        vertices[13].neighbors_vertice = {12, 14, 23};
        vertices[14].neighbors_vertice = {6, 13, 15};
        vertices[15].neighbors_vertice = {14, 25};
        vertices[16].neighbors_vertice = {17, 27};
        vertices[17].neighbors_vertice = {7, 16, 18};
        vertices[18].neighbors_vertice = {17, 19, 29};
        vertices[19].neighbors_vertice = {9, 18, 20};
        vertices[20].neighbors_vertice = {19, 21, 31};
        vertices[21].neighbors_vertice = {11, 20, 22};
        vertices[22].neighbors_vertice = {21, 23, 33};
        vertices[23].neighbors_vertice = {13, 22, 24};
        vertices[24].neighbors_vertice = {23, 25, 35};
        vertices[25].neighbors_vertice = {15, 24, 26};
        vertices[26].neighbors_vertice = {25, 37};
        vertices[27].neighbors_vertice = {16, 28};
        vertices[28].neighbors_vertice = {27, 29, 38};
        vertices[29].neighbors_vertice = {18, 28, 30};
        vertices[30].neighbors_vertice = {29, 31, 40};
        vertices[31].neighbors_vertice = {20, 30, 32};
        vertices[32].neighbors_vertice = {31, 33, 42};
        vertices[33].neighbors_vertice = {22, 32, 34};
        vertices[34].neighbors_vertice = {33, 35, 44};
        vertices[35].neighbors_vertice = {24, 34, 36};
        vertices[36].neighbors_vertice = {35, 37, 46};
        vertices[37].neighbors_vertice = {26, 36};
        vertices[38].neighbors_vertice = {28, 39};
        vertices[39].neighbors_vertice = {38, 40, 47};
        vertices[40].neighbors_vertice = {30, 39, 41};
        vertices[41].neighbors_vertice = {40, 42, 49};
        vertices[42].neighbors_vertice = {32, 41, 43};
        vertices[43].neighbors_vertice = {42, 44, 51};
        vertices[44].neighbors_vertice = {34, 43, 45};
        vertices[45].neighbors_vertice = {44, 46, 53};
        vertices[46].neighbors_vertice = {36, 45};
        vertices[47].neighbors_vertice = {39, 48};
        vertices[48].neighbors_vertice = {47, 49};
        vertices[49].neighbors_vertice = {41, 48, 50};
        vertices[50].neighbors_vertice = {49, 51};
        vertices[51].neighbors_vertice = {43, 50, 52};
        vertices[52].neighbors_vertice = {51, 53};
        vertices[53].neighbors_vertice = {45, 52};

        vertices[0].neighbors_edges = {0, 6};
        vertices[1].neighbors_edges = {0, 1};
        vertices[2].neighbors_edges = {1, 2, 7};
        vertices[3].neighbors_edges = {2, 3};
        vertices[4].neighbors_edges = {3, 4, 8};
        vertices[5].neighbors_edges = {4, 5};
        vertices[6].neighbors_edges = {5, 9};
        vertices[7].neighbors_edges = {10, 18};
        vertices[8].neighbors_edges = {6, 10, 11};
        vertices[12].neighbors_edges = {8, 14, 15};
        vertices[13].neighbors_edges = {15, 16, 21};
        vertices[14].neighbors_edges = {9, 16, 17};
        vertices[15].neighbors_edges = {17, 22};
        vertices[16].neighbors_edges = {23, 33};
        vertices[17].neighbors_edges = {18, 23, 24};
        vertices[18].neighbors_edges = {24, 25, 34};
        vertices[19].neighbors_edges = {19, 25, 26};
        vertices[20].neighbors_edges = {26, 27, 35};
        vertices[21].neighbors_edges = {20, 27, 28};
        vertices[22].neighbors_edges = {28, 29, 36};
        vertices[23].neighbors_edges = {21, 29, 30};
        vertices[24].neighbors_edges = {30, 31, 37};
        vertices[25].neighbors_edges = {22, 31, 32};
        vertices[26].neighbors_edges = {32, 38};
        vertices[27].neighbors_edges = {33, 39};
        vertices[28].neighbors_edges = {39, 40, 49};
        vertices[29].neighbors_edges = {34, 40, 41};
        vertices[30].neighbors_edges = {41, 42, 50};
        vertices[31].neighbors_edges = {35, 42, 43};
        vertices[32].neighbors_edges = {43, 44, 51};
        vertices[33].neighbors_edges = {36, 44, 45};
        vertices[34].neighbors_edges = {45, 46, 52};
        vertices[35].neighbors_edges = {37, 46, 47};
        vertices[36].neighbors_edges = {47, 48, 53};
        vertices[37].neighbors_edges = {38, 48};
        vertices[38].neighbors_edges = {49, 54};
        vertices[39].neighbors_edges = {54, 55, 62};
        vertices[40].neighbors_edges = {50, 55, 56};
        vertices[41].neighbors_edges = {56, 57, 63};
        vertices[42].neighbors_edges = {51, 57, 58};
        vertices[43].neighbors_edges = {58, 59, 64};
        vertices[44].neighbors_edges = {52, 59, 60};
        vertices[45].neighbors_edges = {60, 61, 65};
        vertices[46].neighbors_edges = {53, 61};
        vertices[47].neighbors_edges = {62, 66};
        vertices[48].neighbors_edges = {66, 67};
        vertices[49].neighbors_edges = {63, 67, 68};
        vertices[50].neighbors_edges = {68, 69};
        vertices[51].neighbors_edges = {64, 69, 70};
        vertices[52].neighbors_edges = {70, 71};
        vertices[53].neighbors_edges = {65, 71};
        cout << "Vertices neighbors initialized." << endl;
    }

    void Board::initializeEdgesNeighbors()
    {
        cout << "Initializing edges neighbors..." << endl; 
        edges[0].neighbors_vertice = {0, 1};
        edges[1].neighbors_vertice = {1, 2};
        edges[2].neighbors_vertice = {2, 3};
        edges[3].neighbors_vertice = {3, 4};
        edges[4].neighbors_vertice = {4, 5};
        edges[5].neighbors_vertice = {5, 6};
        edges[6].neighbors_vertice = {0, 8};
        edges[7].neighbors_vertice = {2, 10};
        edges[8].neighbors_vertice = {4, 12};
        edges[9].neighbors_vertice = {6, 14};
        edges[10].neighbors_vertice = {7, 8};
        edges[11].neighbors_vertice = {8, 9};
        edges[12].neighbors_vertice = {9, 10};
        edges[13].neighbors_vertice = {10, 11};
        edges[14].neighbors_vertice = {11, 12};
        edges[15].neighbors_vertice = {12, 13};
        edges[16].neighbors_vertice = {13, 14};
        edges[17].neighbors_vertice = {14, 15};
        edges[18].neighbors_vertice = {7, 17};
        edges[19].neighbors_vertice = {9, 19};
        edges[20].neighbors_vertice = {11, 21};
        edges[21].neighbors_vertice = {13, 23};
        edges[22].neighbors_vertice = {15, 25};
        edges[23].neighbors_vertice = {16, 17};

        edges[24].neighbors_vertice = {17, 18};
        edges[25].neighbors_vertice = {18, 19};
        edges[26].neighbors_vertice = {19, 20};
        edges[27].neighbors_vertice = {20, 21};
        edges[28].neighbors_vertice = {21, 22};
        edges[29].neighbors_vertice = {22, 23};
        edges[30].neighbors_vertice = {23, 24};
        edges[31].neighbors_vertice = {24, 25};
        edges[32].neighbors_vertice = {25, 26};
        edges[33].neighbors_vertice = {16, 27};
        edges[34].neighbors_vertice = {18, 29};
        edges[35].neighbors_vertice = {20, 31};
        edges[36].neighbors_vertice = {22, 33};
        edges[37].neighbors_vertice = {24, 35};
        edges[38].neighbors_vertice = {26, 37};
        edges[39].neighbors_vertice = {27, 28};
        edges[40].neighbors_vertice = {28, 29};
        edges[41].neighbors_vertice = {29, 30};
        edges[42].neighbors_vertice = {30, 31};
        edges[43].neighbors_vertice = {31, 32};
        edges[44].neighbors_vertice = {32, 33};
        edges[45].neighbors_vertice = {33, 34};
        edges[46].neighbors_vertice = {34, 35};
        edges[47].neighbors_vertice = {35, 36};
        edges[48].neighbors_vertice = {36, 37};
        edges[49].neighbors_vertice = {28, 38};
        edges[50].neighbors_vertice = {30, 40};
        edges[51].neighbors_vertice = {32, 42};
        edges[52].neighbors_vertice = {34, 44};
        edges[53].neighbors_vertice = {36, 46};
        edges[54].neighbors_vertice = {38, 39};
        edges[55].neighbors_vertice = {39, 40};
        edges[56].neighbors_vertice = {40, 41};
        edges[57].neighbors_vertice = {41, 42};
        edges[58].neighbors_vertice = {42, 43};
        edges[59].neighbors_vertice = {43, 44};
        edges[60].neighbors_vertice = {44, 45};
        edges[61].neighbors_vertice = {45, 46};
        edges[62].neighbors_vertice = {39, 47};
        edges[63].neighbors_vertice = {41, 49};
        edges[64].neighbors_vertice = {43, 51};
        edges[65].neighbors_vertice = {45, 53};
        edges[66].neighbors_vertice = {47, 48};
        edges[67].neighbors_vertice = {48, 49};
        edges[68].neighbors_vertice = {49, 50};
        edges[69].neighbors_vertice = {50, 51};
        edges[70].neighbors_vertice = {51, 52};
        edges[71].neighbors_vertice = {52, 53};

        edges[0].neighbors_edges = {1, 6};
        edges[1].neighbors_edges = {0, 2, 7};
        edges[2].neighbors_edges = {1, 3, 7};
        edges[3].neighbors_edges = {2, 4, 8};
        edges[4].neighbors_edges = {3, 5, 8};
        edges[5].neighbors_edges = {4, 9};
        edges[6].neighbors_edges = {0, 10, 11};
        edges[7].neighbors_edges = {1, 2, 11, 12};
        edges[8].neighbors_edges = {3, 4, 14, 15};
        edges[9].neighbors_edges = {5, 16, 17};
        edges[10].neighbors_edges = {6, 11, 18};
        edges[11].neighbors_edges = {6, 10, 12, 19};
        edges[12].neighbors_edges = {7, 11, 13, 19};
        edges[13].neighbors_edges = {7, 12, 14, 20};
        edges[14].neighbors_edges = {8, 13, 15, 20};
        edges[15].neighbors_edges = {8, 14, 16, 21};
        edges[16].neighbors_edges = {9, 15, 17, 21};
        edges[17].neighbors_edges = {9, 16, 22};
        edges[18].neighbors_edges = {10, 23, 24};
        edges[19].neighbors_edges = {11, 12, 25, 26};
        edges[20].neighbors_edges = {13, 14, 27, 28};
        edges[21].neighbors_edges = {15, 16, 29, 30};
        edges[22].neighbors_edges = {17, 31, 32};
        edges[23].neighbors_edges = {18, 24, 33};
        edges[24].neighbors_edges = {18, 23, 25, 34};
        edges[25].neighbors_edges = {19, 24, 26, 34};
        edges[26].neighbors_edges = {19, 25, 27, 35};
        edges[27].neighbors_edges = {20, 26, 28, 35};
        edges[28].neighbors_edges = {20, 27, 29, 36};
        edges[29].neighbors_edges = {21, 28, 30, 36};
        edges[30].neighbors_edges = {21, 29, 31, 37};
        edges[31].neighbors_edges = {22, 30, 32, 37};
        edges[32].neighbors_edges = {22, 31, 38};
        edges[33].neighbors_edges = {23, 39};
        edges[34].neighbors_edges = {24, 25, 40, 41};
        edges[35].neighbors_edges = {26, 27, 42, 43};
        edges[36].neighbors_edges = {28, 29, 44, 45};
        edges[37].neighbors_edges = {30, 31, 46, 47};
        edges[38].neighbors_edges = {32, 48};
        edges[39].neighbors_edges = {33, 40, 49};
        edges[40].neighbors_edges = {34, 39, 41, 49};
        edges[41].neighbors_edges = {34, 40, 42, 50};
        edges[42].neighbors_edges = {35, 41, 43, 50};
        edges[43].neighbors_edges = {35, 42, 44, 51};
        edges[44].neighbors_edges = {36, 43, 45, 51};
        edges[45].neighbors_edges = {36, 44, 46, 52};
        edges[46].neighbors_edges = {37, 45, 47, 52};
        edges[47].neighbors_edges = {37, 46, 48, 53};
        edges[48].neighbors_edges = {38, 47, 53};
        edges[49].neighbors_edges = {39, 40, 54};
        edges[50].neighbors_edges = {41, 42, 55, 56};
        edges[51].neighbors_edges = {43, 44, 57, 58};
        edges[52].neighbors_edges = {45, 46, 59, 60};
        edges[53].neighbors_edges = {47, 48, 61};
        edges[54].neighbors_edges = {49, 55, 62};
        edges[55].neighbors_edges = {50, 54, 56, 62};
        edges[56].neighbors_edges = {50, 55, 57, 63};
        edges[57].neighbors_edges = {51, 56, 58, 63};
        edges[58].neighbors_edges = {51, 57, 59, 64};
        edges[59].neighbors_edges = {52, 58, 60, 64};
        edges[60].neighbors_edges = {52, 59, 61, 65};
        edges[61].neighbors_edges = {53, 60, 65};
        edges[62].neighbors_edges = {54, 55, 66};
        edges[63].neighbors_edges = {56, 57, 67, 68};
        edges[64].neighbors_edges = {58, 59, 69, 70};
        edges[65].neighbors_edges = {60, 61, 71};
        edges[66].neighbors_edges = {62, 67};
        edges[67].neighbors_edges = {63, 66, 68};
        edges[68].neighbors_edges = {63, 67, 69};
        edges[69].neighbors_edges = {64, 68, 70};
        edges[70].neighbors_edges = {64, 69, 71};
        edges[71].neighbors_edges = {65, 70};
        cout << "Edges neighbors initialized." << endl;
    }

void Board::assignVerticesAndEdgesToTiles() {
    // Ensure vertexIndices and edgeIndices are properly defined and populated
    vector<vector<int>> vertexIndices = {
        {0, 1, 2, 8, 9, 10}, {2, 3, 4, 10, 11, 12}, {4, 5, 6, 12, 13, 14},
        {7, 8, 9, 17, 18, 19}, {9, 10, 11, 19, 20, 21}, {11, 12, 13, 21, 22, 23}, {13, 14, 15, 23, 24, 25},
        {16, 17, 18, 27, 28, 29}, {18, 19, 20, 29, 30, 31}, {20, 21, 22, 31, 32, 33}, {22, 23, 24, 33, 34, 35}, {24, 25, 26, 35, 36, 37},
        {28, 29, 30, 38, 39, 40}, {30, 31, 32, 40, 41, 42}, {32, 33, 34, 42, 43, 44}, {34, 35, 36, 44, 45, 46},
        {39, 40, 41, 47, 48, 49}, {41, 42, 43, 49, 50, 51}, {43, 44, 45, 51, 52, 53}
    };

    vector<vector<int>> edgeIndices = {
        {0, 1, 6, 7, 11, 12}, {2, 3, 7, 8, 13, 14}, {4, 5, 8, 9, 15, 16},
        {10, 11, 18, 19, 24, 25}, {12, 13, 19, 20, 26, 27}, {14, 15, 20, 21, 28, 29}, {16, 17, 21, 22, 30, 31},
        {23, 24, 33, 34, 39, 40}, {25, 26, 34, 35, 41, 42}, {27, 28, 35, 36, 43, 44}, {29, 30, 36, 37, 45, 46}, {31, 32, 37, 38, 47, 48},
        {40, 41, 49, 50, 54, 55}, {42, 43, 50, 51, 56, 57}, {44, 45, 51, 52, 58, 59}, {46, 47, 52, 53, 60, 61},
        {55, 56, 62, 63, 66, 67}, {57, 58, 63, 64, 68, 69}, {59, 60, 64, 65, 70, 71}
    };

    size_t tileIndex = 0;
    for (size_t layer = 0; layer < tiles.size(); ++layer) {
        for (size_t i = 0; i < tiles[layer].size(); ++i, ++tileIndex) {
            Tile &tile = tiles[layer][i];

            // Assign vertices
            for (int vertexIndex : vertexIndices[tileIndex]) {
                if (vertexIndex < 0 || vertexIndex >= vertices.size()) {
                    std::cerr << "Invalid vertex index " << vertexIndex << " for tile " << tileIndex << std::endl;
                    exit(EXIT_FAILURE);
                }
                tile.vertices.push_back(vertices[(size_t)vertexIndex]);
            }

            // Assign edges
            for (int edgeIndex : edgeIndices[tileIndex]) {
                if (edgeIndex < 0 || edgeIndex >= edges.size()) {
                    std::cerr << "Invalid edge index " << edgeIndex << " for tile " << tileIndex << std::endl;
                    exit(EXIT_FAILURE);
                }
                tile.edges.push_back(edges[(size_t)edgeIndex]);
            }
        }
    }

    cout << "Vertices and edges assigned to tiles." << std::endl;
}


    // void Board::assignVerticesAndEdgesToTiles() {
    //     size_t vertex_index = 0;
    //     size_t edge_index = 0;

    //     // Manually assigning vertices and edges to each tile based on a Catan-like hexagonal layout
    //        // Loop through each layer and assign vertices and edges to the tiles
    //             int layer_size[] = {3, 4, 5, 4, 3}; // The number of tiles in each layer
    //             for (size_t layer = 0; layer < 5; ++layer) {
    //                 for (size_t i = 0; i < layer_size[layer]; ++i) {
    //                     Tile& tile = tiles[layer][i];
        
    //                     tile.vertices.push_back(vertices[vertex_index]);
    //                     tile.vertices.push_back(vertices[vertex_index + 1]);
    //                     tile.vertices.push_back(vertices[vertex_index + 2]);
        
    //                     tile.edges.push_back(edges[edge_index]);
    //                     tile.edges.push_back(edges[edge_index + 1]);
    //                     tile.edges.push_back(edges[edge_index + 2]);
        
    //                     vertex_index += 2;
    //                     edge_index += 3;
    //                 }
    //             }
    //             cout << "Vertices and edges  finish assigned to tiles." << endl;
    //         }
       
// void Board::assignVerticesAndEdgesToTiles()
//     {
//         cout << "Assigning vertices and edges to tiles..." << endl;
//         // Manually assigning vertices to each tile based on a hexagonal layout
//         tiles[0][0].vertices = {0, 1, 2, 8, 9, 10};
//         tiles[0][1].vertices = {2, 3, 4, 10, 11, 12};
//         tiles[0][2].vertices = {4, 5, 6, 12, 13, 14};
//         tiles[1][0].vertices = {7, 8, 9, 17, 18, 19};
//         tiles[1][1].vertices = {9, 10, 11, 19, 20, 21};
//         tiles[1][2].vertices = {11, 12, 13, 21, 22, 23};
//         tiles[1][3].vertices = {13, 14, 15, 23, 24, 25};
//         tiles[2][0].vertices = {16, 17, 18, 27, 28, 29};
//         tiles[2][1].vertices = {18, 19, 20, 29, 30, 31};
//         tiles[2][2].vertices = {20, 21, 22, 31, 32, 33};
//         tiles[2][3].vertices = {22, 23, 24, 33, 34, 35};
//         tiles[2][4].vertices = {24, 25, 26, 35, 36, 37};
//         tiles[3][0].vertices = {28, 29, 30, 38, 39, 40};
//         tiles[3][1].vertices = {30, 31, 32, 40, 41, 42};
//         tiles[3][2].vertices = {32, 33, 34, 42, 43, 44};
//         tiles[3][3].vertices = {34, 35, 36, 44, 45, 46};
//         tiles[4][0].vertices = {39, 40, 41, 47, 48, 49};
//         tiles[4][1].vertices = {41, 42, 43, 49, 50, 51};
//         tiles[4][2].vertices = {43, 44, 45, 51, 52, 53};

//         // Manually assigning edges to each tile based on a hexagonal layout
//         tiles[0][0].edges = {0, 1, 6, 7, 11, 12};
//         tiles[0][1].edges = {2, 3, 7, 8, 13, 14};
//         tiles[0][2].edges = {4, 5, 8, 9, 15, 16};
//         tiles[1][0].edges = {10, 11, 18, 19, 24, 25};
//         tiles[1][1].edges = {12, 13, 19, 20, 26, 27};
//         tiles[1][2].edges = {14, 15, 20, 21, 28, 29};
//         tiles[1][3].edges = {16, 17, 21, 22, 30, 31};
//         tiles[2][0].edges = {23, 24, 33, 34, 39, 40};
//         tiles[2][1].edges = {25, 26, 34, 35, 41, 42};
//         tiles[2][2].edges = {27, 28, 35, 36, 43, 44};
//         tiles[2][3].edges = {29, 30, 36, 37, 45, 46};
//         tiles[2][4].edges = {31, 32, 37, 38, 47, 48};
//         tiles[3][0].edges = {40, 41, 49, 50, 54, 55};
//         tiles[3][1].edges = {42, 43, 50, 51, 56, 57};
//         tiles[3][2].edges = {44, 45, 51, 52, 58, 59};
//         tiles[3][3].edges = {46, 47, 52, 53, 60, 61};
//         tiles[4][0].edges = {55, 56, 62, 63, 66, 67};
//         tiles[4][1].edges = {57, 58, 63, 64, 68, 69};
//         tiles[4][2].edges = {59, 60, 64, 65, 70, 71};
//         cout << "Vertices and edges assigned to tiles." << endl;
//     }

} // namespace ariel    