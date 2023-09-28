//Orders Driver for MainDriver.cpp
#include<iostream>
using namespace std;

#include "Orders.h"

void testOrderList() {
    cout << "Hello from testOrderlist()" << endl <<endl;
    cout << "Creating orders: " << endl;
    cout << "Order (parent class), Deploy and Advance" <<endl;
    Order *o1 = new Order();
    Deploy *d1 = new Deploy();
    Advance *a1 = new Advance();
    OrdersList OL;

    cout << endl <<"Printing Orders List  with ostream: " << endl;
    OL.addOrder(o1);
    OL.addOrder(d1);
    cout << OL;

    cout <<endl <<"Change Order and Deploy Validity to True: " << endl;
    o1->setValid(true);
    d1->setValid(true);
    cout << "Add Advance to Orderslist " << endl;
    OL.addOrder(a1);
    cout << OL;

    cout << endl << "Exectuing orders: " << endl;
    o1->execute();
    d1->execute();
    a1->execute();

}
