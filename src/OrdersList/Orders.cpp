#include <iostream>

#include "Orders.h"

using namespace std;

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

Airlift::Airlift(Airlift *a) {
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
    list<Order*> OL;
}

void OrdersList::addOrder(Order *o){
    OL.push_back(o);
}

//input:
//pos is position wish to place, list starts at position 1 (1st, 2nd, etc...)
//id of order wish to move
bool OrdersList::move(int pos, int id){
    //post out of bounds
    int size = OL.size();
    if (pos == 0 || pos < 0 || pos > size) {
        cout << "From move(): position " << pos << " does not exist" <<endl;
        return false;
    }
    //pos = 1, send to front of list
    if (pos == 1) {
        for (auto o : this->OL) {
            if (o->getOrderID() == id) {
                this->OL.remove(o); // remove Order from List
                this->OL.push_front(o); //place in front
                return true;
            }
        }
    }
    //pos = last
    if (pos == size) {
        for (auto o : this->OL) {
            if (o->getOrderID() == id) {
                this->OL.remove(o); // remove Order from List
                this->OL.push_back(o); //place in front
                return true;
            }
        }
    }
    //first position is >=2
    list<Order*>::iterator it = this->OL.begin();
    for (int i = 0; i < pos - 1; i++) { ++it; } //incrmenet iterator to pos (can not add with integer)
    for (auto o : this->OL) {
        if (o->getOrderID() == id) {
            this->OL.remove(o); // remove Order from List
            this->OL.insert(it,o); // use insert from list std
            return true;
        }
    }
    return false;
}

bool OrdersList::remove(int id) { //remove order by orderID
    for (auto o : this->OL) {
        if (o->getOrderID() == id) {
            this->OL.remove(o);
            delete o;
            return true;
        }
    }
    cout<< "From remove(): Order#" << id << " does not exist" <<endl;
    return false;
}

list <Order*> OrdersList::getOL(){
    return this->OL;
}

void OrdersList::deleteOrdersList(){
    //Delete pointers and free memory
    for (auto o : this->getOL()) {
        delete o;   // deallocate  memory
        o = NULL;   // prevent dangling pointer error
    }
}

ostream& operator << (ostream& out, OrdersList& ol){
    list<Order*>::iterator it;
    list<Order*>OL = ol.getOL();
    cout << "--OrdersList-- " << endl;
    for (it = OL.begin(); it != OL.end(); it++)
    {
        out << *it;
    }
    return out;
}







