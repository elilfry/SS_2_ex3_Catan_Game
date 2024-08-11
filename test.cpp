#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include <iostream>
#include <sstream>

using namespace ariel;
using namespace std;


TEST_CASE("Test placeSettlement")
{
    Board board;
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");

    // Test placeSettlement-first 2 rounds
      
        //test case 1: Successfully place a settlement on a free vertex

        bool flag = board.placeSettlement(p1, 0);
        CHECK(flag);
        // board.placeRoad(p1, 0);
        // board.placeRoad(p1, 1);

        // Test Case 2: Place a settlement on an already occupied vertex
        flag = board.placeSettlement(p1, 0);
        CHECK(!flag); // Cannot place another settlement on the same vertex

        // Test Case 3: Place a settlement on a vertex near to another settlement
        flag = board.placeSettlement(p2, 1);
        CHECK(!flag); // Cannot place a settlement near to another settlement

        // Test Case 4: Place a settlement on a non-existent vertex
        flag = board.placeSettlement(p3, 100);
        CHECK(!flag); // Cannot place a settlement on a non-existent vertex

    //Test placeSettlement- normal rounds
        board.placeRoad(p1, 0);
        p1.addPoints(2);

        //test 1:  Attempt to place a settlement next to another settlement without the proper spacing
        flag = board.placeSettlement(p1, 1);
        CHECK(!flag);

        //test 2:  Place a settlement connected to an owned road
        board.placeRoad(p1, 1);      
        flag = board.placeSettlement(p1,2);  
        CHECK(flag);

        // //test 3 : valid placement of settlement
        // board.placeRoad(p1,2);
        // CHECK(board.placeSettlement(p1,3));

        //test 4:out of bounds placement
        flag = board.placeSettlement(p1, 100);
        CHECK(!flag);
        // Test Case 5: Place settlement without an adjacent road 
        flag = board.placeSettlement(p1, 4);
        CHECK(!flag);
    
    }

TEST_CASE("Test placeRoad") {
    Board board;
    Player p1("Alice");
    Player p2("Bob");

    // Test Case 1: Successfully place a road connected to a settlement
    CHECK(board.placeSettlement(p1, 0)); // Place a settlement first
    CHECK(board.placeRoad(p1, 0)); // Place a road connected to the settlement

    // Test Case 2: Place a road on an already occupied edge
    CHECK(!board.placeRoad(p2, 0)); // Edge is already occupied by p1

    // Test Case 3: Place a road on an edge that has no adjacent settlement or road owned by the player
    CHECK(!board.placeRoad(p1, 10)); // No adjacent settlement or road for p1 on edge 10

    // Test Case 4: Successfully place a road connected to another road owned by the player
    CHECK(board.placeRoad(p1, 1)); // Edge 1 is adjacent to edge 0, which is owned by p1

    // Test Case 5: cannot place more then 2 roads without a settlement
    CHECK(!(board.placeRoad(p1, 2))); 

    // Test Case 5: Place a road on a non-existent edge
    CHECK(!board.placeRoad(p1, 100)); // Edge 100 is out of bounds

    // Test Case 7: Place a road on a valid edge with adjacent road but no adjacent settlement owned by the player
    CHECK(!board.placeRoad(p2, 1)); // Edge 1 is adjacent to edge 0, but no adjacent settlement owned by p2
}

TEST_CASE("Test upgradeSettlementToCity") {
    Board board;
    Player p1("Alice");
    Player p2("Bob");

    // Test Case 1: Successful upgrade of a settlement to a city
    board.placeSettlement(p1, 10);
    bool flag = board.upgradeSettlementToCity(p1, 10);
    CHECK(flag); 
    CHECK(board.getVertex(10).getType() == "city"); // The vertex should now be a city

    // Test Case 2: Attempt to upgrade a settlement that doesn't belong to the player
    board.placeSettlement(p2, 20);
    flag = board.upgradeSettlementToCity(p1, 20);
    CHECK(!flag); // Should fail since the settlement doesn't belong to p1

    // Test Case 3: Attempt to upgrade a non-existent vertex
    flag = board.upgradeSettlementToCity(p1, 100);
    CHECK(!flag); // Should fail due to invalid vertex index

    // Test Case 4: Attempt to upgrade a vertex that is not a settlement
    flag = board.upgradeSettlementToCity(p1, 10); // 10 is already a city
    CHECK(!flag); // Should fail because it's already a city

    // Test Case 5: Attempt to upgrade an empty vertex
    flag = board.upgradeSettlementToCity(p1, 15);
    CHECK(!flag); // Should fail because there's no settlement on the vertex
}

TEST_CASE("Test getTile") {
    Board board;

    // Test valid tile indices
    CHECK_NOTHROW(board.getTile(0));
    CHECK_NOTHROW(board.getTile(10));
    CHECK_NOTHROW(board.getTile(18));

    // Test invalid tile indices
    CHECK_THROWS_AS(board.getTile(-1), std::invalid_argument);
    CHECK_THROWS_AS(board.getTile(19), std::invalid_argument);
}

TEST_CASE("Test distributeResources") {
    Board board;
    Player p1("Alice");
    Player p2("Bob");

    // Place settlements for players
    board.placeSettlement(p1, 10);
    board.placeSettlement(p2, 14);

    // Test resource distribution for dice roll 9 (tiles at index 2, 6,)
    
    board.distributeResources(p1, 9);
    board.distributeResources(p2, 9);

    CHECK(p1.getResource(WOOD) == 0);  // Player 1 should get 0 wood (tile 2)
    CHECK(p2.getResource(WOOD) == 1);  // Player 2 should get 1 wood

    // Test resource distribution for dice roll 8 (tiles at index 10, 14)
    
    board.distributeResources(p1, 10);
    board.distributeResources(p2, 10);

    CHECK(p1.getResource(IRON) == 1);  // Player 1 should get 1 Iron
    CHECK(p2.getResource(IRON) == 0);  // Player 2 should get 0 Iron (tile 0)
}

TEST_CASE("Test intialDistributeResources") {
    Board board;
    Player p1("Alice");

    // Place settlements for the player
    board.placeSettlement(p1, 10);
    board.placeSettlement(p1, 24);

    // Initial resource distribution
    board.intialDistributeResources(p1);

    CHECK(p1.getResource(WOOD) == 1);  // 1 Wood from tiles 11 
    CHECK(p1.getResource(BRICK) == 2);  // 1 Brick from tile 4 and 6
    CHECK(p1.getResource(WHEAT) == 0); 
    CHECK(p1.getResource(SHEEP) == 1);  // 1 Sheep from tile 1
    CHECK(p1.getResource(IRON) == 2);// 2 iron from tile 0 tile 12
}






////////////////////////////////////////// player //////////////////////////////////////////////////////////////////////////////////////////////////////







TEST_CASE("Test addPoints and getPoints") {
    Player p1("Alice");

    // Initial points should be 0
    CHECK(p1.getPoints() == 0);

    // Add points and check
    p1.addPoints(2);
    CHECK(p1.getPoints() == 2);

    p1.addPoints(3);
    CHECK(p1.getPoints() == 5);
}






TEST_CASE("Test addResource, removeResource, and getResource") {
    Player p1("Bob");

    // Initially, all resources should be 0
    for (int i = 0; i < 5; i++) {
        CHECK(p1.getResource(i) == 0);
    }

    // Add resources and check
    p1.addResource(WOOD, 3);
    p1.addResource(BRICK, 2);
    CHECK(p1.getResource(WOOD) == 3);
    CHECK(p1.getResource(BRICK) == 2);

    // Remove resources and check
    p1.removeResource(WOOD, 1);
    p1.removeResource(BRICK, 2);
    CHECK(p1.getResource(WOOD) == 2);
    CHECK(p1.getResource(BRICK) == 0);

    // Try to remove more resources than available
    p1.removeResource(WOOD, 5);
    CHECK(p1.getResource(WOOD) == 2);  // Should remain 2, as there's not enough to remove
}
TEST_CASE("Test addResource and removeResource with invalid resource type") {
    Player p1("Alice");

    // Attempt to add an invalid resource type
    p1.addResource(-1, 5);
    CHECK(p1.getResource(WOOD) == 0);  // Should not change the resources

    // Attempt to remove an invalid resource type
    p1.removeResource(6, 3);
    CHECK(p1.getResource(WOOD) == 0);  // Should not change the resources

    // Ensure no valid resources are affected
    p1.addResource(WOOD, 3);
    CHECK(p1.getResource(WOOD) == 3);
}

TEST_CASE("Test getTotalResources") {
    Player p1("Charlie");

    // Initially, total resources should be 0
    CHECK(p1.getTotalResources() == 0);

    // Add resources and check the total
    p1.addResource(WOOD, 2);
    p1.addResource(BRICK, 1);
    p1.addResource(WHEAT, 4);
    CHECK(p1.getTotalResources() == 7);

    // Remove some resources and check the total
    p1.removeResource(WHEAT, 2);
    CHECK(p1.getTotalResources() == 5);
}

TEST_CASE("Test addDevCard and getDevCardsSum") {
    Player p1("Dave");

    // Initially, no development cards
    CHECK(p1.getDevCardsSum() == 0);

    // Add different development cards
    p1.addDevCard("Knight");
    p1.addDevCard("Victory Point");
    p1.addDevCard("Monopoly");

    // Sum should reflect the total number of dev cards
    CHECK(p1.getDevCardsSum() == 3);

    // Add more and check
    p1.addDevCard("Year of Plenty");
    p1.addDevCard("Road Building");
    CHECK(p1.getDevCardsSum() == 5);
}
TEST_CASE("Test tradeResources") {
    Player p1("Eli");
    Player p2("Meni");

    // Initialize resources
    p1.addResource(WOOD, 4);
    p2.addResource(BRICK, 3);

    // Perform a trade: 2 WOOD for 1 BRICK
    p1.tradeResources(p2, WOOD, 2, BRICK, 1);

    // Check the resulting resources
    CHECK(p1.getResource(WOOD) == 2);
    CHECK(p1.getResource(BRICK) == 1);
    CHECK(p2.getResource(WOOD) == 2);
    CHECK(p2.getResource(BRICK) == 2);
}

TEST_CASE("Test tradeResources with invalid resource type and insufficient resources") {
    Player p1("Bob");
    Player p2("Charlie");

    // Initialize resources
    p1.addResource(WOOD, 2);
    p2.addResource(BRICK, 3);

    // Attempt to trade with an invalid resource type
    p1.tradeResources(p2, -1, 2, BRICK, 1);
    CHECK(p1.getResource(WOOD) == 2);
    CHECK(p2.getResource(BRICK) == 3);

    // Attempt to trade with insufficient resources
    p1.tradeResources(p2, WOOD, 5, BRICK, 1);
    CHECK(p1.getResource(WOOD) == 2);  // Should not change
    CHECK(p2.getResource(BRICK) == 3);  // Should not change
}

TEST_CASE("Test tradeWithBank") {
    Player p1("George");

    // Initialize resources
    p1.addResource(WOOD, 8);

    // Trade 4 WOOD for 1 BRICK
    p1.tradeWithBank(BRICK, 1, WOOD);

    // Check the resulting resources
    CHECK(p1.getResource(WOOD) == 4);
    CHECK(p1.getResource(BRICK) == 1);
}

TEST_CASE("Test tradeWithBank with invalid resource type and insufficient resources") {
    Player p1("Dave");

    // Initialize resources
    p1.addResource(WOOD, 4);

    // Attempt to trade with an invalid resource type
    p1.tradeWithBank(-1, 1, WOOD);
    CHECK(p1.getResource(WOOD) == 4);

    // Attempt to trade with insufficient resources
    p1.tradeWithBank(BRICK, 2, WOOD);  // Trying to trade 8 WOOD but only has 4
    CHECK(p1.getResource(WOOD) == 4);  // Should not change
    CHECK(p1.getResource(BRICK) == 0);  // Should not change
}

TEST_CASE("Test tradeDevelopmentCards with insufficient knight cards") {
    Player p1("Eve");
    Player p2("Frank");

    // Add some resources but no knights
    p2.addResource(WOOD, 3);
    p2.addResource(BRICK, 2);

    // Attempt to trade knight cards when the player has none
    p1.tradeDevelopmentCards(p2, 1, 2, 1, 0, 0, 0);
    CHECK(p1.getKnightsNum() == 0);  // No knights to trade
    CHECK(p2.getResource(WOOD) == 3);
    CHECK(p2.getResource(BRICK) == 2);

    // Add knights and try again
    p1.addKnights(1);
    p1.tradeDevelopmentCards(p2, 2, 2, 1, 0, 0, 0);  // Trying to trade 2 knights but only has 1
    CHECK(p1.getKnightsNum() == 1);  // Should not change
    CHECK(p2.getResource(WOOD) == 3);
    CHECK(p2.getResource(BRICK) == 2);
}


TEST_CASE("Test bigArmyCard") {
    Player p1("Hannah");

    // Initially, points should be 0
    CHECK(p1.getPoints() == 0);

    // Add active knights
    p1.addActiveKnights(3);

    // Check big army card logic
    p1.bigArmyCard();
    CHECK(p1.getPoints() == 2);  // Should have added 2 points
}











//////////////////////////////////////////////////////////////////// catan ///////////////////////////////////////////////////////////////////////////////






TEST_CASE("Test current player turn management") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan catan(p1, p2, p3);

    // Check initial random player
    Player &currentPlayer = catan.getCurrentPlayer();
    REQUIRE((currentPlayer.getName() == "Alice" || currentPlayer.getName() == "Bob" || currentPlayer.getName() == "Charlie"));

    // Check setting current player manually
    catan.setCurrentPlayer(1);  // Set to Bob
    CHECK_EQ(catan.getCurrentPlayer().getName(), "Bob");

    catan.setCurrentPlayer(2);  // Set to Charlie
    CHECK_EQ(catan.getCurrentPlayer().getName(), "Charlie");

    // Check next and previous player functions
    catan.nextPlayer();
    CHECK_EQ(catan.getCurrentPlayer().getName(), "Alice");

    catan.previousPlayer();
    CHECK_EQ(catan.getCurrentPlayer().getName(), "Charlie");
}

TEST_CASE("End of game check") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan catan(p1, p2, p3);

    CHECK_FALSE(catan.isGameFinished());

    p1.addPoints(10);
    CHECK(catan.isGameFinished());  // Alice reaches 10 points, game should end
}

TEST_CASE("Buying development card with insufficient resources") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan catan(p1, p2, p3);

    catan.setCurrentPlayer(0);  // Alice's turn

    // Alice does not have enough resources
    catan.buyDevelopmentCard(p1);
    CHECK_EQ(p1.getDevCardsSum(), 0);  // Alice should not be able to buy a development card
}



TEST_CASE("Placing settlement not on player's turn") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan game(p1, p2, p3);

    game.setCurrentPlayer(0);  // Set current player to Alice

    // Redirect standard input to simulate Bob trying to place a settlement
    istringstream input("0\n");
    cin.rdbuf(input.rdbuf());
    
    game.placeSettlement(p2, game.getBoard());
    CHECK_EQ(p2.getPoints(), 0);  // Bob should not be able to place a settlement on Alice's turn
}

TEST_CASE("Placing road not on player's turn") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan game(p1, p2, p3);

    game.setCurrentPlayer(1);  // Set current player to Bob

    // Redirect standard input to simulate Charlie trying to place a road
    istringstream input("0\n");
    cin.rdbuf(input.rdbuf());

    game.placeRoad(p3, game.getBoard());
    CHECK_EQ(p3.getRoadsNum(), 0);  // Charlie should not be able to place a road on Bob's turn
}

TEST_CASE("Upgrading settlement to city not on player's turn") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan game(p1, p2, p3);

    game.setCurrentPlayer(2);  // Set current player to Charlie

    // Give Alice enough resources to upgrade a settlement
    p1.addResource(WHEAT, 2);
    p1.addResource(IRON, 3);

    // Redirect standard input to simulate Alice trying to upgrade a settlement
    istringstream input("0\n");
    cin.rdbuf(input.rdbuf());

    game.upgradeSettlementToCity(p1, game.getBoard());
    Vertex &v = game.getBoard().getVertex(0);
    CHECK_NE(v.getType(), "city");  // Alice should not be able to upgrade a settlement on Charlie's turn
}

TEST_CASE("Placing settlement without enough resources") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan game(p1, p2, p3);

    game.setCurrentPlayer(0);  // Set current player to Alice

    // Redirect standard input to simulate Alice trying to place another settlement
    istringstream input("1\n");
    cin.rdbuf(input.rdbuf());

    game.placeSettlement(p1, game.getBoard());
    CHECK_EQ(p1.getPoints(), 1);  // Alice should not be able to place another settlement due to insufficient resources
}






////////////////////////////////////////////////////////devcard //////////////////////////////////////////////////////////////////////////////////////////







// Test for Knight card
TEST_CASE("Knight card functionality") {
    Player p1("Alice");
    Catan game(p1, p1, p1);

    p1.addKnights(1);  // Alice has 1 knight card

    Knight knight;
    knight.playCard(p1, game);

    CHECK(p1.getKnightsNum() == 0);  // The knight card should be used
    CHECK(p1.getActiveKnightSum() == 1);  // Alice should now have 1 active knight
}

// Test for Victory Point card
TEST_CASE("Victory Point card functionality") {
    Player p1("Alice");
    Catan game(p1, p1, p1);

    p1.addPoints(0);  // Alice starts with 0 points

    VictoryPoint vp;
    vp.playCard(p1, game);

    CHECK(p1.getPoints() == 1);  // Alice should gain 1 victory point
}

// Test for Monopoly card with edge cases
TEST_CASE("Monopoly card functionality and invalid resource type handling") {
    Player p1("Alice");
    Player p2("Bob");
    Catan game(p1, p2, p1);

    p2.addResource(WOOD, 5);  // Bob has 5 wood

    istringstream simulatedInput("1\n");  // Alice chooses to monopolize Wood
    streambuf* originalCin = cin.rdbuf(simulatedInput.rdbuf());  // Redirect std::cin

    Monopoly monopoly;
    monopoly.playCard(p1, game);

    CHECK(p1.getResource(WOOD) == 5);  // Alice should now have 5 wood
    CHECK(p2.getResource(WOOD) == 0);  // Bob should have 0 wood

    cin.rdbuf(originalCin);  // Restore std::cin to its original state
}

// Test for Year of Plenty card with invalid resource type handling
TEST_CASE("Year of Plenty card functionality and invalid resource type handling") {
    Player p1("Alice");
    Catan game(p1, p1, p1);

    istringstream simulatedInput("2\n");  // Alice chooses to receive Brick
    streambuf* originalCin = cin.rdbuf(simulatedInput.rdbuf());  // Redirect std::cin

    YearOfPlenty yop;
    yop.playCard(p1, game);

    CHECK(p1.getResource(BRICK) == 2);  // Alice should now have 2 brick

    cin.rdbuf(originalCin);  // Restore std::cin to its original state
}


