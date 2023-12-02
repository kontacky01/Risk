#pragma once

#include "../GameEngine/GameEngine.h"
#include "../CardsDeck/Cards.h"
#include "../OrdersList/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"

class Player;

class PlayerStrategy {
public:
    virtual ~PlayerStrategy() = default;

    virtual vector<Territory *> toAttack(Player *player) = 0;

    virtual vector<Territory *> toDefend(Player *player) = 0;

    virtual void issueOrder(Player *player) = 0;

    virtual string getStrategy() = 0;
};


class HumanPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player);

    vector<Territory *> toDefend(Player *player);

    void issueOrder(Player *player);

    string getStrategy();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player);

    vector<Territory *> toDefend(Player *player);

    void issueOrder(Player *player);

    string getStrategy();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player);

    vector<Territory *> toDefend(Player *player);

    void issueOrder(Player *player);

    string getStrategy();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player);

    vector<Territory *> toDefend(Player *player);

    void issueOrder(Player *player);

    string getStrategy();
};

// class CheaterPlayerStrategy : public PlayerStrategy {
// public:
//     vector<Territory *> toAttack(Player *player);

//     vector<Territory *> toDefend(Player *player);

//     void issueOrder(Player *player);

//     string getStrategy();
// };
/************************************************************ PlayerStrategiesDriver **************************************************************/
void testPlayerStrategies();