#include <map>
#include <iostream>
using namespace std;

#include "Orders.h"

bool pFlag = true;                  //Flag for print statements
int Order::countOrderID = 0;        //start counter for orders at 0

Order::Order() {
    orderID = incrementCount();
    addDescription();
};

bool Order::validate() { //Invalid orders can be in OL, will check if valid for execution
    if (pFlag) cout << "validate() from inside Order\n";
    return true;
};

bool Order::execute() {
    if (pFlag) cout << "validate() from inside Order\n";
    return true;
};

int Order::incrementCount() {
    return ++countOrderID;
    if (pFlag) cout << "incremenet() from inside Order\n";
};

int Order::getOrderID() {
    return orderID;
}

void Order::addDescription() {
    this->description = "I am the Order Class";
}

string Order::getDescription(){
    return this->description;
}

//Stream insertion operator
//will ouptut to console everytime "cout <<" is used on Order Object
//like toString but directly from cout<<
ostream& operator << (ostream& out, Order* o)
{
    out << "OrderID: " << o->getOrderID() << endl
        << "Descrption: " << o->getDescription() << endl;
    return out;
}

Deploy::Deploy() {
    this->addDescription();
}

void Deploy::addDescription() {
    this->description = "Move a certain number of army units from the current "
        "player's reinforcement pool to one of the current player's territories.";
}

string Deploy::getDescription() {
    return this->description;
}

OrdersList::OrdersList(){
   std::list<Order*> OL;
}

void OrdersList::addOrder(Order *o){
    OL.push_back(o);
}

list <Order*> OrdersList::getOL(){
    return this->OL;
}

ostream& operator << (ostream& out, OrdersList& ol){
    list<Order*>::iterator it;
    list<Order*>OL = ol.getOL();
    for (it = OL.begin(); it != OL.end(); it++)
    {
        out << *it;
    }
    // for (auto o : OL) // another way to loop through
    //     out << o;
    return out;
}







