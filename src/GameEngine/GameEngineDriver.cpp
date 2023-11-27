#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <random>


void initializeGame(GameEngine &gameEngine) {
    // Load the map
    MapLoader mapLoader;
    Map *currentGameMap = mapLoader.loadMap("../src/Map/MapFolder/World.map");

    if (currentGameMap == nullptr) {
        cout << "Failed to load the map." << endl;
        return;
    }

    // Obtain a list of all territories from the loaded map
    vector<Territory *> allTerritories = currentGameMap->getTerritories();

    Deck *deck = gameEngine.getDeck();
    deck->fillDeck(5);
    deck->shuffleDeck();
    deck->printDeck();

    // Create Player 1 and assign random territories (between 1 and 5)
    Player *player1 = new Player({}, new Hand(), new OrdersList(), 1);
    player1->setReinforcement(50);
    player1->setGameEngine(&gameEngine);
    player1->setDeck(deck);

    // Create Player 2 and assign random territories (between 1 and 5)
    Player *player2 = new Player({}, new Hand(), new OrdersList(), 2);
    player2->setReinforcement(0);
    player2->setGameEngine(&gameEngine);
    player2->setDeck(deck);


    for (int i = 0; i < 5; ++i) {
        Card *drawnCard = deck->draw();
        player1->getHand()->addCard(drawnCard);
    }

    // Shuffle the territories randomly
    shuffle(allTerritories.begin(), allTerritories.end(), std::mt19937(std::random_device()()));

    // Assign territories to players
    // Shuffle the territories randomly
    shuffle(allTerritories.begin(), allTerritories.end(), std::mt19937(std::random_device()()));

// Assign territories to players
    for (size_t i = 0; i < allTerritories.size(); ++i) {
        if (i % 2 == 0 && player1->getTerritories().size() < 5) {
            Territory* territory = allTerritories[i];
            player1->addTerritory(territory);
            territory->setOwnerId(player1->getID());
            territory->continentName = currentGameMap->getContinentById(territory->getContinentId())->getName();
        } else if (player2->getTerritories().size() < 5) {
            Territory* territory = allTerritories[i];
            player2->addTerritory(territory);
            territory->setOwnerId(player2->getID());
            territory->continentName = currentGameMap->getContinentById(territory->getContinentId())->getName();
        }
    }

    // Debug print statements to check the state of the game objects
    cout << "Map loaded successfully." << endl;

    vector<Territory*> player1Territories = player1->getTerritories();

    cout << "Player 1's territories:" << endl;

    for (const auto& territory : player1Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }

    cout << "Player 1 cards: " << player1->getHand() << endl;

    cout << "Player 2 territories: " << player2->getTerritories().size() << endl;

    // Set the map and players in the game engine
    gameEngine.setGameMap(currentGameMap);
    gameEngine.setPlayers({player1, player2});
}


int testMainGameLoop() {
    auto *gameEngine = new GameEngine;

    initializeGame(*gameEngine);

    //gameEngine->gameMap()->printMapSummary();

    gameEngine->reinforcementPhase();
    gameEngine->issueOrdersPhase();
    gameEngine->executeOrdersPhase();

    gameEngine->cleanupResources();

    delete gameEngine;

    return 0;
}

/*
void initializeGameMap(GameEngine *gameEngine) {
    MapLoader mapLoader;
    Map *gameMap = mapLoader.loadMap("../src/Map/MapFolder/World.map");

    // initialize deck and fill it with cards
    Deck *deck = new Deck();
    deck->fillDeck(3);

    // cout << "\n"; deck->printDeck();

    // create players
    auto *player1 = new Player();
    auto *player2 = new Player();
    auto *player3 = new Player();

    // set initial army units for each player
    player1->setReinforcement(500);
    player2->setReinforcement(50);
    player3->setReinforcement(0);

    // assign hands and decks to players
    player1->setHand(new Hand());
    player2->setHand(new Hand());
    player3->setHand(new Hand());
    player1->setDeck(deck);
    player2->setDeck(deck);
    player3->setDeck(deck);

    // add players to the game engine
    vector<Player *> players = {player1, player2, player3};
    gameEngine->setPlayers(players);

    int playerIndex = 0;
    int territoriesToAssign = gameMap->territoryList.size();

    for (const auto &territoryPair: gameMap->territories) {
        Territory *territory = territoryPair.second;

        if (playerIndex == 0 && territoriesToAssign > 0) {
            players[playerIndex]->addTerritory(territory);
            territoriesToAssign--;
        } else if (playerIndex == 2 && territoriesToAssign == 0) {
            // Player 2 gets 0 territories
            playerIndex = (playerIndex + 1) % players.size();
        } else if (playerIndex == 2 && territoriesToAssign > 0) {
            players[playerIndex]->addTerritory(territory);
            territoriesToAssign--;
        } else {
            players[playerIndex]->addTerritory(territory);
        }

        playerIndex = (playerIndex + 1) % players.size();
    }

    // set game map in
    gameEngine->setGameMap(gameMap);
}

int testMainGameLoop() {

    auto *engine = new GameEngine;
    initializeGameMap(engine);

    engine->reinforcementPhase();
    engine->issueOrdersPhase();
    //engine->executeOrdersPhase();

    // check for players without territories and remove them
    //engine->removePlayersWithoutTerritories();



    delete engine;
    engine = nullptr;

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
