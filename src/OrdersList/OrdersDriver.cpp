#include "Orders.h"
#include "../CardsDeck/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

void testOrdersLists() {
    cout << "\n" << "************************************" << "\n"
        << "Time to test Orders and OrdersList!! \n"
        << "************************************" << "\n" << "\n";

    cout << "\n\n---------> Test 1: Create Orders and OrdersList <---------" << "\n\n\n";

    cout << "...Creating orders of every type... " << '\n';
    Order* o1 = new Order();
    Deploy* d1 = new Deploy();
    Advance* a1 = new Advance();
    Bomb* b1 = new Bomb();
    Blockade* blk1 = new Blockade();
    Airlift* air1 = new Airlift();
    Negotiate* n1 = new Negotiate();
    cout << "Orders of type: Order, Deploy, Advance, Bomb, Blockade, Airlift and Negotiate have been created. " << "\n\n";

    cout << "...Creating an OrdersList... " << '\n';
    OrdersList *OL = new OrdersList();
    cout << "Ordrslist has been created " << "\n\n";

    cout << "...Adding Orders to OrdersList...." << '\n';
    OL->addOrder(o1);
    OL->addOrder(d1);
    OL->addOrder(a1);
    OL->addOrder(b1);
    OL->addOrder(blk1);
    OL->addOrder(air1);
    OL->addOrder(n1);
    cout << "Orders have been added to OrdersList " << "\n\n";

    cout << "...Printing Orders List with ostream:...." << "\n\n";
    cout << OL;



    cout << "\n\n---------> Test 2: Create Copies of Each Order <---------" << "\n\n\n";

    cout << "...Creating copies of each Order... " << '\n';
    Order* o1Copy = new Order(o1);
    Deploy* d1Copy = new Deploy(d1);
    Deploy* d1Copy2 = d1;
    Advance* a1Copy = new Advance(a1);
    Bomb* b1Copy = new Bomb(b1);
    Blockade* blk1Copy = new Blockade(blk1);
    Airlift* air1Copy = new Airlift(air1);
    Negotiate* n1Copy = new Negotiate(n1);
    cout << "Copies of each Order have been created. " << "\n\n";

    OrdersList *OLCopy = new OrdersList();

    cout << "...Adding copies of Orders in a new OrdersList:..." << '\n';
    OLCopy->addOrder(o1Copy);
    OLCopy->addOrder(d1Copy);
    OLCopy->addOrder(a1Copy);
    OLCopy->addOrder(b1Copy);
    OLCopy->addOrder(blk1Copy);
    OLCopy->addOrder(air1Copy);
    OLCopy->addOrder(n1Copy);
    cout << "Copies of Orders added." << "\n\n";

    cout << "...Printing Copy OrdersList..." << '\n';
    cout << OLCopy;



    cout << "\n\n---------> Test 3: Validate <---------" << "\n\n\n";

    cout << "...Setting order (parent class) to valid ..." << '\n';
    o1->setValid(true);
    cout << "Order is now valid" << "\n\n";

    cout << "...Seeting deploy to valid ..." << '\n';
    d1->setValid(true);
    cout << "Deploy is now valid" << "\n\n";

    cout << "...Setting blockade to valid ..." << '\n';
    blk1->setValid(true);
    cout << "blockade is now valid" << "\n\n";

    cout << "...Printing OrdersList with new valid Orders ..." << "\n\n";
    cout << OL;


    cout << "\n\n---------> Test 4: Execute <---------" << "\n\n\n";

    cout << "...Exectuing orders:... " << '\n';
    cout << "Note: - only valid Orders can be executed" << "\n";
    cout << "      - All orders are in proper state" << "\n\n";
    
    State* sTest = new State("executeorders");

    cout << "...Executing order(parent class)..." << '\n';
    o1->execute(sTest);
    cout << "\n";
    cout << "...Executing Deploy ..." << '\n';
    d1->execute(sTest);
    cout << "\n";
    cout << "...Execting Advance ..." << '\n';
    a1->execute(sTest);
    cout << "\n";
    cout << "...Executing Bomb ..." << '\n';
    b1->execute(sTest);
    cout << "\n";
    cout << "...Executing Blockaid ..." << '\n';
    blk1->execute(sTest);
    cout << "\n";
    cout << "...Executing Airlift ..." << '\n';
    air1->execute(sTest);
    cout << "\n";
    cout << "..Executing Negotiate ..." << '\n';
    n1->execute(sTest);
    cout << "\n\n";


    cout << "\n\n---------> Test 5: Remove Orders <---------" << "\n\n\n";

    cout << "Removing orders 5, 6 and 7 from Orderslist " << '\n';
    if (OL->remove(5)) cout << "Removed order #5 " << '\n'; else cout << "Did NOT remove order #5" << '\n';
    if (OL->remove(6)) cout << "Removed order #6 " << '\n'; else cout << "Did NOT remove order #6" << '\n';
    if (OL->remove(7)) cout << "Removed order #7 " << '\n'; else cout << "Did NOT remove order #7" << '\n';
    if (OL->remove(9)) cout << "Removed order #9 " << '\n'; else cout << "Did NOT remove order #9" << '\n';
    cout << OL;



    cout << "\n\n---------> Test 6: Move Orders <---------" << "\n\n\n";

    cout << '\n' << "Testing Move() that are out of bounds or don't exist" << '\n';
    if (OL->move(0, 4)) cout << "Moving order #4 to position 0" << '\n'; else cout << "Can NOT move order #4 to position 0" << '\n';
    if (OL->move(-2, 4)) cout << "Moving order #4 to position -2" << '\n'; else cout << "Can NOT move order #4 to position -2" << '\n';
    if (OL->move(10, 4)) cout << "Moving order #4 to position 10" << '\n'; else cout << "Can NOT move order #4 to position 10" << '\n';

    cout << '\n' << "Moving orders" << '\n';
    if (OL->move(1, 4)) cout << "Moving order #4 to position 1" << '\n'; else cout << "Can NOT move order #4 to position 1" << '\n';
    cout << OL << '\n';
    if (OL->move(4, 1)) cout << "Moving order #1 to position 4" << '\n'; else cout << "Can NOT move order #4 to position 3" << '\n';
    cout << OL << '\n';
    if (OL->move(2, 3)) cout << "Moving order #2 to position 3" << '\n'; else cout << "Can NOT move order #4 to position 3" << '\n';
    cout << OL;
   
    cout << "\n\n---------> Test 7: Execute Player Orders <---------" << "\n\n\n";
   
    vector<Territory*> tOL;
    Hand* hOL = new Hand();
    OrdersList *pOL = new OrdersList();
    
    //Initializing Territory adjeceny list
    Territory* t1OL = new Territory("UK", 1, 2, 0);
    Territory* t2OL = new Territory("USA", 2, 3, 0);
    tOL.push_back(t1OL);
    tOL.push_back(t2OL);

    //Create player orders
    Order* pOr1 = new Order();
    Deploy* pD1 = new Deploy();
    Advance* pA1 = new Advance();
    Bomb* pB1 = new Bomb();

    //Add player order to orders list
    pOL->addOrder(pOr1);
    pOL->addOrder(pD1);
    pOL->addOrder(pA1);
    pOL->addOrder(pB1);

    cout << "...Creating state executeorders...\n";
    State* pStateOL = new State("executeorders");
    cout << "Created execute orders.\n\n";

    cout << "...Creating player with territory adjeceny list, Hand, and order list..\n";
    Player* p = new Player(tOL, hOL, pOL, 1, pStateOL);
    cout << "Created player.\n\n";

    cout << "...Printing Players orders..\n";
    cout << "-------------------------------\n";
    cout << p->getOrdersList();

    cout << "...Setting players 2nd and 4th orders to valid..\n";
    p->getOrdersList()->getOL()->at(1)->setValid(true);
    p->getOrdersList()->getOL()->at(3)->setValid(true);
    cout << "Players 2nd and 4th orders are valid.\n\n";


    cout << "If Player is inside execute  rders state and will be able to execute!\n\n";
    cout << "...Executing players orders...\n";
    cout << "-------------------------------\n";
    p->getOrdersList()->executeAll(p->getState());


    cout << "\n\n---------> Test 8: Deleting Pointers <---------" << "\n\n\n";

    cout << "...Deleting pointers..\n";
    OL->deleteOrdersList();
    delete OL;
    OL = NULL;
    OLCopy->deleteOrdersList();
    delete OLCopy;
    OLCopy = NULL;
    delete t1OL;
    t1OL = NULL;
    delete t2OL;
    t2OL = NULL;
    // delete hOL --> hand deletion is managed by the player as it belongs to it;
    hOL = NULL;
    delete p;
    // delete pStateOL --> state will be also deleted by the player;
    pStateOL = NULL;
    delete sTest;
    sTest = NULL;
    cout << "Pointers deleted.\n\n";
};