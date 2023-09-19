#ifndef ORDERS_H
#define ORDERS_H

#include <map>
#include <iostream>
using namespace std;

class Order
{
public:
    Order();                //default contrustor
    /* Invalid orders can be created and put in the list,
     * but their execution will not result in any action.
     * Returns true if valid */
    bool validate();
    bool execute();         //returns true if action implemented
    int incrementCount();   //countOrderID + 1
    void toString();
private:
    static int countOrderID;
    int orderID;
};

class Deploy : public Order
{
public:
    Deploy();
};

class OrdersList
{
public:
    OrdersList();                       //default constructor
    bool move(int index, int orderID);  //Modify sequence of orders
    bool remove(int orderID);           //removes order from ordersList
private:
    map<int, Order*> first;             //Create a map(key,value) list of orders
};



// end marker for the above's #ifndef
#endif