#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

void testMainGameLoop() {
    // initialize game engine and map loader
    GameEngine gameEngine;
    MapLoader mapLoader;
    Map *map = mapLoader.loadMap("../src/Map/MapFolder/World.map"); // loading map
    gameEngine.setMap(map); // set the map in the game engine

    vector<Territory *> territoriesPlayer1;
    vector<Territory *> territoriesPlayer2;

    for (int i = 0; i < map->territoryList.size(); i++) {
        if (i < map->territoryList.size() / 2) {
            territoriesPlayer1.push_back(map->territoryList[i]);
        } else {
            territoriesPlayer2.push_back(map->territoryList[i]);
        }
    }
    Hand *handPlayer1 = new Hand(); // Assuming Hand has a default constructor
    Hand *handPlayer2 = new Hand();

    OrdersList *ordersListPlayer1 = new OrdersList(); // Assuming OrdersList has a default constructor
    OrdersList *ordersListPlayer2 = new OrdersList();

    Player player1(territoriesPlayer1, handPlayer1, ordersListPlayer1, 1); // Player ID: 1
    Player player2(territoriesPlayer2, handPlayer2, ordersListPlayer2, 2); // Player ID: 2
    gameEngine.setPlayers({&player1, &player2});


    // begin game loop
    while (!gameEngine.isGameOver()) {
        cout << "Starting Reinforcement Phase" << endl;
        gameEngine.reinforcementPhase();
        cout << "Reinforcements for Player " << player1.getID() << ":" << endl;
        cout << "Reinforcements for Player " << player2.getID() << ":" << endl;


        cout << "Starting Issue Orders Phase" << endl;
        gameEngine.issueOrdersPhase();
        // Display issued orders
        // ...

        cout << "Starting Execute Orders Phase" << endl;
        gameEngine.executeOrdersPhase();
        // Display results of executed orders
        // ...

        // check for players to remove
        if (gameEngine.removePlayersWithoutTerritories()) {
            cout << "Players without territories have been removed." << endl;
        }

        // check for game end condition
        Player *winner = gameEngine.checkForWinner();
        if (winner != nullptr) {
            cout << "Player " << winner->getID() << " wins the game!" << endl;
            break;
        }
    }

    // cleanup
    cout << "...Cleaning up game resources..." << endl;

    delete map;
    map = nullptr;

    cout << "Game resources cleaned up successfully." << endl;
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