#ifndef ORDERS_H
#define ORDERS_H

#include <map>
#include <iostream>
using namespace std;


class Order
{
public:
    Order();    //default contrustor

    /* Invalid orders can be created and put in the list, 
     * but their execution will not result in any action.
     * Returns true if valid */
    bool validate();    
    bool execute();     //returns true if action implemented
    int incrementCount(); //countOrderID + 1
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


// end marker for the above's #ifndef
#endif

