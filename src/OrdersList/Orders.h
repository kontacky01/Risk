#ifndef ORDERS_H
#define ORDERS_H

#include <list>
#include <iostream>
using namespace std;

class Order
{
public:
    Order();                //default contrustor
    Order(Order *o);        //Deep Copy
    bool validate();        //Invalid orders can be in OL, will check if valid for execution
    virtual void execute();         //prints the order after execution
    int incrementCount();   //countOrderID + 1
    void setOrderID(int id);
    int getOrderID();
    virtual void addDescription();
    virtual string getDescription();
    void setValid(bool v);
protected:
    string description;
private:
    static int countOrderID;
    int orderID;
    bool valid;     //default false
    friend ostream& operator << (ostream& out, Order* o); //overide Stream insertion operator

};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(Deploy *d);      //Deep Copy
    void execute();
    void addDescription();
    string getDescription();
private:
};

class Advance : public Order
{
public:
    Advance();
    Advance(Advance *a);
    void execute();
    void addDescription();
    string getDescription();
private:
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(Bomb* a);
    void execute();
    void addDescription();
    string getDescription();
private:
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(Blockade* a);
    void execute();
    void addDescription();
    string getDescription();
private:
};

class Airlift : public Order
{
public:
    Airlift();
    Airlift(Airlift* a);
    void execute();
    void addDescription();
    string getDescription();
private:
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Negotiate* a);
    void execute();
    void addDescription();
    string getDescription();
private:
};

class OrdersList
{
public:
    OrdersList();                       //default constructor
    virtual void addOrder(Order *o);
    bool move(int pos, int id);  //Modify sequence of orders
    bool remove(int id);                //remove order by id
    list<Order*> getOL();
private:
    list<Order*> OL;  
    friend ostream& operator << (ostream& out, OrdersList& ol); //overide Stream insertion operator         
};

// end marker for the above's #ifndef
#endif