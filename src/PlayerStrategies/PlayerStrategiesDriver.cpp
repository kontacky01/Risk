#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../CardsDeck/Cards.h"
#include "../OrdersList/Orders.h"
#include <random>

/*void initializeGame2(GameEngine &gameEngine) {
    // Load the map
    // MapLoader mapLoader;
    // Map *currentGameMap = mapLoader.loadMap("../src/Map/MapFolder/World.map");

    // if (currentGameMap == nullptr) {
    //     cout << "Failed to load the map." << endl;
    //     return;
    // }

    // Obtain a list of all territories from the loaded map
    vector<Territory *> allTerritories;
    
    Territory* t1 = new Territory("UK", 1, 2, 0);
    Territory* t2 = new Territory("USA", 2, 3, 0);
    Territory* t3 = new Territory("Russia", 3, 3, 0);
    Territory* t4 = new Territory("Israel", 4, 2, 0);
    Territory* t5 = new Territory("Italy", 5, 3, 0);
    Territory* t6 = new Territory("Bulgaria", 6, 3, 0);
    allTerritories.push_back(t1);
    allTerritories.push_back(t2);
    allTerritories.push_back(t3);
    allTerritories.push_back(t4);
    allTerritories.push_back(t5);
    allTerritories.push_back(t6);

    Deck *deck = gameEngine.getDeck();
    deck->fillDeck(5);
    deck->shuffleDeck();
    cout << "\n";
    deck->printDeck();

    BenevolentPlayerStrategy* benevolent = new BenevolentPlayerStrategy();
    NeutralPlayerStrategy* neutral = new NeutralPlayerStrategy();

    // Create Player 1 and assign random territories (between 1 and 5)
    Player *player1 = new Player({}, new Hand(), new OrdersList(), 1);
    player1->setReinforcement(50);
    player1->setGameEngine(&gameEngine);
    player1->setDeck(deck);
    player1->setStrategy(benevolent);

    // Create Player 2 and assign random territories (between 1 and 5)
    Player *player2 = new Player({}, new Hand(), new OrdersList(), 2);
    player2->setReinforcement(50);
    player2->setGameEngine(&gameEngine);
    player2->setDeck(deck);
    player2->setStrategy(neutral);


    for (int i = 0; i < 5; ++i) {
        Card *drawnCard = deck->drawACard();
        player1->getHand()->addCard(drawnCard);
        player2->getHand()->addCard(drawnCard);
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
            territory->continentName = territory->getName();
        } else if (player2->getTerritories().size() < 5) {
            Territory* territory = allTerritories[i];
            player2->addTerritory(territory);
            territory->setOwnerId(player2->getID());
            territory->continentName = territory->getName();
        }
    }

    vector<Territory*> player1Territories = player1->getTerritories();
    cout << "\n================================== Player 1's territories & cards ==================================" << endl;
    for (const auto& territory : player1Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }
    cout << player1->getHand() << endl;

    vector<Territory*> player2Territories = player2->getTerritories();
    cout << "================================== Player 2 territories & cards ==================================" << endl;
    for (const auto& territory : player2Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }
    cout << player2->getHand() << endl;

    // Set the map and players in the game engine
    //gameEngine.setGameMap(currentGameMap);
    gameEngine.setPlayers({player1, player2});
}


void testPlayerStrategies() {
    auto *gameEngine = new GameEngine;

    initializeGame2(*gameEngine);
    gameEngine->mainGameLoop();
    gameEngine->cleanupResources();

    delete gameEngine;

    //return 0;
}*/
//============================================================================================================
void initializeGame2(GameEngine &gameEngine) {
    // Load the map
    MapLoader *mapLoader = new MapLoader();
    cout << "---------> Load a valid map <---------\n\n";
    Map *currentGameMap = mapLoader->loadMap("C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/Map/MapFolder/World.map");
    //currentGameMap->printMapSummary();
    //mapLoader->printContinentsAndBonuses();
    currentGameMap->validate();
    gameEngine.setGameMap(currentGameMap);

    vector<Territory *> allTerritories  = currentGameMap->getTerritories();


    Deck *deck = gameEngine.getDeck();
    deck->fillDeck(5);
    deck->shuffleDeck();
    cout << "\n";
    deck->printDeck();

    BenevolentPlayerStrategy* benevolent = new BenevolentPlayerStrategy();
    NeutralPlayerStrategy* neutral = new NeutralPlayerStrategy();

    // Create Player 1 and assign random territories (between 1 and 5)
    Player *player1 = new Player({}, new Hand(), new OrdersList(), 1);
    player1->setReinforcement(50);
    player1->setGameEngine(&gameEngine);
    player1->setDeck(deck);
    player1->setStrategy(benevolent);

    // Create Player 2 and assign random territories (between 1 and 5)
    Player *player2 = new Player({}, new Hand(), new OrdersList(), 2);
    player2->setReinforcement(50);
    player2->setGameEngine(&gameEngine);
    player2->setDeck(deck);
    player2->setStrategy(neutral);


    for (int i = 0; i < 5; ++i) {
        Card *drawnCard = deck->drawACard();
        player1->getHand()->addCard(drawnCard);
        player2->getHand()->addCard(drawnCard);
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
            territory->continentName = territory->getName();
        } else if (player2->getTerritories().size() < 5) {
            Territory* territory = allTerritories[i];
            player2->addTerritory(territory);
            territory->setOwnerId(player2->getID());
            territory->continentName = territory->getName();
        }
    }

    vector<Territory*> player1Territories = player1->getTerritories();
    cout << "\n================================== Player 1's territories & cards ==================================" << endl;
    for (const auto& territory : player1Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }
    cout << player1->getHand() << endl;

    vector<Territory*> player2Territories = player2->getTerritories();
    cout << "================================== Player 2 territories & cards ==================================" << endl;
    for (const auto& territory : player2Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }
    cout << player2->getHand() << endl;

    // Set the map and players in the game engine
    //gameEngine.setGameMap(currentGameMap);
    gameEngine.setPlayers({player1, player2});
}


void testPlayerStrategies() {
    auto *gameEngine = new GameEngine;

    initializeGame2(*gameEngine);
    gameEngine->mainGameLoop();
    gameEngine->cleanupResources();

    delete gameEngine;

    //return 0;
}