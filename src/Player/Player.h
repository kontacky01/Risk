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
  int id;
  vector<Territory*> territories;
  Hand* hand;
  OrdersList orderList;
  State* state;

  /// <summary>
  /// Helper method to list attack/defended territories
  /// </summary>
  void printTerritories(vector<Territory*> territories);

public:
  /// <summary>
  /// Constructor with with an argument list
  /// </summary>
  Player(vector<Territory*>, Hand*, OrdersList, int);

  /// Constructor with with an argument list
  Player(vector<Territory*>, Hand*, OrdersList, State* s);

  /// <summary>
  /// Default Constructor
  /// </summary>
  Player();

  /// <summary>
  /// Copy Constructor
  /// </summary>
  Player(const Player&);

  //get orderList
  OrdersList getOrdersList();

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
  OrdersList issueOrder(Order* o);
};

/************************************************************ PlayerDriver ************************************************************/
void testPlayers();