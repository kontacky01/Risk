#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

void initializeGame(GameEngine &gameEngine) {
    MapLoader mapLoader;
    Map *map = mapLoader.loadMap("../src/Map/MapFolder/World.map");

    // Obtain a list of all territories from the loaded map
    vector<Territory *> allTerritories = map->territoryList;

    // Create Player 1 and assign territories
    Player *player1 = new Player({}, new Hand(), new OrdersList(), 1);
    player1->setReinforcement(50);

    // Create Player 2 and assign territories
    Player *player2 = new Player({}, new Hand(), new OrdersList(), 2);
    player2->setReinforcement(0);

    // Distribute territories to players
    // For simplicity, let's distribute the territories in alternating fashion
    for (size_t i = 0; i < allTerritories.size(); ++i) {
        if (i % 2 == 0) {
            player1->addTerritory(allTerritories[i]);
        } else {
            player2->addTerritory(allTerritories[i]);
        }
    }

    gameEngine.setGameMap(map);
    gameEngine.setPlayers({player1, player2});
}

int testMainGameLoop() {
    GameEngine gameEngine;

    initializeGame(gameEngine);

    gameEngine.mainGameLoop();

    gameEngine.cleanupResources();

    return 0;
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