

# Catan Game

Welcome to the Catan game implemented in C++! This is a simplified version of the popular board game "Settlers of Catan," where players compete to build settlements, roads, and cities while trading resources to become the dominant player on the board.

## Table of Contents
- [Getting Started](#getting-started)
- [How to Play](#how-to-play)
- [Classes and Structure](#classes-and-structure)
- [Development and Testing](#development-and-testing)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Prerequisites
- C++ compiler supporting C++14 or later (e.g., g++)
- Make (optional, for building the project using the provided Makefile)

### Building the Project
To build the project, use the provided Makefile:

```bash
make catan
```

This will compile the source files and create an executable named `demo`, and start the game.



## How to Play

### Objective
The goal of the game is to be the first player to reach 10 victory points. Points are earned by building settlements, cities, and obtaining certain development cards.

### Game Flow
1. **Starting the Game**: Each player takes turns placing their initial settlements and roads on the board.
2. **Rolling the Dice**: At the start of each turn, the current player rolls two dice. The sum determines which tiles produce resources.
3. **Gathering Resources**: Players receive resources based on their settlements and cities adjacent to the tiles producing resources.
4. **Building and Trading**: Players can build roads, settlements, and cities using their resources. They can also trade resources with other players or with the bank.
5. **Playing Development Cards**: Players can buy and play development cards, which grant various advantages, such as additional resources, knights, or victory points.
6. **Ending the Turn**: The current player ends their turn, and the next player takes their turn.

### Winning the Game
The first player to reach 10 victory points wins the game. Points are gained by building settlements (1 point each), cities (2 points each), and obtaining certain development cards .

## Classes and Structure

### Main Classes
- **Player**: Represents a player in the game, handling their resources, points, and actions.
- **Board**: Represents the game board, managing the tiles, roads, and settlements.
- **Catan**: The main game class that manages the game flow, including player turns, dice rolls, and game state.
- **Devcard**: Represents development cards that players can buy and use during the game.

### Game Structure
- **Tiles**: The hexagonal tiles on the board that produce resources when the corresponding dice roll occurs.
- **Vertices**: The points where roads and settlements are placed.
- **Edges**: The connections between vertices where roads are placed.

### Development Cards
Development cards include:
- **Knight**: the player who has all 3 knight gets the big army card(2 points).
- **Victory Point**: Adds a victory point to the player's total.
- **Monopoly**: Allows the player to take all of a specific resource from all other players.
- **Year of Plenty**: Grants the player two of any resource.
- **Road Building**: Allows the player to place two roads for free.

## Development and Testing

### Testing
The project includes test cases using the Doctest framework. To run the tests, use:

```bash
make test

```

### Valgrind
To check for memory leaks and other issues, you can use Valgrind:

```bash
make valgrind
```



## Contributing
Contributions are welcome! Please fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.


## Contact

For any questions or inquiries, please contact Eli Frydman at elifrydman08@gmail.com.
