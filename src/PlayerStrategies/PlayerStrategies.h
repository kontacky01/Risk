#pragma once

#include "../GameEngine/GameEngine.h"
#include "../OrdersList/Orders.h"
#include "../Map/Map.h"

class Player;

class PlayerStrategy {
public:
    virtual ~PlayerStrategy() = default;

    virtual vector<Territory *> toAttack(Player *player) = 0;

    virtual vector<Territory *> toDefend(Player *player) = 0;

    virtual void issueOrder(Player *player, string orderName) = 0;

    virtual string getStrategyType() = 0;
};


class HumanPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player) override;

    vector<Territory *> toDefend(Player *player) override;

    void issueOrder(Player *player, string orderName) override;

    string getStrategyType() override;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player) override;

    vector<Territory *> toDefend(Player *player) override;

    void issueOrder(Player *player, string orderName) override;

    string getStrategyType() override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player) override;

    vector<Territory *> toDefend(Player *player) override;

    void issueOrder(Player *player, string orderName) override;

    string getStrategyType() override;
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player) override;

    vector<Territory *> toDefend(Player *player) override;

    void issueOrder(Player *player, string orderName) override;

    string getStrategyType() override;
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory *> toAttack(Player *player) override;

    vector<Territory *> toDefend(Player *player) override;

    void issueOrder(Player *player, string orderName) override;

    string getStrategyType() override;
};

int testPlayerStrategies();