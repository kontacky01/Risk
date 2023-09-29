//Orders Driver for MainDriver.cpp
#include<iostream>
using namespace std;

#include "Orders.h"

void testOrderList() {
    cout << "Hello from testOrderlist()" << endl <<endl;
    cout << "Creating orders: " << endl;
    Order *o1 = new Order();
    Deploy *d1 = new Deploy();
    Advance *a1 = new Advance();
    Bomb *b1 = new Bomb();
    Blockade *blk1 = new Blockade();
    Airlift *air1 = new Airlift();
    Negotiate *n1 = new Negotiate();
    OrdersList OL;
    // Copies
    Order *o1Copy = new Order(o1);
    Deploy *d1Copy = new Deploy(d1);
    Deploy *d1Copy2 = d1;
    Advance *a1Copy = new Advance(a1);
    Bomb *b1Copy = new Bomb(b1);
    Blockade *blk1Copy = new Blockade(blk1);
    Airlift *air1Copy = new Airlift(air1);
    Negotiate *n1Copy = new Negotiate(n1);
    OrdersList OLCopy;

    cout << endl <<"Printing Orders List  with ostream: " << endl;
    OL.addOrder(o1);
    OL.addOrder(d1);
    OL.addOrder(a1);
    OL.addOrder(b1);
    OL.addOrder(blk1);
    OL.addOrder(air1);
    OL.addOrder(n1);
    cout << OL;
    
    cout << endl << "Printing Copies of Order And Deploy in a new OrdersList: " << endl;
    OLCopy.addOrder(o1Copy);
    OLCopy.addOrder(d1Copy);
    OLCopy.addOrder(a1Copy);
    OLCopy.addOrder(b1Copy);
    OLCopy.addOrder(blk1Copy);
    OLCopy.addOrder(air1Copy);
    OLCopy.addOrder(n1Copy);
    cout << OL;

    cout <<endl <<"Change Order, Deploy and Blockade Validity to True: " << endl;
    o1->setValid(true);
    d1->setValid(true);
    blk1->setValid (true);
    cout << OL;

    cout << endl << "Exectuing orders: " << endl;
    o1->execute();
    d1->execute();
    a1->execute();
    b1->execute();
    blk1->execute();
    air1->execute();
    n1->execute();
}
