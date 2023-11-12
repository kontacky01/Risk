#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

void testMainGameLoop(GameEngine& gameEngine) {
    // Create test territories
    Territory* territoryA = new Territory("Territory A", 1, 1, 10);
    Territory* territoryB = new Territory("Territory B", 2, 2, 15);
    Territory* territoryC = new Territory("Territory C", 3, 1, 20);

    // Add territories to player 1
    vector<Territory*> territoriesPlayer1 { territoryA, territoryB };

    // Add territories to player 2
    vector<Territory*> territoriesPlayer2 { territoryC };

    // Print territories for Player 1
    cout << "\n\nTerritories for Player 1:" << endl;
    for (Territory* territory : territoriesPlayer1) {
        if (territory != nullptr) {
            cout << territory->getName() << endl;
        } else {
            cout << "Null territory found in Player 1's list." << endl;
        }
    }

    // Dynamic allocation of players and their components
    Player* player1 = new Player(territoriesPlayer1, new Hand(), new OrdersList(), 1);
    Player* player2 = new Player(territoriesPlayer2, new Hand(), new OrdersList(), 2);
    gameEngine.setPlayers({player1, player2});
}








/*void testGameStates() {
    cout << "\n************************************\nTesting Game Driver!!! \n************************************\n\n";
    GameEngine engine;
    string command;

    while (true) {
        cout << "\nEnter a command: ";
        cin >> command;

        if (command == "quit") {
            break;
        }

        engine.executeCommand(command);
    }
}*/