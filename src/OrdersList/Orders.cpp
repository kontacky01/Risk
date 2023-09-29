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

Order::Order( Order *o) {
    orderID = o->getOrderID();
    addDescription();
    setValid(false);
};

bool Order::validate() { //Invalid orders can be in OL, will check if valid for execution
    return this->valid;
};

void Order::execute() {
    if(validate()==1) cout << "Executing order #" << getOrderID() <<" ..." << endl;
    else cout << "Can NOT execute order #" << getOrderID() << " ..." << endl;
};

int Order::incrementCount() {
    return ++countOrderID;
};

void Order::setOrderID(int id){
    orderID = id;
}

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
    //Lambda: If true return "true", b/c c++ will return 1
    auto printBoolValue = [](bool b) { if (b) return "true"; else return "false"; };

    out << "OrderID: " << o->getOrderID() << endl
        << "Descrption: " << o->getDescription() << endl
        << "Is valid: " << printBoolValue(o->validate()) <<endl;
    return out;
}

/******************************* DEPLOY *********************************************/
Deploy::Deploy() {
    this->addDescription();
}

Deploy::Deploy(Deploy *d) {
    setOrderID(d->getOrderID());
    this->addDescription();
}

void Deploy::execute() {
    if (validate() == 1) cout << "Executing (Deploy) order #" << getOrderID() << " ..." << endl;
    else cout << "Can NOT execute (Deploy) order #" << getOrderID() << " ..." << endl;
};

void Deploy::addDescription() {
    this->description = "(Deploy) Move a certain number of army units from the current "
        "player's reinforcement pool to one of the current player's territories.";
}

string Deploy::getDescription() {
    return this->description;
}

/******************************* Advance *********************************************/
Advance::Advance() {
    this->addDescription();
}

Advance::Advance(Advance *a) {
    setOrderID(a->getOrderID());
    this->addDescription();
}

void Advance::execute() {
    if (validate() == 1) cout << "Executing (Advance) order #" << getOrderID() << " ..." << endl;
    else cout << "Can NOT execute (Advance) order #" << getOrderID() << " ..." << endl;
};

void Advance::addDescription() {
    this->description = "(Advance) Move a certain number of army units from one territory" 
                    "(source territory) to another territory (target territory).";
}

string Advance::getDescription() {
    return this->description;
}

/******************************* Bomb *********************************************/
Bomb::Bomb() {
    this->addDescription();
}

Bomb::Bomb(Bomb* a) {
    setOrderID(a->getOrderID());
    this->addDescription();
}

void Bomb::execute() {
    if (validate() == 1) cout << "Executing (Bomb) order #" << getOrderID() << " ..." << endl;
    else cout << "Can NOT execute (Bomb) order #" << getOrderID() << " ..." << endl;
};

void Bomb::addDescription() {
    this->description = "(Bomb) Destroy half of the army units located on a target territory." 
                        "This order can only be issued if a player has the bomb card in their hand.";
}

string Bomb::getDescription() {
    return this->description;
}

/******************************* Blockade *********************************************/
Blockade::Blockade() {
    this->addDescription();
}

Blockade::Blockade(Blockade* a) {
    setOrderID(a->getOrderID());
    this->addDescription();
}

void Blockade::execute() {
    if (validate() == 1) cout << "Executing (Blockade) order #" << getOrderID() << " ..." << endl;
    else cout << "Can NOT execute (Blockade) order #" << getOrderID() << " ..." << endl;
};

void Blockade::addDescription() {
    this->description = "(Blockade) Triple the number of army units on a target territory and make it a neutral territory. "
                        "This order can only be issued if a player has the blockade card in their hand.";
}

string Blockade::getDescription() {
    return this->description;
}

/******************************* Airlift *********************************************/
Airlift::Airlift() {
    this->addDescription();
}

Airlift::Airlift(Airlift* a) {
    setOrderID(a->getOrderID());
    this->addDescription();
}

void Airlift::execute() {
    if (validate() == 1) cout << "Executing (Airlift) order #" << getOrderID() << " ..." << endl;
    else cout << "Can NOT execute (Airlift) order #" << getOrderID() << " ..." << endl;
};

void Airlift::addDescription() {
    this->description = "(Airlift) Advance a certain number of army units from one from one territory (source territory) "
                        "to another territory (target territory). This order can only be issued if a player has the airlift card in their hand.";
}

string Airlift::getDescription() {
    return this->description;
}

/******************************* Negotiate *********************************************/
Negotiate::Negotiate() {
    this->addDescription();
}

Negotiate::Negotiate(Negotiate* a) {
    setOrderID(a->getOrderID());
    this->addDescription();
}

void Negotiate::execute() {
    if (validate() == 1) cout << "Executing (Negotiate) order #" << getOrderID() << " ..." << endl;
    else cout << "Can NOT execute (Negotiate) order #" << getOrderID() << " ..." << endl;
};

void Negotiate::addDescription() {
    this->description = "(Negotiate) prevent attacks between the current player and another target "
                        "player until the end of the turn. This order can only be issued if a player has the diplomacy card in their hand.";
}

string Negotiate::getDescription() {
    return this->description;
}

/******************************* OrdersList *********************************************/
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







