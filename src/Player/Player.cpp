#include "Player.h"

/************************************************************ TODO: TEMP ************************************************************/
Territory::Territory(string n)
{
  name = n;
}

/************************************************************ Player ************************************************************/
/// <summary>
/// Constructor with with an argument list
/// </summary>
Player::Player(vector<Territory*> t, Hand* h, vector<Order*> o)
{
  territories = t;
  hand = h;
  orderList = o;

  // If seed is set to 1, the generator is reinitialized to its initial value and produces the same values as before any call to rand or srand
  srand((unsigned)time(NULL));
}

/// <summary>
/// Helper method to list attack/defended territories
/// </summary>
void Player::printTerritories(vector<Territory*> territories)
{
  for (int i = 0; i < territories.size(); i++)
  {
    cout << i << ")" << territories.at(i)->name << endl << endl;
  }
}

/// <summary>
/// Copy Constructor
/// </summary>
// TODO: does need to be a shallow or deep copy
Player::Player(const Player& p)
{
  cout << "...Copy constructor was called..." << endl;
  territories = p.territories;
  hand = p.hand;
  orderList = p.orderList;
};

/// <summary>
/// Default Constructor
/// </summary>
// Todo: Should have the default init for hand, terr and orderlist?
Player::Player() {};

/// <summary>
/// toDefend
/// Returns a random list of territories that are assigned to the user which they would like to defend
/// </summary>
vector<Territory*> Player::toDefend()
{
  vector<Territory*> defended;
  // if no territories were init
  if (territories.size() == 0)
  {
    cout << "...There are no territories to defend..." << "\n";
    return defended;
  }
  int index = rand() % territories.size() + 1;
  for (int i = 0; i < index; i++)
  {
    defended.push_back(territories.at(i));
  }
  cout << "\n" << "Territories to defend: " << "\n" << "-------------------" << "\n";
  printTerritories(defended);
  return defended;
}

/// <summary>
/// toAttack
/// Returns a random list of territories that the user would like to attack
/// </summary>
vector<Territory*> Player::toAttack()
{
  vector<Territory*> attacked;
  if (territories.size() == 0)
  {
    cout << "...There are no territories to attack..." << "\n";
    return attacked;
  }
  int index = rand() % territories.size() + 1;
  for (int i = 0; i < index; i++)
  {
    attacked.push_back(territories.at(i));
  }
  cout << endl << "Territories to attack: " << "\n" << "-------------------" << "\n";
  printTerritories(attacked);

  return attacked;
}

/// <summary>
/// issueOrder
/// Take in an order and add it into the OrderList
/// </summary>
vector<Order*> Player::issueOrder(Order* o)
{
  orderList.push_back(o);
  cout << "...Pushed a new order to orderList..." << "\n";
  cout << "New order id: " << o->getOrderID() << "\n" << "\n";
  return orderList;
}