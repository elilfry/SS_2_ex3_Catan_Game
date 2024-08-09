#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include <iostream>
#include <sstream>

using namespace ariel;
using namespace std;


TEST_CASE("Board Tests")
{
    Board board;
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");

    SUBCASE("Test placeSettlement")
    {
        bool flag = board.placeSettlement(p1, 9);
        CHECK(flag);
        CHECK(board.getVertex(9).getOwner() == "Alice");

        flag = board.placeSettlement(p1, 9);
        CHECK(!flag); // Cannot place another settlement on the same vertex

        flag = board.placeSettlement(p2, 9);
        CHECK(!flag); // Cannot place another settlement on the same vertex

        flag = board.placeSettlement(p2, 10);
        CHECK(!flag); // Cannot place a settlement new to another settlement


    }

    SUBCASE("Test placeRoad")
    {
        board.placeSettlement(p1, 9);
        bool flag = board.placeRoad(p1, 9);
        CHECK(flag);
        //CHECK(board.getEdge(9).getOwner() == "Alice");

        flag = board.placeRoad(p1, 9);
        CHECK(!flag); // Cannot place another road on the same edge

        flag = board.placeRoad(p2, 9);
        CHECK(!flag); // Cannot place a road on an edge with another player's settlement

        flag = board.placeRoad(p2, 10);
        CHECK(!flag); // Cannot place a road on an edge with no settlement
    }






}
// TEST_CASE("Player Tests") {
//     Player player("Eli");

//     SUBCASE("Test getName") {
//         CHECK(player.getName() == "Eli");
//     }

//     SUBCASE("Test addResource") {
//         player.addResource(WOOD, 2);
//         CHECK(player.getResource(WOOD) == 2);
//     }

//     SUBCASE("Test removeResource") {
//         player.addResource(WOOD, 2);
//         player.removeResource(WOOD, 1);
//         CHECK(player.getResource(WOOD) == 1);
//     }

//     SUBCASE("Test getTotalResources") {
//         player.addResource(WOOD, 2);
//         player.addResource(BRICK, 3);
//         CHECK(player.getTotalResources() == 5);
//     }

//     SUBCASE("Test sumIs7") {
//         player.addResource(WOOD, 10);
//         player.sumIs7();
//         CHECK(player.getResource(WOOD) == 5);
//     }
// }

// TEST_CASE("Board Tests") {
//     Board board;
//     Player player("Eli");

//     SUBCASE("Test placeSettlement") {
//         bool success = board.placeSettlement(player, 0);
//         CHECK(success);
//         CHECK(board.getVertex(0).getOwner() == "Eli");

//         success = board.placeSettlement(player, 0);
//         CHECK(!success);  // Cannot place another settlement on the same vertex
//     }

//     SUBCASE("Test placeRoad") {
//         board.placeSettlement(player, 0);
//         bool success = board.placeRoad(player, 0);
//         CHECK(success);
//         CHECK(board.getEdge(0).getOwner() == "Eli");
//     }

//     SUBCASE("Test upgradeSettlementToCity") {
//         board.placeSettlement(player, 0);
//         bool success = board.upgradeSettlementToCity(player, 0);
//         CHECK(!success);  // Not enough resources

//         player.addResource(WHEAT, 2);
//         player.addResource(IRON, 3);
//         success = board.upgradeSettlementToCity(player, 0);
//         CHECK(success);
//         CHECK(board.getVertex(0).getType() == "city");
//     }

//     SUBCASE("Test distributeResources") {
//         board.placeSettlement(player, 0);
//         player.addResource(WHEAT, 2);
//         player.addResource(IRON, 3);
//         board.upgradeSettlementToCity(player, 0);

//         board.distributeResources(player, 10);
//         CHECK(player.getResource(IRON) == 5);  // Received 2 IRON from the city on tile with number 10
//     }
// }

// TEST_CASE("Catan Tests") {
//     Player p1("Eli"), p2("Meni"), p3("Chen");
//     Catan game(p1, p2, p3);

//     SUBCASE("Test ChooseStartingPlayer") {
//         game.ChooseStartingPlayer();
//         CHECK((game.getCurrentPlayer().getName() == "Eli" ||
//                game.getCurrentPlayer().getName() == "Meni" ||
//                game.getCurrentPlayer().getName() == "Chen"));
//     }

//     SUBCASE("Test nextPlayer") {
//         game.ChooseStartingPlayer();
//         string initialPlayer = game.getCurrentPlayer().getName();
//         game.nextPlayer();
//         CHECK(game.getCurrentPlayer().getName() != initialPlayer);
//     }

//     SUBCASE("Test placeSettlement and placeRoad") {
//         game.ChooseStartingPlayer();
//         Player &currentPlayer = game.getCurrentPlayer();
//         Board &board = game.getBoard();

//         game.placeSettlement(currentPlayer, board);
//         CHECK(currentPlayer.getPoints() == 1);

//         game.placeRoad(currentPlayer, board);
//         CHECK(currentPlayer.getRoadsNum() == 1);
//     }

//     SUBCASE("Test rollDice") {
//         game.ChooseStartingPlayer();
//         Board &board = game.getBoard();
//         game.rollDice(board);
//     }

//     SUBCASE("Test buyDevelopmentCard") {
//         game.ChooseStartingPlayer();
//         Player &currentPlayer = game.getCurrentPlayer();
//         currentPlayer.addResource(WHEAT, 1);
//         currentPlayer.addResource(IRON, 1);
//         currentPlayer.addResource(SHEEP, 1);

//         game.buyDevelopmentCard(currentPlayer);
//         CHECK(currentPlayer.getDevCardsSum() == 1);
//     }

//     SUBCASE("Test playDevelopmentCard") {
//         game.ChooseStartingPlayer();
//         Player &currentPlayer = game.getCurrentPlayer();
//         currentPlayer.addDevCard("Knight");
//         CHECK(currentPlayer.getDevCardsSum() == 1);

//         game.playDevelopmentCard(currentPlayer);
//         CHECK(currentPlayer.getDevCardsSum() == 0); // Assuming the playDevelopmentCard function decreases the count
//     }
// }


// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"
// #include "player.hpp"
// #include "board.hpp"
// #include "catan.hpp"
// #include "devcard.hpp"

// using namespace ariel;

// void initGame()
//     {
//         Player p1("Alice"), p2("Bob"), p3("Charlie");
//         Catan catan(p1, p2, p3);
//         Board &board = catan.getBoard();
//         board.printBoard();

//         catan.ChooseStartingPlayer();

//         cout << "first round" << endl;

//         for(int i = 0; i < 3; i++)
//         {
//             cout << "\n Player " << catan.getCurrentPlayer().getName() << " turn. 1st Settelment" << endl;
//             bool flag = board.placeSettlement(catan.getCurrentPlayer(), 9);
//             CHECK(flag == true);
//         }


//     }

// // TEST_SUITE("Catan Game Tests") {

// //     TEST_CASE("Player Initialization") {
// //         Player p1("Alice");
// //         CHECK(p1.getName() == "Alice");
// //         CHECK(p1.getPoints() == 0);
// //         CHECK(p1.getTotalResources() == 0);
// //     }

// //     TEST_CASE("Resource Management") {
// //         Player p2("Bob");
// //         p2.addResource(WOOD, 5);
// //         CHECK(p2.getResource(WOOD) == 5);
// //         p2.removeResource(WOOD, 3);
// //         CHECK(p2.getResource(WOOD) == 2);

// //         SUBCASE("Attempting to remove more resources than available") {
// //             p2.removeResource(WOOD, 4);
// //             CHECK(p2.getResource(WOOD) == 2);  // Should not change due to error
// //         }
// //     }

// //     TEST_CASE("Board Setup and Operations") {
// //         Board board;
// //         CHECK(board.getVertex(0).getOwner() == "none");

// //         Player p1("Alice");
// //         p1.addResource(WOOD, 1);
// //         p1.addResource(BRICK, 1);
// //         board.placeRoad(p1, 1);  
// //         CHECK(p1.getRoadsNum() == 1);
// //     }

// //     TEST_CASE("Game Flow and Player Interactions") {
// //         Player p1("Alice"), p2("Bob"), p3("Charlie");
// //         Catan game(p1, p2, p3);
// //         game.ChooseStartingPlayer();

// //         SUBCASE("Initial resource distribution") {
// //             game.intialResources(game.getBoard());
// //             CHECK(p1.getTotalResources() > 2); // 
// //         }

// //         SUBCASE("Building Settlements and Roads") {
// //             // Assuming player has necessary resources to build
// //             p1.addResource(WOOD, 1);
// //             p1.addResource(BRICK, 1);
// //             p1.addResource(WHEAT, 1);
// //             p1.addResource(SHEEP, 1);
// //             game.placeSettlement(p1, game.getBoard());
// //             game.placeRoad(p1, game.getBoard());
// //             CHECK(p1.getPoints() == 1);  // Points should increase from placing a settlement
// //             CHECK(p1.getRoadsNum() == 1);
// //         }
// //     }

// //     TEST_CASE("Development Card Functionality") {
// //         Player p4("Dana");
// //         p4.addResource(WHEAT, 1);
// //         p4.addResource(SHEEP, 1);
// //         p4.addResource(IRON, 1);
// //         Catan game(p4, p4, p4);  // Dummy setup for testing

// //         game.buyDevelopmentCard(p4);
// //         CHECK(p4.getDevCardsSum() == 1); // Assuming a card is successfully bought

// //         SUBCASE("Playing Development Cards") {
// //             if (p4.getKnightsNum() > 0) {
// //                 // Knight specific logic, if applicable
// //             }
// //         }
// //     }

// //     TEST_CASE("Trade Functionality") {
// //         Player p1("Alice"), p2("Bob");
// //         p1.addResource(WOOD, 5);
// //         p2.addResource(BRICK, 5);

// //         // Set up trade where p1 gives 3 wood for 3 brick from p2
// //         p1.tradeResources(p2, WOOD, 3, BRICK, 3);
// //         CHECK(p1.getResource(WOOD) == 2);
// //         CHECK(p2.getResource(BRICK) == 2);
// //         CHECK(p1.getResource(BRICK) == 3);
// //         CHECK(p2.getResource(WOOD) == 3);
// //     }
// // }

