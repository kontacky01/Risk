#pragma once

#include <ctime>

#include <iostream>
#include <string>
#include <vector>

#include "../CardsDeck/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../OrdersList/Orders.h"
#include "LoggingObserver.h"

using namespace std;

/************************************************************ Player **************************************************************/

class Player : public Subject, ILoggable {
private:
    int id;
    int reinforcements;
    vector<Territory *> territories;
    Hand *hand;
    OrdersList *orderList;
    State *state;
    GameEngine *gameEngine;

    /**
     * Helper method to print the list of territories to attack/defended
     */
    friend ostream &operator<<(ostream &out, Player *o);  // override Stream insertion operator

    void printTerritories(vector<Territory *> territories);

    string gamePhase;

public:
    /**
     * Constructor with with an argument list
     */
    Player(vector<Territory *>, Hand *, OrdersList *, int id, State *);

    /**
     * Default Constructor
     */
    Player();

    /**
     * Copy Constructor
     */
    Player(const Player &);

    /**
     * Destructor
     */
    ~Player();

    int getID() const;

    int getReinforcement() const;

    void setReinforcement(int r);

    void addReinforcement(int r);

    void subtractReinforcements(int r);

    vector<Territory *> getTerritories();

    void addTerritory(Territory *t);

    void removeTerritory(Territory *t);

    void eraseTerritory(Territory *t);

    vector<int> continentOwnershipComplete();

    OrdersList *getOrdersList();

    State *getState();

    static void setGamePhase(string gamePhase);

    string getGamePhase();

    bool ownsTerritory(Territory *t);

    Hand *getHand();

    string stringToLog() override;

    /**
     * Returns a random list of territories that are assigned to the user which
     * they would like to defend
     */
    vector<Territory *> toDefend();

    /**
     * Returns a random list of territories that the user would like to attack
     */
    vector<Territory *> toAttack();

    /**
     * Take in an order and add it into the OrderList
     */
    OrdersList *issueOrder(Order *o);

    //void executeNextOrderAndRemove();
};

/************************************************************ PlayerDriver **************************************************************/
void testPlayers();