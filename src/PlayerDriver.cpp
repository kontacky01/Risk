#include "Player.h";

class PlayerDriver
{
  public:
  static void testPlayers()
  {
    vector<Territory *> t = new Territory();
    Hand h = new Hand(); // later change it to get card
    vector<Order *> o = new Territory();

    // Create a player
    Player p = new Player(t, h, o);

    // Player owns a hand of Warzone cards
    p.getHand();

    // Player contains methods toDefend()
    p.toDefend();
    // Player contains methods toAttack()
    p.toAttack();

    // Player contains methods issueOrder()
    p.issueOrder();
  };
};