#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include "../CardsDeck/Cards.h"
#include "../OrdersList/Orders.h"
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"

using namespace std;

/************************************************************ Player ************************************************************/

class Player
{
private:
  vector<Territory*> territories;
  Hand* hand;
  vector<Order*> orderList;
  State* state;

  /// <summary>
  /// Helper method to list attack/defended territories
  /// </summary>
  void printTerritories(vector<Territory*> territories);

public:
  /// <summary>
  /// Constructor with with an argument list
  /// </summary>
  Player(vector<Territory*>, Hand*, vector<Order*>);

  /// Constructor with with an argument list
  Player(vector<Territory*>, Hand*, vector<Order*>, State* s);

  /// <summary>
  /// Default Constructor
  /// </summary>
  Player();

  /// <summary>
  /// Copy Constructor
  /// </summary>
  Player(const Player&);

  //get orderList
  vector<Order*> getOrderList();

  //get state
  State* getState();

  /// <summary>
  /// toDefend
  /// Returns a random list of territories that are assigned to the user which they would like to defend
  /// </summary>
  vector<Territory*> toDefend();

  /// <summary>
  /// toAttack
  /// Returns a random list of territories that the user would like to attack
  /// </summary>
  vector<Territory*> toAttack();

  /// <summary>
  /// issueOrder
  /// Take in an order and add it into the OrderList
  /// </summary>
  vector<Order*> issueOrder(Order* o);
};

/************************************************************ PlayerDriver ************************************************************/
void testPlayers();