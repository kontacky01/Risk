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
    OrdersList OL;
    // Copies
    Order *o1Copy = new Order(o1);
    Deploy *d1Copy = new Deploy(d1);
    Deploy *d1Copy2 = d1;
    Advance *a1Copy = new Advance(a1);
    Bomb *b1Copy = new Bomb(b1);
    OrdersList OLCopy;

    cout << endl <<"Printing Orders List  with ostream: " << endl;
    OL.addOrder(o1);
    OL.addOrder(d1);
    OL.addOrder(a1);
    OL.addOrder(b1);
    cout << OL;
    
    cout << endl << "Printing Copies of Order And Deploy in a new OrdersList: " << endl;
    OLCopy.addOrder(o1Copy);
    OLCopy.addOrder(d1Copy);
    OLCopy.addOrder(a1Copy);
    OLCopy.addOrder(b1Copy);
    cout << OL;

    cout <<endl <<"Change Order and Deploy Validity to True: " << endl;
    o1->setValid(true);
    d1->setValid(true);
    cout << OL;

    cout << endl << "Exectuing orders: " << endl;
    o1->execute();
    d1->execute();
    a1->execute();
    b1->execute();
    
}
