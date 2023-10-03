#include<iostream>

#include "Orders.h"

using namespace std;

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

    cout << endl << "Removing orders 5, 6and 7 from Orderslist " << endl;
    if (OL.remove(5)) cout << "Removed order #5 " << endl; else cout << "Did NOT remove order #5" << endl;
    if (OL.remove(6)) cout << "Removed order #6 " << endl; else cout << "Did NOT remove order #6" << endl;
    if (OL.remove(7)) cout << "Removed order #7 " << endl; else cout << "Did NOT remove order #7" << endl;
    if (OL.remove(9)) cout << "Removed order #9 " << endl; else cout << "Did NOT remove order #9" << endl;
    cout << OL;

    cout <<endl << "Testing Move() that are out of bounds or don't exist" <<endl;
    if (OL.move(0, 4)) cout << "Moving order #4 to position 0" << endl; else cout << "Can NOT move order #4 to position 0" << endl;
    if (OL.move(-2, 4)) cout << "Moving order #4 to position -2" << endl; else cout << "Can NOT move order #4 to position -2" << endl;
    if (OL.move(10, 4)) cout << "Moving order #4 to position 10" << endl; else cout << "Can NOT move order #4 to position 10" << endl;

    cout << endl << "Moving orders" << endl;
    if (OL.move(1, 4)) cout << "Moving order #4 to position 1" << endl; else cout << "Can NOT move order #4 to position 1" << endl;
    cout << OL << endl;
    if (OL.move(4, 1)) cout << "Moving order #1 to position 4" << endl; else cout << "Can NOT move order #4 to position 3" << endl;
    cout << OL << endl;
    if (OL.move(2, 3)) cout << "Moving order #2 to position 3" << endl; else cout << "Can NOT move order #4 to position 3" << endl;
    cout << OL;

    OL.deleteOrdersList();
    OLCopy.deleteOrdersList();
}
