#include <algorithm>
#include "GameEngine.h"
#include "Player.h"


/************************************************************ Player **************************************************************/
/**
 * Constructor with with an argument list
 */
Player::Player(vector<Territory *> t, Hand *h, OrdersList *o, int id, State *s) {
    territories = t;
    hand = h;
    orderList = o;
    this->id = id;
    state = s;

    // if seed is set to 1, the generator is reinitialized to its initial value
    // and produces the same values as before any call to rand or srand
    srand((unsigned) time(NULL));
}

/**
 *  Helper method to list attack/defended territories
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
    hand = new Hand(*p.hand);

    // create a new orderlist
    orderList = new OrdersList(*p.orderList);

    // create a new state
    if (p.state == NULL) {
        state = NULL;
    } else {
        //state = new State(*p.state);
    }

    // it's not a pointer, so we just increase the ID 1
    id = p.id + 1;
}

/**
 * Destructor
 */
Player::~Player() {
    cout << "...Player destructor was called...\n";
    for (int i = 0; i < territories.size(); i++) {
        territories.at(i) = NULL;
    }

    delete hand;
    hand = NULL;

    delete orderList;
    orderList = NULL;

    delete state;
    state = NULL;
}

/**
 * Default Constructor
 */
Player::Player() {}

int Player::getID() const { return this->id; }

void Player::setGamePhase(string gamePhase) {
    gamePhase = gamePhase;
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
    t->setOwnerId(0); // resets value that map points too
    t->setArmyCount(0); // resets value that map points too
    auto it = find(territories.begin(), territories.end(), t);
    territories.erase(it);
}

OrdersList *Player::getOrdersList() { return this->orderList; }

State *Player::getState() { return this->state; }

bool Player::ownsTerritory(Territory *t) { return t->getOwnerId() == this->id; }

Hand *Player::getHand() { return this->hand; }

/**
 * Returns a random list of territories that are assigned to the user which they
 * would like to defend
 */
vector<Territory *> Player::toDefend() {
    vector<Territory *> defended;
    // if no territories were init
    if (territories.size() == 0) {
        cout << "...There are no territories to defend...\n";
        return defended;
    }
    int index = rand() % territories.size() + 1;
    for (int i = 0; i < index; i++) {
        defended.push_back(territories.at(i));
    }
    cout << "\nTerritories to defend:\n -------------------\n";
    printTerritories(defended);
    return defended;
}

/**
 * Returns a random list of territories that the user would like to attack
 */
vector<Territory *> Player::toAttack() {
    vector<Territory *> attacked;
    if (territories.size() == 0) {
        cout << "...There are no territories to attack...\n";
        return attacked;
    }
    int index = rand() % territories.size() + 1;
    for (int i = 0; i < index; i++) {
        attacked.push_back(territories.at(i));
    }
    cout << "\nTerritories to attack:\n-------------------\n";
    printTerritories(attacked);

    return attacked;
}

/**
 * Take in an order and add it into the OrderList
 */
OrdersList *Player::issueOrder(Order *o) {
    orderList->addOrder(o);
    cout << "...Pushed a new order to orderList...\n";
    cout << "New order id: " << o->getOrderID() << "\n\n";
    return orderList;
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
    out << "\nCurrent player's state: "
        //   << (p->state == NULL ? "no state yet" : p->state->getStateName())
        << "\n\n";
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
