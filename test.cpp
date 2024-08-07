// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"
// #include "player.hpp"
// #include "board.hpp"
// #include "catan.hpp"
// #include "devcard.hpp"

// using namespace ariel;

// TEST_SUITE("Catan Game Tests") {

//     TEST_CASE("Player Initialization") {
//         Player p1("Alice");
//         CHECK(p1.getName() == "Alice");
//         CHECK(p1.getPoints() == 0);
//         CHECK(p1.getTotalResources() == 0);
//     }

//     TEST_CASE("Resource Management") {
//         Player p2("Bob");
//         p2.addResource(WOOD, 5);
//         CHECK(p2.getResource(WOOD) == 5);
//         p2.removeResource(WOOD, 3);
//         CHECK(p2.getResource(WOOD) == 2);

//         SUBCASE("Attempting to remove more resources than available") {
//             p2.removeResource(WOOD, 4);
//             CHECK(p2.getResource(WOOD) == 2);  // Should not change due to error
//         }
//     }

//     TEST_CASE("Board Setup and Operations") {
//         Board board;
//         CHECK(board.getVertex(0).getOwner() == "none");

//         Player p1("Alice");
//         p1.addResource(WOOD, 1);
//         p1.addResource(BRICK, 1);
//         board.placeRoad(p1, 1);  
//         CHECK(p1.getRoadsNum() == 1);
//     }

//     TEST_CASE("Game Flow and Player Interactions") {
//         Player p1("Alice"), p2("Bob"), p3("Charlie");
//         Catan game(p1, p2, p3);
//         game.ChooseStartingPlayer();

//         SUBCASE("Initial resource distribution") {
//             game.intialResources(game.getBoard());
//             CHECK(p1.getTotalResources() > 2); // 
//         }

//         SUBCASE("Building Settlements and Roads") {
//             // Assuming player has necessary resources to build
//             p1.addResource(WOOD, 1);
//             p1.addResource(BRICK, 1);
//             p1.addResource(WHEAT, 1);
//             p1.addResource(SHEEP, 1);
//             game.placeSettlement(p1, game.getBoard());
//             game.placeRoad(p1, game.getBoard());
//             CHECK(p1.getPoints() == 1);  // Points should increase from placing a settlement
//             CHECK(p1.getRoadsNum() == 1);
//         }
//     }

//     TEST_CASE("Development Card Functionality") {
//         Player p4("Dana");
//         p4.addResource(WHEAT, 1);
//         p4.addResource(SHEEP, 1);
//         p4.addResource(IRON, 1);
//         Catan game(p4, p4, p4);  // Dummy setup for testing

//         game.buyDevelopmentCard(p4);
//         CHECK(p4.getDevCardsSum() == 1); // Assuming a card is successfully bought

//         SUBCASE("Playing Development Cards") {
//             if (p4.getKnightsNum() > 0) {
//                 // Knight specific logic, if applicable
//             }
//         }
//     }

//     TEST_CASE("Trade Functionality") {
//         Player p1("Alice"), p2("Bob");
//         p1.addResource(WOOD, 5);
//         p2.addResource(BRICK, 5);

//         // Set up trade where p1 gives 3 wood for 3 brick from p2
//         p1.tradeResources(p2, WOOD, 3, BRICK, 3);
//         CHECK(p1.getResource(WOOD) == 2);
//         CHECK(p2.getResource(BRICK) == 2);
//         CHECK(p1.getResource(BRICK) == 3);
//         CHECK(p2.getResource(WOOD) == 3);
//     }
// }

// // Additional cases can include error handling for invalid operations,
// // and complex game scenarios like a complete game with multiple actions.
