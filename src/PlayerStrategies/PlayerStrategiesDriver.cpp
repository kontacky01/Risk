#include "GameEngine.h"
#include <random>

void initializeGame(GameEngine &gameEngine) {

    //=========================================== Map/Deck Initialization ============================================//
    // Load the map
    MapLoader mapLoader;
    Map *currentGameMap = mapLoader.loadMap("../src/Map/MapFolder/World.map");

    // Obtain a list of all territories from the loaded map
    vector<Territory *> allTerritories = currentGameMap->getTerritories();

    Deck *deck = gameEngine.getDeck();
    deck->fillDeck(5);
    deck->shuffleDeck();
    cout << "\n";
    deck->printDeck();

    //============================================== Player Strategies ===============================================//
    auto *human = new HumanPlayerStrategy();
    auto *aggressive = new AggressivePlayerStrategy();
    //auto* benevolent = new BenevolentPlayerStrategy();
    //auto* neutral = new NeutralPlayerStrategy();
    //auto* cheater = new CheaterPlayerStrategy();

    //============================================ Player/Hand Creation ==============================================//

    // Create Player 1 and assign random territories (between 1 and 5)
    auto *player1 = new Player({}, new Hand(), new OrdersList(), 1);
    player1->setReinforcement(50);
    player1->setGameEngine(&gameEngine);
    player1->setDeck(deck);
    player1->setStrategy(aggressive);

    for (int i = 0; i < 5; ++i) {
        Card *drawnCard = deck->drawACard();
        player1->getHand()->addCard(drawnCard);
    }

    // Create Player 2 and assign random territories (between 1 and 5)
    auto *player2 = new Player({}, new Hand(), new OrdersList(), 2);
    player2->setReinforcement(0);
    player2->setGameEngine(&gameEngine);
    player2->setDeck(deck);
    player2->setStrategy(human);

    for (int i = 0; i < 5; ++i) {
        Card *drawnCard = deck->drawACard();
        player2->getHand()->addCard(drawnCard);
    }

    //============================================= Territory Assignment =============================================//
    // Shuffle the territories randomly
    shuffle(allTerritories.begin(), allTerritories.end(), mt19937(random_device()()));

    // Assign territories to players
    for (size_t i = 0; i < allTerritories.size(); ++i) {
        if (i % 2 == 0 && player1->getTerritories().size() < 5) {
            Territory *territory = allTerritories[i];
            player1->addTerritory(territory);
            territory->setOwnerId(player1->getID());
            territory->continentName = currentGameMap->getContinentById(territory->getContinentId())->getName();
        } else if (player2->getTerritories().size() < 5) {
            Territory *territory = allTerritories[i];
            player2->addTerritory(territory);
            territory->setOwnerId(player2->getID());
            territory->continentName = currentGameMap->getContinentById(territory->getContinentId())->getName();
        }
    }

    //================================================= Player Stats =================================================//
    vector<Territory *> player1Territories = player1->getTerritories();
    cout << "\n================================== Player 1's territories & cards =================================="
         << endl;
    for (const auto &territory: player1Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }
    cout << player1->getHand() << endl;

    vector<Territory *> player2Territories = player2->getTerritories();
    cout << "================================== Player 2 territories & cards =================================="
         << endl;
    for (const auto &territory: player2Territories) {
        cout << "Territory Name: " << territory->getName() << endl;
        // You can print other information about the territory here
        cout << "Continent: " << territory->getContinentName() << endl;
        cout << "Army Count: " << territory->getArmyCount() << endl;
        // Add more information if needed
        cout << endl;
    }
    cout << player2->getHand() << endl;

    //================================================= Final Setup ==================================================//
    // Set the map and players in the game engine
    gameEngine.setGameMap(currentGameMap);
    gameEngine.setPlayers({player1, player2});
}

//=============================================== testPlayerStrategies ===============================================//
int testPlayerStrategies() {
    auto *gameEngine = new GameEngine;

    initializeGame(*gameEngine);
    gameEngine->mainGameLoop();
    gameEngine->cleanupResources();

    delete gameEngine;

    return 0;
}