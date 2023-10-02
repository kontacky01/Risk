#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

/************************************************************ TEMP ************************************************************/
class Territory
{
public:
    string name;
    // constructor
    Territory(string);
};

class temp_Order
{
public:
    string orderID;
    // constrcutor
    temp_Order(string);
};

class temp_Hand
{
};

/************************************************************ Player ************************************************************/

class Player
{
private:
    vector<Territory *> territories;
    temp_Hand *hand;
    vector<temp_Order *> orderList;

    /// <summary>
    /// Helper method to list attack/defended territories
    /// </summary>
    void printTerritories(vector<Territory *> territories);

public:
    /// <summary>
    /// Constructor with with an argument list
    /// </summary>
    Player(vector<Territory *>, temp_Hand *, vector<temp_Order *>);

    /// <summary>
    /// Default Constructor
    /// </summary>
    Player();

    /// <summary>
    /// Copy Constructor
    /// </summary>
    Player(const Player &);

    /// <summary>
    /// toDefend
    /// Returns a random list of territories that are assigned to the user which they would like to defend
    /// </summary>
    vector<Territory *> toDefend();

    /// <summary>
    /// toAttack
    /// Returns a random list of territories that the user would like to attack
    /// </summary>
    vector<Territory *> toAttack();

    /// <summary>
    /// issueOrder
    /// Take in an order and add it into the OrderList
    /// </summary>
    vector<temp_Order *> issueOrder(temp_Order *o);
};

/************************************************************ PlayerDriver ************************************************************/
namespace PlayerDriver
{
    void testPlayers();
}