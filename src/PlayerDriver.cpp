#include "Player.h"

#include <iostream>


void PlayerDriver::testPlayers() {
  vector < Territory * > t;
  Hand * h = new Hand(); // TODO later change it to get card
  vector < Order * > o;

  /// <summary>
  /// Create 6 territories and push them to the territories vector 
  /// </summary>
  Territory * t1 = new Territory("UK");
  Territory * t2 = new Territory("USA");
  Territory * t3 = new Territory("Russia");
  Territory * t4 = new Territory("Israel");
  Territory * t5 = new Territory("Italy");
  Territory * t6 = new Territory("Bulgaria");
  t.push_back(t1);
  t.push_back(t2);
  t.push_back(t3);
  t.push_back(t3);
  t.push_back(t3);
  t.push_back(t3);
  t.push_back(t3);

  /// <summary>
  /// Init a player
  /// </summary>  
  Player * p = new Player(t, h, o);

  /// <summary>
  /// Show that Player contains method toDefend()
  /// </summary>  

  p -> toDefend();
  /// <summary>
  /// Show that Player contains method toAttack()
  /// </summary>  
  p -> toAttack();

  /// <summary>
  /// Show that Player contains method issueOrder()
  /// </summary>  
  p -> issueOrder();

  /// <summary>
  /// Dereference my pointers
  /// </summary>  
  delete h;
  h = NULL;
};