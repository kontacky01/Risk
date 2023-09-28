#include "Player.h"

void PlayerDriver::testPlayers()
{
  vector<Territory *> t;
  Hand *h = new Hand();
  vector<Order *> o;

  // Create 6 territories and push them to the territories vector
  Territory *t1 = new Territory("UK");
  Territory *t2 = new Territory("USA");
  Territory *t3 = new Territory("Russia");
  Territory *t4 = new Territory("Israel");
  Territory *t5 = new Territory("Italy");
  Territory *t6 = new Territory("Bulgaria");
  t.push_back(t1);
  t.push_back(t2);
  t.push_back(t3);
  t.push_back(t4);
  t.push_back(t5);
  t.push_back(t6);

  // Init a player
  Player *p = new Player(t, h, o);
  // Show that player contains a copy constructor
  Player *pCopy = new Player(*p);

  // Show that Player contains method toDefend()
  p->toDefend();

  // Show that Player contains method toAttack()
  p->toAttack();

  // Show that Player contains method issueOrder()
  Order *newOrder = new Order("1");
  p->issueOrder(newOrder);

  // Show that Player contains method toDefend()
  pCopy->toDefend();

  // Show that Player contains method toAttack()
  pCopy->toAttack();

  // Show that Player contains method issueOrder()
  Order *newOrderCopy = new Order("2");
  pCopy->issueOrder(newOrderCopy);

  // Delete hand pointer
  delete h;
  h = NULL;

  // Delete territories pointer
  for (int i = 0; i < t.size(); i++)
  {
    delete t.at(i);
    t.at(i) = NULL;
  }
  // Delete orderlist pointer
  for (int i = 0; i < o.size(); i++)
  {
    delete o.at(i);
    o.at(i) = NULL;
  }

  // Delete player pointer
  delete p;
  p = NULL;

  // Delete playerCopy pointer
  delete pCopy;
  pCopy = NULL;
};