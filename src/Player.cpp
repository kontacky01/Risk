#include "Player.h"
#include <iostream>
#include <string>


// constructor
Player::Player(vector<Territory *> t, Hand * h, vector<Order *> o){
    territories = t;
    hand = h;
    orderList = o;
};

// copy constructor
Player::Player(const Player &){};
Player::Player(){};

Hand* Player::getHand() {
  return hand;
};

/**
  * toDefend
  * Returns a random list of territories that are assigned to the user which he would like to defend
  */
vector<Territory *> Player::toDefend()
{
      vector<Territory *> defended;

  if(territories.size() == 0){
    cout << "There are no territories to defend\n";
    return defended;
  }
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
vector<Territory *> Player::toAttack()
{
    vector<Territory *> attacked;
     if(territories.size() == 0){
    cout << "There are no territories to attack\n";
    return attacked;
  }
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
 
vector<Order *> Player::issueOrder()
{
    Order *o = new Order();
    orderList.push_back(o);
    cout << "pushed a new order to orderlist";
    return orderList;
}