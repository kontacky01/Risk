#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <random>

void initializeGame(GameEngine &gameEngine) {
    Map *map = new Map();
    MapLoader mapLoader;
    map = mapLoader.loadMap("../src/Map/MapFolder/World.map");

    // Obtain a list of all territories from the loaded map
    vector<Territory *> allTerritories = map->territoryList;

    // Create Player 1 and assign random territories (between 1 and 5)
    Player *player1 = new Player({}, new Hand(), new OrdersList(), 1);
    player1->setReinforcement(50);

    // Create Player 2 and assign random territories (between 1 and 5)
    Player *player2 = new Player({}, new Hand(), new OrdersList(), 2);
    player2->setReinforcement(0);

    // Shuffle the territories randomly
    shuffle(allTerritories.begin(), allTerritories.end(), std::mt19937(std::random_device()()));

    // Assign territories to players
    for (size_t i = 0; i < allTerritories.size(); ++i) {
        if (i % 2 == 0 && player1->getTerritories().size() < 5) {
            player1->addTerritory(allTerritories[i]);
        } else if (player2->getTerritories().size() < 5) {
            player2->addTerritory(allTerritories[i]);
        }
    }

    gameEngine.setGameMap(map);
    gameEngine.setPlayers({player1, player2});
}

int testMainGameLoop() {
    GameEngine* gameEngine = new GameEngine;

    initializeGame(*gameEngine);

    gameEngine->mainGameLoop();

    gameEngine->cleanupResources();

    delete gameEngine;

    return 0;
}


/*void testGameStates() {
    cout << "\n************************************\nTesting Game Driver!!! \n************************************\n\n";
    GameEngine engine;
    string command;

    while (true) {
        cout << "\nEnter a command: ";
        getline(cin, command);

        if (command == "quit") {
            break;
        }
        engine.executeCommand(command);
    }
}*/