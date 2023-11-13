#include "Player.h"

using namespace std;

/************************************************************ Player **************************************************************/
/**
 * Constructor with with an argument list
 */
Player::Player(vector<Territory *> t, Hand *h, OrdersList *o, int id) {
    territories = t;
    hand = h;
    orderList = o;
    this->id = id;
    this->reinforcements = 0;

    // if seed is set to 1, the generator is reinitialized to its initial value
    // and produces the same values as before any call to rand or srand
    srand((unsigned) time(NULL));
}

/**
 *  Helper method to list attack/assetList territories
 */
void Player::printTerritories(vector<Territory *> territories) {
    for (int i = 0; i < territories.size(); i++) {
        cout << i << ")" << territories.at(i);
    }
}

/**
 * Copy Constructor
 */
Player::Player(const Player &p) {
    cout << "...Player Copy constructor was called...\n";
    // it's a vector, hence we don't create a new pointer to the territories
    for (int i = 0; i < p.territories.size(); i++) {
        Territory *currentT = p.territories.at(i);
        territories.push_back(currentT);
    }

    // create a new hand
    hand = p.hand ? new Hand(*p.hand) : nullptr;

    // create a new orderlist
    orderList = p.orderList ? new OrdersList(*p.orderList) : nullptr;

    // it's not a pointer, so we just increase the ID 1
    id = p.id + 1;
}

/**
 * Destructor
 */
Player::~Player() {
    cout << "...Player destructor was called...\n";
    for (int i = 0; i < territories.size(); i++) {
        delete territories[i];
        territories.at(i) = nullptr;
    };
    territories.clear();

    delete hand;
    hand = nullptr;

    delete orderList;
    orderList = nullptr;
}

/**
 * Default Constructor
 */
Player::Player() {
    this->id = 0;
}

int Player::getID() const { return this->id; }

void Player::setGamePhase(string gamePhase) {
    this->gamePhase = gamePhase;
}

string Player::getGamePhase() {
    return gamePhase;
}

vector<int> Player::continentOwnershipComplete() {
    vector<int> controlBonuses; // Store control bonuses for continents
    vector<string> awardedContinents; // Store the names of awarded continents

    // Iterate through all continents on the game map
    for (auto &continent : gameEngine->gameMap()->continentList) {
        int territoriesInCurrentContinent = continent->territoriesInContinents.size();
        int territoryOwnershipCount = 0;

        // Check how many territories in the continent are owned by the player
        for (auto &territory : territories) {
            if (territory->getContinentName() == continent->getName()) {
                territoryOwnershipCount++;
            }
        }
        // Check if the player owns all territories in the continent and it hasn't been awarded already
        if (territoriesInCurrentContinent == territoryOwnershipCount &&
            find(awardedContinents.begin(), awardedContinents.end(), continent->getName()) == awardedContinents.end()) {
            // Get the bonus value for the continent and add it to the controlBonuses vector
            int bonus = continent->getControlBonusValue();
            controlBonuses.push_back(bonus);

            // Add the continent to the awardedContinents vector to track it
            awardedContinents.push_back(continent->getName());
        }
    }
    return controlBonuses; // Return the control bonuses for continents
}

/*vector<int> Player::continentOwnershipComplete() {
    int territoriesInCurrentContinent;
    std::vector<int> controlBonuses;
    // iterate through the continents on the game map and get number of territories in each
    for (auto &continent: gameEngine->gameMap()->continentList) {
        territoriesInCurrentContinent = continent->territoriesInContinents.size();
        int territoryOwnershipCount = 0;

        for (auto &territory: territories) {
            if (territory->getContinentName() == continent->getName()) {
                territoryOwnershipCount++;
            }
        }
        // If player owns all territories in the continent, get its control bonus value
        if (territoriesInCurrentContinent == territoryOwnershipCount) {
            controlBonuses.push_back(continent->getControlBonusValue());
        }
    }
    return controlBonuses;
}*/

int Player::getReinforcement() const { return this->reinforcements; }

void Player::setReinforcement(int r) { this->reinforcements = r; }

void Player::addReinforcement(int r) { this->reinforcements = this->reinforcements + r; }

void Player::subtractReinforcements(int r) { this->reinforcements = this->reinforcements - r; }

vector<Territory *> Player::getTerritories() { return this->territories; }

void Player::addTerritory(Territory *t) {
    t->setOwnerId(this->id);
    this->territories.push_back(t);
}

void Player::removeTerritory(Territory *t) {
    auto it = find(territories.begin(), territories.end(), t);
    territories.erase(it);
}

/**
 * @brief deletes territory and sets
 */
void Player::eraseTerritory(Territory *t) {
    if (territories.size() == 0) {
        cout << "Error: Territory list is empty\n";
        return;
    }
    if (!ownsTerritory(t)) {
        cout << "Error: Player does not own Territory\n";
        return;
    }
    if (t) {
        t->setOwnerId(0);
        t->setArmyCount(0);
        auto it = find(territories.begin(), territories.end(), t);
        if (it != territories.end()) {
            territories.erase(it);
        }
    } else {
        cout << "The territory you are attempting to erase is NULL!!";
    }
}

OrdersList *Player::getOrdersList() { return this->orderList; }

bool Player::ownsTerritory(Territory *t) { return t->getOwnerId() == this->id; }

Hand *Player::getHand() { return this->hand; }

void Player::setHand(Hand *hand) {
    this->hand = hand;
}

/**
 * Returns a random list of territories that are assigned to the user which they
 * would like to defend
 */
vector<Territory *> Player::toDefend() {
    vector<Territory *> assetList;
    // if no territories were init
    if (defendList.empty()) {
        cout << "...There are no territories to defend...\n";
        return assetList;
    }
    int index = rand() % defendList.size();
    for (int i = 0; i <= index; i++) {
        assetList.push_back(defendList.at(i));
    }
    cout << "\nTerritories to defend:\n -------------------\n";
    printTerritories(assetList);
    return assetList;
}

/**
 * Returns a random list of territories that the user would like to attack
 */
vector<Territory *> Player::toAttack() {
    vector<Territory *> enemyList;
    if (attackList.empty()) {
        cout << "...There are no territories to attack...\n";
        return enemyList;
    }
    int index = rand() % attackList.size();
    for (int i = 0; i <= index; i++) {
        enemyList.push_back(attackList.at(i));
    }
    cout << "\nTerritories to attack:\n-------------------\n";
    printTerritories(enemyList);

    return enemyList;
}

void Player::addTerritoryToList(Territory *territory, const string &listType) {
    vector<Territory *> *targetList;
    if (listType == "defend") {
        targetList = &defendList;
    } else {
        targetList = &attackList;
    }
    // add the territory if it's not already in the list
    if (find(targetList->begin(), targetList->end(), territory) == targetList->end()) {
        targetList->push_back(territory);
    }
    // sort the list in descending order of army count
    sort(targetList->begin(), targetList->end(), [](const Territory *a, const Territory *b) {
        return a->getArmyCount() > b->getArmyCount();
    });
}


//cards: "bomb", "blockade", "airlift", "diplomacy" -- "reinforcement" (not associated with any order)
//orders: "bomb", "deploy", "advance", "blockade", "airlift", "negotiate"

void Player::issueOrder() {
    int armyUnits;
    string orderName;
    cout << "Enter an order (bomb, reinforcement, blockade, airlift, diplomacy, deploy, advance): ";
    cin >> orderName;
    transform(orderName.begin(), orderName.end(), orderName.begin(),
              [](unsigned char c) { return std::tolower(c); });

    if (this->getReinforcement() > 0 && orderName == "deploy") {
        Order *deployOrder = new Deploy(); // create a deploy order
        cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";

        string territoryName;
        // ask for the territory ID
        cout << "\nEnter the territory you wish to deploy to: ";
        cin >> territoryName;

        // ask for the number of units
        cout << "\nEnter the number of army units you wish to deploy: ";
        cin >> armyUnits;

        // check if the territory is owned by the player
        Territory *targetTerritory = nullptr;
        //for (auto & territory : currentTerritoryList) {
        for (auto &territory: territories) {
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
        if (targetTerritory->getOwnerId() == this->getID()) {
            // allocate reinforcements to the territory
            targetTerritory->setArmyCount(targetTerritory->getArmyCount() + armyUnits);
            // add the territory to the defend list
            addTerritoryToList(targetTerritory, "defend");
            // add the "deploy" order to the player's orders list
            this->orderList->addOrder(deployOrder); // add order to list
            cout << "\n" << targetTerritory->getName() << " now has " << targetTerritory->getArmyCount()
                 << " army units!\n";
            cout << orderList;
        } else {
            cout << "\nInvalid: You do not own " << territoryName << ".\n";
            delete deployOrder;
            return;
        }
    } else if (this->getReinforcement() == 0 && orderName == "deploy") {
        cout << "\nInvalid: You have deployed all your army units.\n";

    } else if (this->getReinforcement() > 0 && orderName == "advance") {
        cout << "\nInvalid: You still have " << this->getReinforcement() << " army units to deploy!\n";

    } else if (this->getReinforcement() == 0 && orderName == "advance") {
        Order *advanceOrder = new Advance(); // create an advance order
        cout << "\n~~~~~~ You have issued an order to: [" << orderName << "] !\n";

        string sourceTerritoryName, targetTerritoryName;
        cout << "\nEnter the territory you wish to move army units FROM: ";
        cin >> sourceTerritoryName;
        cout << "\nEnter the territory you wish to move army units TO: ";
        cin >> targetTerritoryName;
        cout << "\nEnter the amount of army units you wish to advance TO " << targetTerritoryName << ": ";
        cin >> armyUnits;

        Territory *sourceTerritory = nullptr;
        //for (auto &territory: currentTerritoryList) {
        for (auto &territory: territories) {
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
        Territory *targetTerritory = nullptr;
        //for (auto &territory: currentTerritoryList) {
        for (auto &territory: territories) {
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
        if (targetTerritory->getOwnerId() == this->getID()) { // player is trying to DEFEND
            addTerritoryToList(targetTerritory, "defend"); // add to defend list
            sourceTerritory->subFromArmy(armyUnits); // subtract from source
            targetTerritory->addToArmyCount(armyUnits); // add to target
            this->orderList->addOrder(advanceOrder); // add order to list
            cout << "\n" << targetTerritory->getName() << " now has " << targetTerritory->getArmyCount()
                 << " army units!";
            cout << "\n" << sourceTerritory->getName() << " now has " << sourceTerritory->getArmyCount()
                 << " army units!\n";
        } //else
        if (targetTerritory->getOwnerId() != this->getID()) {
            // player is trying to ATTACK, check if target territory is adjacent
            if (find(sourceTerritory->getAdjacencyList().begin(),
                     sourceTerritory->getAdjacencyList().end(),
                     targetTerritory) != sourceTerritory->getAdjacencyList().end()) {
                // Target is neighboring
                addTerritoryToList(targetTerritory, "attack"); // add to attack list
                sourceTerritory->subFromArmy(armyUnits); // subtract from source
                this->orderList->addOrder(advanceOrder); // add order to list
            } else {
                cout << "\nInvalid: Territory " << targetTerritoryName << " is not adjacent and cannot be attacked!\n";
                delete advanceOrder; // clean up allocated memory
            }
        }
    } else if (this->getReinforcement() > 0 && (orderName == "airlift" || orderName == "blockade" ||
                                                orderName == "bomb" || orderName == "diplomacy" ||
                                                orderName == "negotiate")) {
        cout << "\nInvalid: You still have " << this->getReinforcement() << " army units to deploy!\n";

    } else if (this->getReinforcement() == 0 && (orderName == "airlift" || orderName == "blockade" ||
                                                 orderName == "bomb" || orderName == "diplomacy" ||
                                                 orderName == "negotiate")) {
        bool hasCard = false; // check if the player has the card in their hand
        for (auto &card: this->getHand()->hand) {
            if (card->getType() == orderName) {
                playCard(card, deck, orderList);
                cout << "\n~~~~~~ You have issued an order to: [" << card->getType() << "] !\n";
                hasCard = true;
                break;
            }
        }
        if (!hasCard) {
            cout << "\nYou do not have a [" << orderName << "] card in your hand!\n";
        }
    } else {
        cout << "\nInvalid: There is no such card.\n";
    }
}

/**
 * Override the stream operator for Player
 */
ostream &operator<<(ostream &out, Player *p) {
    out << "Printing info about player ID: " << p->id
        << "\n********************************\n\n"
        << " Reinforcements: " << p->getReinforcement() << "\n\n"
        << " Info about territories: \n ------------------------\n";
    p->printTerritories(p->territories);
    out << p->orderList;
    out << p->hand;
    return out;
}

string Player::stringToLog() {
    return {};
}

void Player::playCard(Card *card, Deck *deck, OrdersList *OL) {
    this->hand->play(card, deck, OL);
}

void Player::setDeck(Deck *deck) {
    this->deck = deck;
}

OrdersList *Player::issuesOrder(Order *o) {
    orderList->addOrder(o);
    cout << "...Pushed a new order to orderList...\n";
    cout << "New order id: " << o->getOrderID() << "\n\n";
    return orderList;
}

Deck* Player::getDeck() {
    return deck;
}
