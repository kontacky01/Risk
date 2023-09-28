//Orders Driver for MainDriver.cpp
#include<iostream>
using namespace std;

#include "Orders.h"

void testOrderList() {
    cout << "Hello from testOrderlist()\n";
    Order *o1 = new Order();
    Deploy *deploy = new Deploy();
    OrdersList OL;
    
    OL.addOrder(o1);
    OL.addOrder(deploy);
    OL.addOrder(o1);
    cout << OL;
}
