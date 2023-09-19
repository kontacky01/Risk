#include <map>
#include <iostream>
using namespace std;

#include "Order.h"

bool pFlag = true;
int Order::countOrderID = 0;

Order::Order() {
    orderID=incrementCount();
};    

/* Invalid orders can be created and put in the list,
    * but their execution will not result in any action.
    * Returns true if valid
    */
bool Order::validate(){
    if(pFlag) cout << "validate() from inside Order\n";
    return true;
};

bool Order::execute(){
    if (pFlag) cout << "validate() from inside Order\n";
    return true;
};     
    
int Order::incrementCount(){
    return ++countOrderID;
    if (pFlag) cout << "incremenet() from inside Order\n";
};

void Order::toString(){
    cout << "I am order number " << orderID << "\n";
};

Deploy::Deploy(){}
