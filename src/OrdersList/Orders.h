#ifndef ORDERS_H
#define ORDERS_H

#include <list>
#include <iostream>
using namespace std;

class Order
{
public:
    Order();                //default contrustor
    bool validate();        //Invalid orders can be in OL, will check if valid for execution
    bool execute();         //prints the order after execution
    int incrementCount();   //countOrderID + 1
    int getOrderID();
    virtual void addDescription();
    virtual string getDescription();
    void setValid(bool v);
protected:
    string description;
    bool valid;
private:
    static int countOrderID;
    int orderID;
    friend ostream& operator << (ostream& out, Order* o); //overide Stream insertion operator

};

class Deploy : public Order
{
public:
    Deploy();
    virtual void addDescription();
    virtual string getDescription();
private:
};

class OrdersList
{
public:
    OrdersList();                       //default constructor
    virtual void addOrder(Order *o);
    bool move(int index, int orderID);  //Modify sequence of orders
    bool remove(int orderID);           //removes order from ordersList
    list<Order*> getOL();
private:
    list<Order*> OL;  
    friend ostream& operator << (ostream& out, OrdersList& ol); //overide Stream insertion operator         
};

// end marker for the above's #ifndef
#endif