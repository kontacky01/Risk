#include <algorithm>
#include <cstdlib>
#include <memory>
#include <cctype>
#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"

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
        territories.at(i) = NULL;
    };
    territories.clear();

    delete hand;
    hand = NULL;

    delete orderList;
    orderList = NULL;
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


/**
 * Take in an order and add it into the OrderList
 */
void Player::issueOrder() {
    //cards: "bomb", "blockade", "airlift", "diplomacy" -- "reinforcement" (not associated with any order)
    //orders: "bomb", "deploy", "advance", "blockade", "airlift", "negotiate"
    string orderName;
    cout << "Enter an order (bomb, reinforcement, blockade, airlift, diplomacy, deploy, advance): ";
    cin >> orderName;
    transform(orderName.begin(), orderName.end(), orderName.begin(),
              [](unsigned char c) { return std::tolower(c); });

    if (this->getReinforcement() > 0 && orderName == "deploy") {
        Order *deployOrder = new Deploy(); // create a deploy order
        this->orderList->addOrder(deployOrder); // add to orders list
        cout << "You have issued an order to: [" << orderName << "] !" << endl;

    } else if (this->getReinforcement() == 0 && orderName == "deploy") {
        cout << "Invalid: You have deployed all your army units." << endl;

    } else if (this->getReinforcement() > 0 && orderName == "advance") {
        cout << "Invalid: You still have " << this->getReinforcement() << " army units to deploy!" << endl;

    } else if (this->getReinforcement() == 0 && orderName == "advance") {
        Order *advanceOrder = new Advance(); // create an advance order
        this->orderList->addOrder(advanceOrder); // add to orders list
        cout << "You have issued an order to: [" << orderName << "] !" << endl;

    } else if (this->getReinforcement() > 0 && (orderName == "airlift" || orderName == "blockade" ||
                                                orderName == "bomb" || orderName == "diplomacy" ||
                                                orderName == "negotiate")) {
        cout << "Invalid: You still have " << this->getReinforcement() << " army units to deploy!" << endl;

    } else if (this->getReinforcement() == 0 && (orderName == "airlift" || orderName == "blockade" ||
                                                 orderName == "bomb" || orderName == "diplomacy" ||
                                                 orderName == "negotiate")) {

        bool hasCard = false; // check if the player has the card in their hand
        Order *order;
        for (auto &card: this->getHand()->hand) {
            if (card->getType() == orderName) {
                if (orderName == "advance") {
                    order = new Advance();
                } else if (orderName == "airlift") {
                    order = new Airlift();
                } else if (orderName == "blockade") {
                    order = new Blockade();
                } else if (orderName == "bomb") {
                    order = new Bomb();
                } else if (orderName == "diplomacy") {
                    order = new Negotiate();
                }
                if (order != nullptr) {
                    this->playCard(card, deck);
                    cout << "You have issued an order to: [" << orderName << "] !" << endl;
                    hasCard = true;
                    break;
                }
            }
        }
        if (!hasCard) {
            cout << "You do not have a [" << orderName << "] card in your hand!" << endl;
        }
    } else {
        cout << "Invalid: There is no such card." << endl;
    }

    cout << "okay next" << endl;
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

vector<int> Player::continentOwnershipComplete() {
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
}

void Player::playCard(Card *card, Deck *deck) {
    this->hand->play(card, deck);
}

OrdersList *Player::issuesOrder(Order *o) {
    orderList->addOrder(o);
    cout << "...Pushed a new order to orderList...\n";
    cout << "New order id: " << o->getOrderID() << "\n\n";
    return orderList;
}
