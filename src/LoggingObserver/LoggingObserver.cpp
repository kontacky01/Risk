#include "LoggingObserver.h"
/************************************************ Subject ************************************************************/
/**
 * Attach to view
 */
void Subject::attach(Observer *observer) {
    observers.push_back(observer);
}

/**
 * Detach from view
 */
void Subject::detach(Observer *observer) {
    observers.remove(observer);
}

/**
 * Notify all observers that a change has been made in the state
 */
void Subject::notify(ILoggable *loggable) {
    // create an iterator
    list<Observer *>::iterator i = observers.begin();
    for (; i != observers.end(); i++) {
        (*i)->update(loggable);
    }
}

/*************************************************** LogObserver *****************************************************/
void LogObserver::update(ILoggable *loggable) {
    string log = loggable->stringToLog();
    cout << log;
    printToFileHelper(log);
}

void LogObserver::printToFileHelper(string log) {

    // Create an ofstream object to work with a file
    ofstream outputFile;
    // Append instead of overwrite
    outputFile.open("gamelog.txt", ios_base::app);


    // Check if the file is successfully opened
    if (outputFile.is_open()) {
        // Write data to the file
        outputFile << log;

        // Close the file when you're done with it
        outputFile.close();
    }
}

/****************************************** LoggingDriver ************************************************************/

void testLoggingObserver() {
    // create the log observer
    LogObserver *logger = new LogObserver();
    // create  territory, state, hand, orderlist and player to test
    vector<Territory *> t;
    Territory *t6 = new Territory("Bulgaria", 6, 3, 0);
    //ExecuteordersState *executeordersState = new ExecuteordersState("executeorders");
    auto *executeordersState = new ExecuteordersState();
    Hand *h = new Hand();
    OrdersList *o = new OrdersList;
    t.push_back(t6);
    Player *p = new Player(t, h, o, 1);
    Deploy *deploy = new Deploy(p, t6, 3);
    deploy->setValid(true);

    delete t6;
    t6 = NULL;

    delete p; // will delete all items that were passed to players constructor such as territories, hand, orderlist and state
    p = NULL;


    delete logger;
    logger = NULL;


}


// TODO: when merged
// Order::execute() --> DONE, BUT THE EFFECT ISNT READY, SO NEED TO ADD IT WHEN WE MERGE