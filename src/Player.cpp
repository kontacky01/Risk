#include 'Player.h';
#include <iostream>
#include <string>

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
     * toDefend
     * Returns a random list of territories that are assigned to the user which he would like to defend
     */
    vector<Territory *> toDefend()
    {
        vector<Territory *> defended;
        int index = rand() % territories.size() + 1;
        for (int i = 0; i < index; i++)
        {
            defended.push_back(territories.at(i));
        }
        // todo, territories class should have a toString that returns a comma separated list of defended territories. 
        cout << "Territories to defend:" << defended.size();
        return defended;
    }

    /**
     * toAttack
     * Returns a random list of territories that are assigned to the user which he would like to defend
     */
    vector<Territory *> toAttack()
    {
        vector<Territory *> attacked;
        int index = rand() % territories.size() + 1;
        for (int i = 0; i < index; i++)
        {
            attacked.push_back(territories.at(i));
        }
        // todo, territories class should have a toString that returns a comma separated list of attacked territories. 
        cout << "Territories to attack:" << attacked.size();
        return attacked;
    }
    /**
     * issueOrder
     * Take in an order and add it into the OrderList
     */
    vector<Order *> issueOrder()
    {
        Order *o = new Order();
        orderlist.push_back(o);
    }
};
