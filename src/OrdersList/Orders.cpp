#include <map>
#include <iostream>
using namespace std;

#include "Orders.h"

bool pFlag = false;                  //Flag for print statements
int Order::countOrderID = 0;        //start counter for orders at 0

Order::Order() {
    orderID = incrementCount();
    addDescription();
    setValid(false);
};

bool Order::validate() { //Invalid orders can be in OL, will check if valid for execution
    return this->valid;
};

void Order::execute() {
    if(validate()==1) {
        cout << "Executing order #" << getOrderID() <<" ..." << endl;
    }
    else 
        cout << "Can NOT execute order #" << getOrderID() << " ..." << endl;
};

int Order::incrementCount() {
    return ++countOrderID;
};

int Order::getOrderID() {
    return orderID;
}

void Order::addDescription() {
    this->description = "(Order Class)";
}

string Order::getDescription(){
    return this->description;
}

void Order::setValid(bool v){
    this->valid = v;
}

//Stream insertion operator
//will ouptut to console everytime "cout <<" is used on Order Object
//like toString but directly from cout<<
ostream& operator << (ostream& out, Order* o)
{
    //If true return "true", b/c c++ will return 1
    auto printBoolValue = [](bool b) { if (b) return "true"; else return "false"; };

    out << "OrderID: " << o->getOrderID() << endl
        << "Descrption: " << o->getDescription() << endl
        << "Is valid: " << printBoolValue(o->validate()) <<endl;
    return out;
}

Deploy::Deploy() {
    this->addDescription();
}

void Deploy::addDescription() {
    this->description = "(Deploy) Move a certain number of army units from the current "
        "player's reinforcement pool to one of the current player's territories.";
}

string Deploy::getDescription() {
    return this->description;
}

Advance::Advance() {
    this->addDescription();
}

void Advance::addDescription() {
    this->description = "(Advance) Move a certain number of army units from one territory" 
                    "(source territory) to another territory (target territory).";
}

string Advance::getDescription() {
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
    cout << "--OrdersList-- " << endl;
    for (it = OL.begin(); it != OL.end(); it++)
    {
        out << *it;
    }
    // for (auto o : OL) // another way to loop through
    //     out << o;
    return out;
}







