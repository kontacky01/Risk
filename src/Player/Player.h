//#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../OrdersList/Orders.h"
#include "../CardsDeck/Cards.h"
#include "../LoggingObserver/LoggingObserver.h"

using namespace std;

/************************************************************ Player **************************************************************/
class Hand;//Forward declaration
class Order;//Forward declaration
class OrdersList;//Forward declaration

class Player {
 private:
  int id;
  int reinforcements;
  vector<Territory*> territories;
  Hand* hand;
  OrdersList* orderList;

  /**
   * Helper method to print the list of territories to attack/defended
   */
  friend ostream& operator<<(ostream& out, Player* o);  // overide Stream insertion operator
  
  void printTerritories(vector<Territory*> territories);

 public:
  /**
   * Constructor with with an argument list
   */
  Player(vector<Territory*>, Hand*, OrdersList*, int id);

  /**
   * Default Constructor
   */
  Player();

  /**
   * Copy Constructor
   */
  Player(const Player&);

  /**
   * Destructor
   */
  ~Player();

  int getID();

  int getReinforcement();

  void setReinforcement(int r);

  void addReinforcement(int r);

  void subtractReinforcemnts(int r);

  vector<Territory*> getTerritories();

  void addTerritory(Territory* t);

  void removeTerritory(Territory* t);

  void eraseTerritory(Territory* t);

  OrdersList* getOrdersList();

  bool ownsTerritory(Territory *t);

  Hand* getHand();

  /**
   * Returns a random list of territories that are assigned to the user which
   * they would like to defend
   */
  vector<Territory*> toDefend();

  /**
   * Returns a random list of territories that the user would like to attack
   */
  vector<Territory*> toAttack();

  /**
   * Take in an order and add it into the OrderList
   */
  OrdersList* issueOrder(Order* o);

  //void executeNextOrderAndRemove();
};

/************************************************************ PlayerDriver **************************************************************/
void testPlayers();
#endif