//Orders Driver for MainDriver.cpp
#include<iostream>
using namespace std;

#include "Orders.h"

void testOrderList() {
    cout << "Hello from testOrderlist()" << endl;
    cout << "Creating orders: " << endl;
    Order *o1 = new Order();
    Deploy *d1 = new Deploy();
    OrdersList OL;

    cout << "Printing Orders List  with ostream: " << endl;
    OL.addOrder(o1);
    OL.addOrder(d1);
    cout << OL;

    o1->setValid(true);
    d1->setValid(true);
    cout << OL;

}
