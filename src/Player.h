#pragma once
#include <vector>
using namespace std;

// temp
class Territory
{
};
class Hand
{
}; // contains cards inside
class Order
{
};

class Player
{
    // constructor
    Player(vector<Territory *>, Hand *, vector<Order *>);

    // copy constructor
    Player(const Player &);

    // private data members
private:
    vector<Territory *> territories;
    Hand *hand;
    vector<Order *> orderlist;

    /**
     * getHand
     * Q: ask if i need this method as was not part of the specs
     */
    Hand *getHand()
    {
        return hand;
    }

    /**
     * toDefend
     * Returns a random list of territories that are assigned to the user which he would like to defend
     */
    vector<Territory *> toDefend();

    /**
     * toAttack
     * Returns a random list of territories that are assigned to the user which he would like to defend
     */
    vector<Territory *> toAttack();
    /**
     * issueOrder
     * Take in an order and add it into the OrderList
     */
    vector<Order *> issueOrder();
};

class PlayerDriver
{
public:
  static void testPlayers();
};