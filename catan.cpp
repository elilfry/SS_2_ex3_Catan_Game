#include "catan.hpp"

using namespace std;

namespace ariel
{
    
    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        // static int boardInIt = 0;
        // boardInIt++;
            //initialize players
            players.push_back(&p1);
            players.push_back(&p2);
            players.push_back(&p3);
        
         for (int i = 0; i < 4; ++i) {
            devCards.push_back(std::make_unique<VictoryPoint>());
        }
        for (int i = 0; i < 3; ++i) {
            devCards.push_back(std::make_unique<Knight>());
        }
        for (int i = 0; i < 2; ++i) {
        devCards.push_back(std::make_unique<Monopoly>());
        devCards.push_back(std::make_unique<YearOfPlenty>());
        devCards.push_back(std::make_unique<RoadBuilding>());
        }

        //suffle the dev cards
        shuffleResources(devCards);

         //push the dev cards to the stack
        for (size_t i = 0; i < devCards.size(); i++)
        {
            devCardsDeck.push(move(devCards[i]));
        }
        
            this->ChooseStartingPlayer();
            
    
        
        
    }

    Catan::~Catan()
    {
        cout << "Catan game destroyed." << endl;
    }
    

    vector<Player*> Catan::getPlayers()
    {
        return players;
    }
    void Catan::shuffleResources(vector<std::unique_ptr<Devcard>> &devCards)
    {
        random_device rd;
        mt19937 g(rd());

        // Shuffle the resources vector using the random number generator
        shuffle(devCards.begin(), devCards.end(), g);

       

    }

    void Catan::ChooseStartingPlayer() //need to check
    {
        srand(time(0));
        currentPlayer = rand() % 3; // choose a random player to start
    }

    Board& Catan::getBoard()
    {
        return board;
    }

    Player& Catan::getCurrentPlayer()
    {
        return *players[(size_t)currentPlayer];
    }

    void Catan::setCurrentPlayer(int playerIndex) //for testing
    {
    currentPlayer = playerIndex;
    }


    void Catan::nextPlayer()
    {
        currentPlayer = (currentPlayer + 1) % 3;
    }

    void Catan::previousPlayer()
    {
        currentPlayer = (currentPlayer + 2) % 3;
    }

    void Catan::placeSettlement(Player &player, Board &board    )
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }


        //if it is the 1st round of the game

        if(player.getPoints() < 2) 
        {
            cout << "Please enter where you want to place the settlement(0-53)." << endl;
            int place;
            cin >> place;
            
            while(!board.placeSettlement(player, place))
            {
                cout << "Please enter again where you want to place the settlement(0-53)." << endl;
                cin >> place;
            }
            player.addPoints(1);
        }
        else //if it is the 2nd round of the game or more
        {
            //check if the player has enough resources(1 wood, 1 brick, 1 sheep, 1 wheat)
            if(player.getResource(WOOD) < 1 || player.getResource(BRICK) < 1 || player.getResource(SHEEP) < 1 || player.getResource(WHEAT) < 1)
            {
                cout << "You don't have enough resources to place a settlement." << endl;
                return;
            }

            cout << "Please enter where you want to place the settlement(0-53)." << endl;
            int place;
            cin >> place;

            while (!board.placeSettlement(player, place))
            {
                cout << "Please enter again where you want to place the settlement(0-53) , -1 to exit ." << endl;
                cin >> place;
                if(place == -1)
                {
                    return;
                }
            }
            // Deduct the resources from the player
            player.removeResource(WOOD, 1);
            player.removeResource(BRICK, 1);
            player.removeResource(SHEEP, 1);
            player.removeResource(WHEAT, 1);
            
            player.addPoints(1);



        }
       
    }

    void Catan::placeRoad(Player &player, Board &board)
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }

       //if we are in the 1st round of the game
        if(player.getPoints() <= 2 && player.getRoadsNum() < 2 )
        {
            cout << "Please enter where you want to place the road." << endl;
            int place;
            cin >> place;

            while(!board.placeRoad(player, place))
            {
                cout << "Please enter again where you want to place the road, -1 to exit" << endl;
                cin >> place;
                if(place == -1)
                {
                    return;
                }
            }
        }else //if it is the 2nd round of the game or more
        {
            //check if the player has enough resources
            if(player.getResource(WOOD) < 1 || player.getResource(BRICK) < 1)
            {
                cout << "You don't have enough resources to place a road." << endl;
                return;
            }

            cout << "Please enter where you want to place the road." << endl;
            int place;
            cin >> place;

            while (!board.placeRoad(player, place))
            {
                cout << "Please enter again where you want to place the road, -1 to exit" << endl;
                cin >> place;
                if(place == -1)
                {
                    return;
                }
            }

            player.removeResource(WOOD, 1);
            player.removeResource(BRICK, 1);
        }
    }

    void Catan::upgradeSettlementToCity(Player &player, Board &board)
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }

        //check if the player has enough resources
        if(player.getResource(IRON) < 3 || player.getResource(WHEAT) < 2)
        {
            cout << "You don't have enough resources to upgrade a settlement to a city." << endl;
            return;
        }

        cout << "Please enter where you want to upgrade the settlement to a city." << endl;
        int place;
        cin >> place;

        while (!board.upgradeSettlementToCity(player, place))
        {
            cout << "Please enter again where you want to upgrade the settlement to a city. -1 to exit" << endl;
            cin >> place;
            if(place == -1)
            {
                return;
            }
        }
        // Deduct the resources from the player
        player.removeResource(WHEAT, 2);
        player.removeResource(IRON, 3);
        player.addPoints(1);
        
    }

    void Catan::intialResources(Board &board)
    {
         for(int i=0; i<players.size(); i++)
        {
            //distribute initial resources
            
        board.intialDistributeResources(*players[(size_t)i]);
        }
    }




    bool Catan::isGameFinished()
            {
                for (size_t i = 0; i < players.size(); i++)
                {
                    if (players[i]->getPoints() >= 10)
                    {
                        cout << "The game is finished. The winner is: " << players[i]->getName() << endl;
                        return true;
                    }
                }
                return false;
            }

    void Catan::rollDice( Board &board)
    {
        
        srand(time(0));
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int sum = dice1 + dice2;
        cout << "The sum of the dice is: " << sum << endl;
        cout << "\n";

        if(sum == 7)
        {
            cout << "The sum of the dice is 7. All players with more than 7 resources will lose half of their resources." << endl;
            //itrate through the players and do the player.sumIs7
            for(int i=0; i<players.size(); i++)
            {
                if(players[(size_t)i]->getTotalResources() > 7){
                (*players[(size_t)i]).sumIs7();

                }
                cout << "Player " << players[(size_t)i]->getName() << " 7" << endl;
            }
            return;
                
        }



        for(int i=0; i<players.size(); i++)
        {
            //distribute resources
            
        board.distributeResources(*players[(size_t)i], sum);
        }

    }
    Player* Catan::getPlayerByName( string &name)
    {
        for (Player* player : players)
    {
        if (player->getName() == name)
            return player;
    }
    return nullptr; // Player not found
    }

    
    //     Catan::buyDevelopmentCard:

    // Checks if the player has enough resources to buy a development card.
    // Deducts the resources from the player if they have enough.
    // Checks if there are development cards left in the deck.
    // Gives the player a development card from the deck.
    // Prints the action summary.

    void Catan::buyDevelopmentCard(Player &player)
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }

        //check if there is a development card left in the deck
        if(devCardsDeck.empty())
        {
            cout << "There are no development cards left in the deck." << endl;
            return;
        }

        //check if the player has enough resources
        if(player.getResource(WHEAT) < 1 || player.getResource(IRON) < 1 || player.getResource(SHEEP) < 1)
        {
            cout << "You don't have enough resources to buy a development card." << endl;
            return;
        }

        // Deduct the resources from the player
        player.removeResource(WHEAT, 1);
        player.removeResource(IRON, 1);
        player.removeResource(SHEEP, 1);

        // Give the player a development card from the deck
        std::unique_ptr<Devcard> devCard = move(devCardsDeck.top());
        devCardsDeck.pop(); // remove the development card from the deck
        cout << "The development card you got is: " << devCard->getType() << endl;
        player.addDevCard(devCard->getType()); // add the development card to the player's hand
    }

    void Catan::playDevelopmentCard(Player &player)
    {
        //check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) // check if the player is the current player
        {
            cout << "It is not your turn." << endl;
            return;
        }

        //check if the player has any development cards
        if(player.getDevCardsSum()<1)
        {
            cout << "You don't have any development cards to play." << endl;
            return;
        }

        cout << "Please enter the development card you want to play :" << endl;
        cout << "1. Victory Point" << endl;
        cout << "2. Knight" << endl;
        cout << "3. Monopoly" << endl;
        cout << "4. Year of Plenty" << endl;
        cout << "5. Road Building" << endl;

        int devCardType; //1 vp 2 knight 3 monopoly 4 year of plenty 5 road building
        cin >> devCardType;

        bool valid = false;
        while (!valid) // loop until the player enters a valid development card type
        {
            if (devCardType>=1 && devCardType<=5)
            {
                valid = true;
            }else if (devCardType == 0){
                return;
            }
            else
            {
                cout << "Invalid development card type. Please enter again." << endl;
                cout<< "if you want to exit enter 0." << endl;
                cin >> devCardType;
            }
        }

        
        switch (devCardType)
        {
            case 1: //Victory Point
            
                if(player.getVictoryPointCard() < 1)
                {
                    cout << "You don't have a Victory Point development card to play." << endl;
                    return;
                }else
                {
                    //play this card
                    VictoryPoint().playCard(player, *this);

                }
                break;
            case 2: //Knight
                if(player.getKnightsNum() < 1)
                {
                    cout << "You don't have a Knight development card to play." << endl;
                    return;
                }else
                {
                    //play this card
                    Knight().playCard(player, *this);

                }
                break;
            case 3: //Monopoly
                if(player.getMonopolyCard() < 1)
                {
                    cout << "You don't have a Monopoly development card to play." << endl;
                    return;
                }else
                {
                    //play this card
                    Monopoly().playCard(player, *this);

                }
                break;
            case 4: //Year of Plenty
                if(player.getYearOfPlentyCard() < 1)
                {
                    cout << "You don't have a Year of Plenty development card to play." << endl;
                    return;
                }else
                {
                    //play this card
                    YearOfPlenty().playCard(player, *this);

                }
                break;
            case 5: //Road Building
                if(player.getRoadBuildingCard() < 1)
                {
                    cout << "You don't have a Road Building development card to play." << endl;
                    return;
                }else
                {
                    //play this card
                    RoadBuilding().playCard(player, *this);

                }
                break;
          
        }

    }

    void Catan::trade(Player &player) 
    {
        // Check if it is the player's turn
        if (player.getName() != getCurrentPlayer().getName()) {
            cout << "It is not your turn." << endl;
            return;
        }

        int choice = getValidInput(0, 3, "Please enter 1 to trade resources, or 2 to trade development cards , or 3 to trade with the bank ,(0 to exit): ");
        switch(choice) 
        {
            case 0: return;
            case 1: tradeResources(player); break;
            case 2: tradeDevelopmentCard(player); break;
            case 3: tradeWithBank(player); break;
            default: cout << "Invalid choice -1." << endl;
        }

    }


    int Catan::getValidInput(int min, int max, const string& prompt) {
      int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
            cout << "Invalid input, please try again.\n";
        } else {
            break; // Valid input, break the loop
        }
    }
    return input;
}

    void Catan::tradeResources(Player &player) {
        
        int giveResource = getValidInput(1, 5, "Please enter the resource you want to give (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ");
        int giveAmount = getValidInput(1, INT_MAX, "Please enter the amount of the resource you want to give(positive number): ");

        //print the players
        for (size_t i = 0; i < players.size(); i++)
        {
            if(players[i]->getName() != player.getName()){
                cout << players[i]->getName() << endl;
            }
        }

        cout<< "Enter the name of the player you want to trade with: ";
        string name;
        cin >> name;
        Player* otherPlayer = getPlayerByName(name); // Get the player to trade with
        if(otherPlayer == nullptr) {
            cout << "Player not found." << endl;
            return;
        } else if(otherPlayer->getName() == player.getName()) { // Check if the player is trying to trade with themselves
            cout << "You can't trade with yourself." << endl;
            return;
        }

        int takeResource = getValidInput(1, 5, "Please enter the resource you want to give (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ");
        int takeAmount = getValidInput(1, INT_MAX, "Please enter the amount of the resource you want to give(positive number): ");

        player.tradeResources(*otherPlayer, giveResource-1, giveAmount, takeResource-1, takeAmount); // Trade resources


    }

    void Catan::tradeDevelopmentCard(Player &player) {
        //print the players
        for (size_t i = 0; i < players.size(); i++)
        {
            if(players[i]->getName() != player.getName()){
                cout << players[i]->getName() << endl;
            }
        }
        cout << "Please enter the name of the player you want to trade with: ";
        string name;
        cin >> name;
        Player* otherPlayer = getPlayerByName(name);
        if(otherPlayer == nullptr) {
            cout << "Player not found." << endl;
            return;
        } else if(otherPlayer->getName() == player.getName()) {
            cout << "You can't trade with yourself." << endl;
            return;
        }

        int knightAmount = getValidInput(1, INT_MAX, "Please enter the amount of Knight development cards you want to give(positive number): ");

        cout << "now player " << otherPlayer->getName() << " enter the amount of resources you want to give " << endl;

        int woodAmount = getValidInput(0, INT_MAX, "Please enter the amount of Wood you want to give(positive number): ");
        int brickAmount = getValidInput(0, INT_MAX, "Please enter the amount of Brick you want to give(positive number): ");
        int sheepAmount = getValidInput(0, INT_MAX, "Please enter the amount of Sheep you want to give(positive number): ");
        int wheatAmount = getValidInput(0, INT_MAX, "Please enter the amount of Wheat you want to give(positive number): ");
        int ironAmount = getValidInput(0, INT_MAX, "Please enter the amount of Iron you want to give(positive number): ");

        player.tradeDevelopmentCards(*otherPlayer, knightAmount, woodAmount, brickAmount, sheepAmount, wheatAmount, ironAmount); // Trade development cards
    }

    void Catan::tradeWithBank(Player &player) 
    {
        int getResource = getValidInput(1, 5, "Please enter the resource you want to get from the bank (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ");
        int amount = getValidInput(1, INT_MAX, "Please enter the amount of the resource you want to get(positive number): ");

        cout << "The amount you need to give is " << amount * 4 << " of the same resource." << endl;
        int giveResource = getValidInput(1, 5, "Please enter the resource you want to give to the bank (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ");

        player.tradeWithBank(getResource - 1, amount, giveResource - 1); // Trade with the bankP@tra
    }





    /*
    trade function
    case 1 trade resources
    case 2 dev card

    check if it is the player turn
    
    void Catan::trade(Player &player) {
    // Check if it is the player's turn
    if (player.getName() != getCurrentPlayer().getName()) {
        cout << "It is not your turn." << endl;
        return;
    }

    cout << "Please enter 1 to trade resources, or 2 to trade development cards , or 3 to trade with the bank ,(0 to exit): ";
    int choice;
    cin >> choice;
    if(choice < 0 || choice > 3) {
        cout << "Invalid choice. Please enter again." << endl;
        return;
    }

    switch(choice) {  
        case 0:
            return;
        
        case 1: { // Trade resources
            cout << "Please enter the resource you want to give (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ";
            int giveResource;
            cin >> giveResource;
            if(giveResource < 1 || giveResource > 5) {
                cout << "Invalid resource type. Please enter again." << endl;
                return;
            }
            cout << "Please enter the amount of the resource you want to give: ";
            int giveAmount;
            cin >> giveAmount;
            if(giveAmount < 1) {
                cout << "Invalid amount. Please enter again." << endl;
                return;
            }
            //print the players
            for (size_t i = 0; i < players.size(); i++)
            {
                if(players[i]->getName() != player.getName()){
                    cout << players[i]->getName() << endl;
                }
            }
            cout << "Enter the name of the player you want to trade with: ";
            string name;
            cin >> name;
            
            Player* otherPlayer = getPlayerByName(name); // Get the player to trade with
            if (otherPlayer == nullptr) {
                cout << "Player not found." << endl;
                return;
            } else if (otherPlayer->getName() == player.getName()) { // Check if the player is trying to trade with themselves
                cout << "You can't trade with yourself." << endl;
                return;
            }

            cout << " Player " << otherPlayer->getName() << " enter the resource you want to take (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ";
            int takeResource;
            cin >> takeResource;
            if(takeResource < 1 || takeResource > 5) {
                cout << "Invalid resource type. Please enter again." << endl;
                return;
            }
            cout << "Please enter the amount of the resource you want to take: ";
            int takeAmount;
            cin >> takeAmount;
            if(takeAmount < 1) {
                cout << "Invalid amount. Please enter again." << endl;
                return;
            }

            player.tradeResources(*otherPlayer, giveResource, giveAmount, takeResource, takeAmount); // Trade resources
            break;
        }
        cout << "printing the players" << endl;
        case 2: { // Trade development cards (only knights)
            //print the players
            for (size_t i = 0; i < players.size(); i++)
            {
                if(players[i]->getName() != player.getName()){
                    cout << players[i]->getName() << endl;
                }
            }
            cout << "Please enter the name of the player you want to trade with: ";

            string name2;
            cin >> name2;
            Player* otherPlayer = getPlayerByName(name2);
            if (otherPlayer == nullptr) {
                cout << "Player not found." << endl;
                return;
            } else if(otherPlayer->getName() == player.getName()) {
                cout << "You can't trade with yourself." << endl;
                return;
            }
            
             cout << "Please enter the amount of Knight development cards you want to give:" << endl;
                int knightAmount;
                cin >> knightAmount;
                if(knightAmount<1)
                {
                    cout << "Invalid amount. Please enter again." << endl;
                    return;
                }

                int woodAmount, brickAmount, sheepAmount, wheatAmount, ironAmount;
                cout << "Please enter the amount of resources you want in return:" << endl;
                cout << "if you want Wood enter amount(0 is ok)" << endl; cin >> woodAmount;
                cout << "if you want Brick enter amount(0 is ok)" << endl; cin >> brickAmount;
                cout << "if you want Sheep enter amount(0 is ok)" << endl; cin >> sheepAmount;
                cout << "if you want Wheat enter amount(0 is ok)" << endl; cin >> wheatAmount;
                cout << "if you want Iron enter amount(0 is ok)" << endl; cin >> ironAmount;

            player.tradeDevelopmentCards(*otherPlayer, knightAmount, woodAmount, brickAmount, sheepAmount, wheatAmount, ironAmount); 
                break;
        }

        case 3: { // Trade with the bank
            cout << "Please enter the resource you want to get from the bank (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron , 0 to exit): ";
            cout << "the trade is 4 to 1" << endl;
            int getResource;
            cin >> getResource;
            while(getResource < 0 || getResource > 5) {
                cout << "Invalid resource type. Please enter again." << endl;
                cin >> getResource;
                if(getResource == 0)
                {
                    return;
                }
            }
            cout << "Please enter the amount of the resource you want to get: ";
            int amount;
            cin >> amount;
            while(amount < 1) {
                cout << "Invalid amount. Please enter again." << endl;
                cin >> amount;
            }
            cout<< "you need to give 4 resources of the same resource to get 1 resource" << endl;
            cout << "Please enter the resource you want to give to the bank (1. Wood, 2. Brick, 3. Sheep, 4. Wheat, 5. Iron): ";
            int giveResource;
            cin >> giveResource;
            while(giveResource < 1 || giveResource > 5) {
                cout << "Invalid resource type. Please enter again." << endl;
                cin >> giveResource;
            }
            cout << "The amout you need to give is "<< amount*4 << " of the same resource" << endl;

            player.tradeWithBank(getResource-1, amount, giveResource-1); // Trade with the bank
            break;
        }

        default:
            cout << "Invalid choice. Please enter again." << endl;
            return;
    }
}
*/



} // namespace ariel