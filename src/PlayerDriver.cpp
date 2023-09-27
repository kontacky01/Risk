#include "Player.h"
#include <iostream>


void PlayerDriver::testPlayers()
{
  vector<Territory *> t;
  Hand *h = new Hand(); // TODO later change it to get card
  vector<Order *> o;

  // Create a player
  Player *p = new Player(t, h, o);

  // Player owns a hand of Warzone cards
  p->getHand();

  // Player contains methods toDefend()
  
  
  p->toDefend();
  // Player contains methods toAttack()
  p->toAttack();

  // Player contains methods issueOrder()
  p->issueOrder();
};
