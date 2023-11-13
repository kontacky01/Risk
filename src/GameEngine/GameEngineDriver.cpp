#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <random>

void initializeGameMap(GameEngine *gameEngine) {
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

    // create continents
    auto *northAmerica = new Continent("north america", 5);
    auto *europe = new Continent("europe", 5);

    // create territories
    auto *usa = new Territory("usa", 1, northAmerica->getId(), 500);
    auto *canada = new Territory("canada", 2, northAmerica->getId(), 0);
    auto *france = new Territory("france", 3, europe->getId(), 50);
    auto *germany = new Territory("germany", 4, europe->getId(), 700);

    // assign territories to the players
    player1->addTerritory(usa);
    player1->addTerritory(france);
    player1->addTerritory(germany);

    // set territory adjacency
    usa->addAdjacentTerritory(canada);
    canada->addAdjacentTerritory(usa);

    // add territories to continents
    northAmerica->territoriesInContinents.push_back(usa);
    northAmerica->territoriesInContinents.push_back(canada);
    europe->territoriesInContinents.push_back(france);
    europe->territoriesInContinents.push_back(germany);

    // create game map and add continents
    Map *gameMap = new Map();
    gameMap->addContinent(northAmerica);
    gameMap->addContinent(europe);

    // add territories to the map
    gameMap->addTerritory(usa);
    gameMap->addTerritory(canada);
    gameMap->addTerritory(france);
    gameMap->addTerritory(germany);

    // set game map in
    gameEngine->setGameMap(gameMap);
}

int testMainGameLoop() {

         auto *engine = new GameEngine;
    initializeGameMap(engine);

    //*************************************************************//
    //                     W E L C O M E                           //
    //                          T O                                //
    //                         R I S K                             //
    //*************************************************************//


    // simulation of game phases
  //  while (!engine->isGameOver()) {
        engine->reinforcementPhase();
        engine->issueOrdersPhase();
        engine->executeOrdersPhase();

        // check for players without territories and remove them
        engine->removePlayersWithoutTerritories();

        // check if a player has won
     //   if (engine->checkForWinner()) {
     //       break;
    //    }
  //  }

    // announce winner or game status
   // Player *winner = engine->checkForWinner();
  //  if (winner) {
  //      cout << "Player " << winner->getID() << " wins the game!" << endl;
  //  }

    delete engine;
    engine = nullptr;

    return 0;
}











/*
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
