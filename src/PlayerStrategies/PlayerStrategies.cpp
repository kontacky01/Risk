#include "PlayerStrategies.h"

using namespace std;

//================================ human player ================================
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

    cout << "\nEnter an order (bomb, blockade, airlift, deploy, advance, negotiate): ";
    cin >> orderName;
    transform(orderName.begin(), orderName.end(), orderName.begin(),
              [](unsigned char c) { return tolower(c); });
    cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";

    if (orderName == "deploy") {
        string territoryName;
        Deploy *deployOrder;
    
        cout << "\nEnter the territory you wish to deploy to: ";
        cin >> territoryName;

        cout << "\nEnter the number of army units you wish to deploy: ";
        cin >> armyUnits;

        Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(territoryName);
        
        if (targetTerritory) {
            deployOrder = new Deploy(player,targetTerritory,armyUnits);
            player->orderList->addOrder(deployOrder);
            deployOrder->execute();
        }
        else {
            cout << "\nInvalid: Target Territory '" << territoryName << "' not found in current game map.\n";
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
        Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(targetTerritoryName);

        if (sourceTerritory && targetTerritory) {
            advanceOrder = new Advance(player,sourceTerritory,targetTerritory,armyUnits);
            player->orderList->addOrder(advanceOrder);
            advanceOrder->execute();
        }
        else {
            cout << "\nInvalid Source or Target Territories: '" << sourceTerritory << " or " << targetTerritory << "' not found in current game map.\n";
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
                    string territoryName;
                    Bomb *bombOrder;
                
                    cout << "\nEnter the territory you wish to bomb: ";
                    cin >> territoryName;

                    Territory *targetTerritory = player->getGameEngine()->gameMap()->getTerritory(territoryName);
                    
                    if (targetTerritory) {
                        bombOrder = new Bomb(player,targetTerritory);
                        player->orderList->addOrder(bombOrder);
                        bombOrder->execute();
                    }
                    else {
                        cout << "\nInvalid: Target Territory '" << territoryName << "' not found in current game map.\n";
                    }
                    //if(bombOrder){delete bombOrder; bombOrder = NULL;}
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

//================================ Aggressive player ================================
string AggressivePlayerStrategy::getStrategy() {
    return "Aggressive";
}

vector<Territory *> AggressivePlayerStrategy::toDefend(Player *player) {
    return player->toDefend();
}

vector<Territory *> AggressivePlayerStrategy::toAttack(Player *player) {
    return player->toAttack();
}

void AggressivePlayerStrategy::issueOrder(Player *player) {

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