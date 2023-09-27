#include "Player.h"

/************************************************************ TODO: TEMP ************************************************************/
Territory::Territory(string n) {
  name = n;
}

Order::Order(string o) {
  orderID = o;
}

Hand::Hand(){
  cards.push_back("card1");
  cards.push_back("card2");
}

void Hand::getHand() {
    cout << "The hand has been init with the following cards: " << cards.at(0) << " and " << cards.at(1) << "\n";
}
/************************************************************ Player ************************************************************/
/// <summary>
/// Constructor with with an argument list
/// </summary>
Player::Player(vector < Territory * > t, Hand * h, vector < Order * > o) {
  territories = t;
  hand = h;
  orderList = o;
  h->getHand();
  // init the seed for random generation
  srand((unsigned)time(NULL));
};

/// <summary>
/// Copy Constructor
/// </summary>
Player::Player(const Player & ) {};

/// <summary>
/// Default Constructor
/// </summary>
Player::Player() {};

/// <summary>
/// toDefend
/// Returns a random list of territories that are assigned to the user which they would like to defend
/// </summary>
vector < Territory * > Player::toDefend() {
  vector < Territory * > defended;
  // if no territories were init
  if (territories.size() == 0) {
    cout << "There are no territories to defend\n";
    return defended;
  }
  int index = rand() % territories.size() + 1;
  for (int i = 0; i < index; i++) {
    defended.push_back(territories.at(i));
  }
  // TODO: override the operator to handle this, perhaps in the territory class
  cout << "Territories to defend:\n";
  for (int i = 0; i < defended.size(); i++) {
    cout << defended.at(i) -> name << "\n";
  }
  cout << "------------------------------\n";
  return defended;
}

/// <summary>
/// toAttack
/// Returns a random list of territories that the user would like to attack
/// </summary>
vector < Territory * > Player::toAttack() {
  vector < Territory * > attacked;
  if (territories.size() == 0) {
    cout << "There are no territories to attack\n";
    return attacked;
  }
  int index = rand() % territories.size() + 1;
  for (int i = 0; i < index; i++) {
    attacked.push_back(territories.at(i));
  }
  // TODO: override the operator to handle this, perhaps in the territory class
  cout << "Territories to attack:\n";
  for (int i = 0; i < attacked.size(); i++) {
    cout << attacked.at(i) -> name << "\n";
  }
  cout << "------------------------------\n";
  return attacked;
}

/// <summary>
/// issueOrder
/// Take in an order and add it into the OrderList
/// </summary>
vector < Order * > Player::issueOrder(Order* o) {
  orderList.push_back(o);
  cout << "pushed a new order to orderList with orderID:" << o -> orderID;
  return orderList;
}