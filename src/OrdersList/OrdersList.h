#ifndef ORDERSLIST_H
#define ORDERSLIST_H

#include <map>
#include <iostream>
using namespace std;

#include "Order.h"

void testOrderList();

// int orderID; 

class OrdersList
{
public:
    OrdersList();       //default constructor

    /* Modifies the sequence of orders in the list
     * Returns true if succesful
     */
    bool move(int index, int orderID);

    bool remove(int orderID);       //removes order from ordersList

private:
    //Create a map(key,value) list of orders
    map<int, Order*> first;
};

// end marker for the above's #ifndef
#endif
