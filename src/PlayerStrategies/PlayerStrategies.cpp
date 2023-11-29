#include "PlayerStrategies.h"

using namespace std;

string HumanPlayerStrategy::getStrategy() {
    return "human";
}

vector<Territory *> HumanPlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> HumanPlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void HumanPlayerStrategy::issueOrder(Player *player) {
    //cards: "bomb", "blockade", "airlift", "diplomacy" -- "reinforcement" (not associated with any order)
    //orders: "bomb", "deploy", "advance", "blockade", "airlift", "negotiate"

    int armyUnits;
    string orderName;
    cout << "Enter an order (bomb, reinforcement, blockade, airlift, diplomacy, deploy, advance): ";
    cin >> orderName;
    transform(orderName.begin(), orderName.end(), orderName.begin(),
              [](unsigned char c) { return tolower(c); });

    if (player->getReinforcement() > 0 && orderName == "deploy") {
        Order *deployOrder = new Deploy(); // create a deploy order
        cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";

        string territoryName;
        // ask for the territory ID
        cout << "\nEnter the territory you wish to deploy to: ";
        cin >> territoryName;

        // ask for the number of units
        cout << "\nEnter the number of army units you wish to deploy: ";
        cin >> armyUnits;

        // Check if player has enough reinforcement units to deploy
        if (armyUnits > player->getReinforcement()) {
            cout << "Invalid: You cannot deploy more units than you have available." << endl;
            cout << "You have " << player->getReinforcement() << " units available." << endl;
            return; // Return early if the player does not have enough units
        }

        // check if the territory is owned by the player
        Territory *targetTerritory = nullptr;
        //for (auto & territory : currentTerritoryList) {
        for (auto &territory: player->territories) {
            if (territory->getName() == territoryName) {
                targetTerritory = territory;
                break;
            }
        }
        // check if the territory was found
        if (!targetTerritory) {
            cout << "\nInvalid: Territory '" << territoryName << "' not found.\n";
            delete deployOrder;
            return;
        }
        // now check if the player owns the territory
        if (targetTerritory->getOwnerId() == player->getID()) {
            // allocate reinforcements to the territory
            targetTerritory->setArmyCount(targetTerritory->getArmyCount() + armyUnits);
            // add the territory to the defend list
            player->addTerritoryToList(targetTerritory, "defend");
            // add the "deploy" order to the player's orders list
            player->orderList->addOrder(deployOrder); // add order to list
            player->reinforcements -= armyUnits;
            cout << "\n" << targetTerritory->getName() << " now has " << targetTerritory->getArmyCount()
                 << " army units!\n";
            cout << player->orderList;
        } else {
            cout << "\nInvalid: You do not own " << territoryName << ".\n";
            delete deployOrder;
            return;
        }
    } else if (player->getReinforcement() == 0 && orderName == "deploy") {
        cout << "\nInvalid: You have deployed all your army units.\n";

    } else if (player->getReinforcement() > 0 && orderName == "advance") {
        cout << "\nInvalid: You still have " << player->getReinforcement() << " army units to deploy!\n";

    } else if (player->getReinforcement() == 0 && orderName == "advance") {
        Order *advanceOrder = new Advance(); // create an advance order
        cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";

        string sourceTerritoryName, targetTerritoryName;
        cout << "\nEnter the territory you wish to move army units FROM: ";
        cin >> sourceTerritoryName;
        cout << "\nEnter the territory you wish to move army units TO: ";
        cin >> targetTerritoryName;
        cout << "\nEnter the amount of army units you wish to advance TO " << targetTerritoryName << ": ";
        cin >> armyUnits;

        Territory *sourceTerritory = player->getGameEngine()->gameMap()->getTerritory(sourceTerritoryName);
        for (auto &territory: player->territories) {
            if (territory->getName() == sourceTerritoryName) {
                sourceTerritory = territory;
                break;
            }
        }
        if (!sourceTerritory) {
            cout << "\nInvalid: Source territory not found or does not exist.\n";
            delete advanceOrder;
            return;
        }
        if (sourceTerritory->getArmyCount() < armyUnits) {
            cout << "Invalid: Source territory does not have enough army units. It only has "
                 << sourceTerritory->getArmyCount() << " units.\n";
            delete advanceOrder;
            return;
        }
        Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(targetTerritoryName);
        for (auto &territory: player->territories) {
            if (territory->getName() == targetTerritoryName) {
                targetTerritory = territory;
                break;
            }
        }
        if (!targetTerritory) {
            cout << "\nInvalid: Target territory not found or does not exist.\n";
            delete advanceOrder; // clean up allocated memory
            return;
        }
        if (targetTerritory->getOwnerId() == player->getID()) { // player is trying to DEFEND
            player->addTerritoryToList(targetTerritory, "defend"); // add to defend list
            sourceTerritory->subFromArmy(armyUnits); // subtract from source
            targetTerritory->addToArmyCount(armyUnits); // add to target
            player->orderList->addOrder(advanceOrder); // add order to list
            cout << "\n" << targetTerritory->getName() << " now has " << targetTerritory->getArmyCount()
                 << " army units!";
            cout << "\n" << sourceTerritory->getName() << " now has " << sourceTerritory->getArmyCount()
                 << " army units!\n";
        } //else
        if (targetTerritory->getOwnerId() != player->getID()) {
            // player is trying to ATTACK, check if target territory is adjacent
            if (find(sourceTerritory->getAdjacencyList().begin(),
                     sourceTerritory->getAdjacencyList().end(),
                     targetTerritory) != sourceTerritory->getAdjacencyList().end()) {
                // Target is neighboring
                player->addTerritoryToList(targetTerritory, "attack"); // add to attack list
                sourceTerritory->subFromArmy(armyUnits); // subtract from source
                player->orderList->addOrder(advanceOrder); // add order to list
            } else {
                cout << "\nInvalid: Territory " << targetTerritoryName << " is not adjacent and cannot be attacked!\n";
                delete advanceOrder; // clean up allocated memory
            }
        }
    } else if (player->getReinforcement() > 0 && (orderName == "airlift" || orderName == "blockade" ||
                                                orderName == "bomb" || orderName == "diplomacy" ||
                                                orderName == "negotiate")) {
        cout << "\nInvalid: You still have " << player->getReinforcement() << " army units to deploy!\n";

    } else if (player->getReinforcement() == 0 && (orderName == "airlift" || orderName == "blockade" ||
                                                 orderName == "bomb" || orderName == "diplomacy" ||
                                                 orderName == "negotiate")) {
        bool hasCard = false; // check if the player has the card in their hand
        for (auto &card : player->getHand()->hand) {
            if (card->getType() == orderName) {
                cout << "\n~~~~~~ You have issued an order to: [" << card->getType() << "] !\n";
                player->playCard(card, player->getDeck(), player->orderList);
                hasCard = true;
                cout << player->orderList;
                player->getHand()->printDeck();
                player->getDeck()->printDeck();
                break;
            }
        }
        if (!hasCard) {
            cout << "\nYou do not have a [" << orderName << "] card in your hand!\n";
        }
    } else {
        cout << "\nInvalid: There is no such card.\n";
    }
    toDefend(player);
    toAttack(player);
}