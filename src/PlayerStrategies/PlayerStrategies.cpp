#include <set>
#include "PlayerStrategies.h"

using namespace std;

/********************************************** Human Strategy ********************************************************/
string HumanPlayerStrategy::getStrategyType() {
    return "human";
}

vector<Territory *> HumanPlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> HumanPlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void HumanPlayerStrategy::issueOrder(Player *player, string orderName) {
    //cards: "bomb", "blockade", "airlift", "diplomacy" -- "reinforcement" (not associated with any order)
    //orders: "bomb", "deploy", "advance", "blockade", "airlift", "negotiate"

    int armyUnits;
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
        for (auto &card: player->getHand()->hand) {
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

/********************************************** Aggressive Strategy ***************************************************/
string AggressivePlayerStrategy::getStrategyType() {
    return "aggressive";
}

vector<Territory *> AggressivePlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> AggressivePlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void AggressivePlayerStrategy::issueOrder(Player *player, string orderName) {
    int armyUnits = player->getReinforcement();
    int topArmyCount = 0;
    Territory *strongestTerritory = (player->getTerritories())[0];
    Territory *attackTargetTerritory;
    Territory *currentTerritory;

    transform(orderName.begin(), orderName.end(), orderName.begin(),
              [](unsigned char c) { return tolower(c); });

    cout << "\n~~~~~~ Issuing Orders in Aggressive Player mode!";

    if (!strongestTerritory) {
        // Find the strongest territory only on the first turn
        for (int i = 0; player->getTerritories().size() > i; i++) {
            Territory *currentTerritory = (player->getTerritories())[i];
            if (currentTerritory->getArmyCount() > topArmyCount) {
                topArmyCount = currentTerritory->getArmyCount();
                strongestTerritory = currentTerritory;
            }
        }
    }
    orderName = "deploy";
    if (player->getReinforcement() > 0 && orderName == "deploy") {
        Order *deployOrder = new Deploy(); // create a deploy order

        strongestTerritory->setArmyCount(strongestTerritory->getArmyCount() + armyUnits);
        player->addTerritoryToList(strongestTerritory, "defend");
        player->orderList->addOrder(deployOrder);
        player->reinforcements -= armyUnits;
        cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";
        cout << "\n" << "Your strongest territory [" << strongestTerritory->getName() << "] now has "
             << strongestTerritory->getArmyCount()
             << " army units!\n";
        toDefend(player);

        orderName = "advance";
        if (player->getReinforcement() == 0 && orderName == "advance") {
            cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";
            if (strongestTerritory->getArmyCount() > 0) {
                vector<Territory *> adjacentTerritories = player->getGameEngine()->gameMap()->getTerritory(
                        strongestTerritory->getName())->getAdjacencyList();
                attackTargetTerritory = player->getGameEngine()->gameMap()->getTerritory(
                        adjacentTerritories[0]->getName());

                bool isAdjacent = false;
                for (int i = 0; i < adjacentTerritories.size(); i++) {
                    if (player->getGameEngine()->gameMap()->getTerritory(
                            adjacentTerritories[i]->getName())->getOwnerId() != player->getID()) {
                        isAdjacent = true;
                        Order *advanceOrder = new Advance(); // create an advance order
                        attackTargetTerritory = player->getGameEngine()->gameMap()->getTerritory(
                                adjacentTerritories[i]->getName());
                        player->addTerritoryToList(attackTargetTerritory, "attack"); // add to attack list
                        strongestTerritory->subFromArmy(armyUnits); // subtract from source
                        player->orderList->addOrder(advanceOrder); // add order to list
                        toAttack(player);
                        break;
                    } else {
                        cout << "\nInvalid: Territory " << attackTargetTerritory
                             << " is not adjacent and cannot be attacked!\n";
                    }
                }
            }
        }
        orderName = "";
        player->getHand()->printHand();

        for (auto it = player->getHand()->hand.begin(); it != player->getHand()->hand.end();) {
            string cardType = (*it)->getType();
            if (cardType == "bomb" || cardType == "blockade" || cardType == "airlift") {
                orderName = cardType;
                cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";
                player->playCard(*it, player->getDeck(), player->orderList);
                cout << player->orderList;
                //player->getHand()->printHand();
            } else {
                ++it;
            }
        }
    }
}

//================================ benevolent player ================================
string BenevolentPlayerStrategy::getStrategy() {
    return "Benevolent";
}

vector<Territory *> BenevolentPlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> BenevolentPlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void BenevolentPlayerStrategy::issueOrder(Player *player) {

    //cards: "bomb", "blockade", "airlift", "diplomacy" -- "reinforcement" (not associated with any order)
    //orders: "bomb", "deploy", "advance", "blockade", "airlift", "negotiate"

    //since benevolent player can only deploy/advance on its weakest contries
    //that means we check and deal with countires in toDefend() and accept all orders except bomb
    //and in advance we only advance in on territories in toDefend() not toAttack()

    int armyUnits;
    string orderName;

    cout << "\nEnter an order (blockade, deploy, advance, negotiate): ";
    cin >> orderName;
    transform(orderName.begin(), orderName.end(), orderName.begin(),
              [](unsigned char c) { return tolower(c); });
    cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";

    if (orderName == "deploy") {
        string territoryName;
        Deploy *deployOrder;
    
        toDefend(player);
        cout << "\nEnter the territory you wish to deploy to from your weakest countries to defend: ";
        cin >> territoryName;

        cout << "\nEnter the number of army units you wish to deploy: ";
        cin >> armyUnits;

        vector<Territory *> weakestToDefend = toDefend(player);

        Territory *targetTerritory = nullptr;
        for (auto &territory: weakestToDefend) {
            if (territory->getName() == territoryName) {
                targetTerritory = territory;
                deployOrder = new Deploy(player,targetTerritory,armyUnits);
                player->orderList->addOrder(deployOrder);
                deployOrder->execute();
                break;
            }
        }
        if (!targetTerritory) {
            cout << "\nInvalid: Target Territory '" << territoryName << "' not found in your weakest countries to defend.\n";
        }
        //if(deployOrder) {delete deployOrder;deployOrder = NULL;}
    }
    if (orderName == "advance") {
        string sourceTerritoryName, targetTerritoryName;
        Advance *advanceOrder;

        cout << "\nEnter the territory you wish to move army units FROM: ";
        cin >> sourceTerritoryName;

        cout << "\nEnter the territory you wish to move army units TO: ";
        cin >> targetTerritoryName;

        cout << "\nEnter the amount of army units you wish to advance TO " << targetTerritoryName << ": ";
        cin >> armyUnits;

        Territory *sourceTerritory = player->getGameEngine()->gameMap()->getTerritory(sourceTerritoryName);
        vector<Territory *> weakestToDefend = toDefend(player);

        Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(targetTerritoryName);
        for (auto &territory: weakestToDefend) {
            if (territory->getName() == targetTerritoryName) {
                targetTerritory = territory;
                advanceOrder = new Advance(player,sourceTerritory,targetTerritory,armyUnits);
                player->orderList->addOrder(advanceOrder);
                advanceOrder->execute();
                break;
            }
        }
        if (!targetTerritory) {
            cout << "\nInvalid: Target Territory '" << targetTerritoryName << "' not found in your weakest countries to defend.";
            cout << "\nPlayer is a Benevolent Player and cannot Attack!\n";
        }
        //if(advanceOrder){delete advanceOrder;advanceOrder = NULL;}
    }
    if(orderName == "airlift" || orderName == "blockade" || orderName == "bomb" ||
         orderName == "diplomacy" || orderName == "negotiate"){
            bool hasCard = false;
        // check if the player has the card in their hand
        for (auto &card : player->getHand()->hand) {
            if (card->getType() == orderName) {
                hasCard = true;
                cout << "\n~~~~~~ You have issued an order to: [" << card->getType() << "] !\n";
                player->playCard(card, player->getDeck(), player->orderList);

                if(orderName == "bomb"){
                    cout << "\nPlayer is a Benevolent Player and cannot Attack!\n";
                }
                if(orderName == "blockade"){
                    string territoryName;
                    Blockade *blockadeOrder;
                    Player *anyNeutralPlayerInGame;

                    vector<Player *> gamePlayers = player->getGameEngine()->getPlayers();
                    for (auto &otherplayer : gamePlayers) {
                        if(dynamic_cast<NeutralPlayerStrategy*>(player->getStrategy()) != nullptr){
                            anyNeutralPlayerInGame = otherplayer;

                            cout << "\nEnter the territory you wish to blockade: ";
                            cin >> territoryName;

                            Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(territoryName);
                            
                            if (targetTerritory) {
                                blockadeOrder = new Blockade(player,anyNeutralPlayerInGame,targetTerritory);
                                player->orderList->addOrder(blockadeOrder);
                                blockadeOrder->execute();
                            }
                            else {
                                cout << "\nInvalid: Target Territory '" << territoryName << "' not found in current game map.\n";
                            }
                            break;
                        }
                        else{
                            cout << "\nThe current game tournament has no Neutral Player!\n";
                        }
                    }
                    //if(anyNeutralPlayerInGame){delete anyNeutralPlayerInGame;; anyNeutralPlayerInGame = NULL;}
                    //if(blockadeOrder){delete blockadeOrder; blockadeOrder = NULL;}
                }
                if(orderName == "airlift"){
                    string sourceTerritoryName, targetTerritoryName;
                    Airlift *airliftOrder;

                    cout << "\nEnter the territory you wish to move army units FROM: ";
                    cin >> sourceTerritoryName;

                    cout << "\nEnter the territory you wish to move army units TO: ";
                    cin >> targetTerritoryName;

                    cout << "\nEnter the amount of army units you wish to advance TO " << targetTerritoryName << ": ";
                    cin >> armyUnits;

                    Territory *sourceTerritory = player->getGameEngine()->gameMap()->getTerritory(sourceTerritoryName);
                    Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(targetTerritoryName);

                    if (sourceTerritory && targetTerritory) {
                        airliftOrder = new Airlift(player,sourceTerritory,targetTerritory,armyUnits);
                        player->orderList->addOrder(airliftOrder);
                        airliftOrder->execute();
                    }
                    else {
                        cout << "\nInvalid Source or Target Territories: '" << sourceTerritory << " or " << targetTerritory << "' not found in current game map.\n";
                        return;
                    }
                    //if(airliftOrder){delete airliftOrder; airliftOrder = NULL;}
                }
                if(orderName == "negotiate"){
                    int id;
                    Player *playerToNegotiate;
                    Negotiate *negotiateOrder;
                    cout << "\nEnter the player(ID) you wish to negotiate with: ";
                    cin >> id;

                    vector<Player *> gamePlayers = player->getGameEngine()->getPlayers();
                    for (auto &otherplayer : gamePlayers) {
                            if(otherplayer->getID() == id){
                                playerToNegotiate = otherplayer;
                                negotiateOrder = new Negotiate(player,playerToNegotiate);
                                player->orderList->addOrder(negotiateOrder);
                                negotiateOrder->execute();
                                break;
                            }
                            else{
                                cout << "\nThere is no such player in the current game tournament!\n";
                            }
                    }
                    //if(playerToNegotiate){delete playerToNegotiate; playerToNegotiate = NULL;}
                    //if(negotiateOrder){delete negotiateOrder; negotiateOrder = NULL;}

                }
                cout << player->orderList;
                player->getHand()->printDeck();
                player->getDeck()->printDeck();
                break;
            }
        }
        if(!hasCard){
            cout << "\nPlayer does not have a valid card to issue the order " << orderName <<"\n";
        }
    }
}
//================================ neutral player ================================
string NeutralPlayerStrategy::getStrategy() {
    return "Neutral";
}

vector<Territory *> NeutralPlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> NeutralPlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void NeutralPlayerStrategy::issueOrder(Player *player) {
    //cards: "bomb", "blockade", "airlift", "diplomacy" -- "reinforcement" (not associated with any order)
    //orders: "bomb", "deploy", "advance", "blockade", "airlift", "negotiate"

    cout << "\nPlayer is NEUTRAL and cannot issue orders!\n";

}
/********************************************** Cheater Strategy ******************************************************/
string CheaterPlayerStrategy::getStrategyType() {
    return "cheater";
}

vector<Territory *> CheaterPlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> CheaterPlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void CheaterPlayerStrategy::issueOrder(Player *player, string orderName) {
    cout << "\n~~~~~~ Issuing Orders in Cheater Player mode!\n";

    // Create a vector to keep track of territories already conquered in this turn
    vector<Territory *> conqueredTerritories;

    // Loop through the player's territories
    for (auto &territory : player->getTerritories()) {
        // Get the adjacent territories
        vector<Territory *> adjacentTerritories = territory->getAdjacencyList();

        // Loop through adjacent territories
        for (auto &adjacentTerritory : adjacentTerritories) {
            // Check if the adjacent territory is not owned by the player and has not been conquered in this turn
            if (adjacentTerritory->getOwnerId() != player->getID() &&
                find(conqueredTerritories.begin(), conqueredTerritories.end(), adjacentTerritory) == conqueredTerritories.end()) {
                // Conquer the territory
                adjacentTerritory->setOwnerId(player->getID());
                conqueredTerritories.push_back(adjacentTerritory);
                cout << "Player " << player->getID() << " conquered territory: " << adjacentTerritory->getName() << endl;
            }
        }
    }
}
