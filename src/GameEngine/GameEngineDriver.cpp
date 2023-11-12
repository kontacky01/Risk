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
    Player *player[4];
    Deck *theDeck = new Deck();
    Card *card1 = new Card();
    Card *card2 = new Card();
    card1->setType("bomb");
    card2->setType("blockade");

    theDeck->fillDeck(3);                                                 // Fill the deck with cards

    for (int i = 0; i < 4; ++i) {                                                    // Initialize 4 players
        player[i] = new Player();                                                    // Create a new player
        Hand* hand = new Hand();
        hand->addCard(card1);
        player[i]->setHand(hand);
        player[i]->setDeck(theDeck);
        player[i]->orderList = new OrdersList();                                     // Create the player's orders list
        cout << player[i]->getReinforcement() << endl;                               // Output the units
        player[i]->setGamePhase(gamePhase);                                          // Set the game phase
    }
    player[0]->setReinforcement(50);                                              // Give the players random army units
    player[1]->setReinforcement(0);
    player[2]->setReinforcement(25);
    player[3]->setReinforcement(10);

    cout << "****************************************" << endl;
    cout << "           Testing MainGameLoop         " << endl;
    cout << "****************************************" << endl;

    cout << "Players are now in the " << gamePhase << " [reinforcement] phase!\n" << endl;  // Output the units
    cout << "...Reinforcement Army Units (Before [reinforcement] Phase)..." << endl;
    cout << "Player Test0 has " << player[0]->getReinforcement() << " reinforcements" << endl;  // Output the units
    cout << "Player Test1 has " << player[1]->getReinforcement() << " reinforcements" << endl;
    cout << "Player Test2 has " << player[0]->getReinforcement() << " reinforcements" << endl;  // Output the units
    cout << "Player Test3 has " << player[1]->getReinforcement() << " reinforcements\n" << endl;
    cout << "...Reinforcement Army Units (After [reinforcement] Phase)..." << endl;

    int baseReinforcement = max(3, static_cast<int>(player->getTerritories().size() / 3));
    player->setReinforcement(player->getReinforcement() + baseReinforcement);

    // if player owns continent, award control bonus value
    vector<int> continentBonuses = player->continentOwnershipComplete();
    for (int bonus: continentBonuses) {
        player->setReinforcement(player->getReinforcement() + bonus);
    }




    cout << "Player Test0 has " << player[0]->getReinforcement() << " reinforcements" << endl;  // Output the units
    cout << "Player Test1 has " << player[1]->getReinforcement() << " reinforcements" << endl;
    cout << "Player Test2 has " << player[0]->getReinforcement() << " reinforcements" << endl;  // Output the units
    cout << "Player Test3 has " << player[1]->getReinforcement() << " reinforcements\n" << endl;

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