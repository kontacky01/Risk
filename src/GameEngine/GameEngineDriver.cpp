#include "GameEngine.h"
#include "Player.h"
#include <algorithm>

void testGameStates() {
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
}

/*void testReinforcementPhase() {
    GameEngine gameEngine; // Assuming this sets up the map and players.

    // Mock data setup
    const int MIN_TERRITORIES_FOR_BONUS = 3;
    const int INITIAL_REINFORCEMENTS = 50;
    const int BASE_REINFORCEMENTS = 3;

    std::vector<std::vector<Territory *>> mockTerritoryCounts = {
            std::vector<Territory *>(), // Player 1 territories
            std::vector<Territory *>(), // Player 2 territories
            std::vector<Territory *>()  // Player 3 territories
    };

    std::vector<int> mockContinentBonuses = {5, 0, 10}; // Assume the first player has a continent, others don't
    std::vector<int> territoryCounts = {12, 15, 9};


    for (size_t i = 0; i < gameEngine.getPlayers().size(); ++i) {
        for (int j = 0; j < territoryCounts[i]; ++j) {
            mockTerritoryCounts[i].push_back(new Territory()); // Assuming Territory constructor is default
        }
        auto *territory = new Territory();
        // Now assign these mock territories to each player
        gameEngine.getPlayers()[i]->addTerritory(territory);
    }

    // Assign territories and continents to players
    for (size_t i = 0; i < gameEngine.getPlayers().size(); ++i) {
        auto player = gameEngine.getPlayers()[i];
        // Mock the territories
        for (Territory *territory: mockTerritoryCounts[i]) {
            player->addTerritory(territory);
        }
        // Mock the continent bonus
        if (mockContinentBonuses[i] > 0) {
            player->addReinforcement(mockContinentBonuses[i]);
        }
    }

    // Run the reinforcement phase
    gameEngine.reinforcementPhase();

    // Verify the results
    for (size_t i = 0; i < gameEngine.getPlayers().size(); ++i) {
        auto player = gameEngine.getPlayers()[i];
        int expectedBaseReinforcements = std::max(BASE_REINFORCEMENTS,
                                                  static_cast<int>(player->getTerritories().size() /
                                                                   MIN_TERRITORIES_FOR_BONUS));
        int expectedReinforcements = INITIAL_REINFORCEMENTS + expectedBaseReinforcements + mockContinentBonuses[i];

        std::cout << "Player " << player->getID() << " has " << player->getReinforcement() << " reinforcements."
                  << std::endl;

        if (player->getReinforcement() != expectedReinforcements) {
            std::cout << "Test failed for player " << player->getID() << ": expected " << expectedReinforcements
                      << ", got " << player->getReinforcement() << std::endl;
        } else {
            std::cout << "Test passed for player " << player->getID() << std::endl;
        }
    }
}*/