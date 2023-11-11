#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include <algorithm>

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

void testMainGameLoop() {
    string gamePhase = "Reinforcement";
    Player *player[2];
    Deck *theDeck = new Deck();
    Card *card1 = new Card();
    card1->setType("bomb");

    theDeck->fillDeck(3);  // Fill the deck with cards

    // Initialize 2 players
    for (int i = 0; i < 2; ++i) {
        player[i] = new Player();  // Create a new player
        player[i]->setHand(new Hand());  // Allocate a new hand for the player
        player[i]->getHand()->addCard(card1);
        player[i]->orderList = new OrdersList();  // Create the player's orders list
        player[i]->setReinforcement(0);  // Give the player 50 army units
        cout << player[i]->getReinforcement() << endl;  // Output the units
        player[i]->setGamePhase(gamePhase);  // Set the game phase
    }

    string phase = player[1]->getGamePhase();
    cout << phase << endl;

    // issue orders and add them to orders list
    bool continueIssuingOrders = true;
    while (continueIssuingOrders) {
        string userInput;
        cout << "\nPlayer " << player[1]->getID() << ", would you like to issue an order? (YES/NO): ";
        cin >> userInput;
        cout << "\n";
        transform(userInput.begin(), userInput.end(), userInput.begin(),
                  [](unsigned char c) { return toupper(c); });
        if (userInput == "YES") {
            player[1]->issueOrder();

        } else if (userInput == "NO") {
            continueIssuingOrders = false;
        } else {
            std::cout << "\nInvalid input! Please enter YES or NO.";
        }
    }
    cout << player[1]->orderList << endl;

    for (int i = 0; i < 2; ++i) {
        delete player[i];
        player[i] = nullptr;
    }
    delete theDeck;
    theDeck = nullptr;
    delete card1;
    card1 = nullptr;
}