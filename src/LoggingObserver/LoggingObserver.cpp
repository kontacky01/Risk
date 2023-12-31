#include "LoggingObserver.h"
#include "../OrdersList/Orders.h"
#include "../Player/Player.h"
#include "../CardsDeck/Cards.h"
#include "../CommandProcessing/CommandProcessing.h"

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

    // test the save command
    string c = "loadmap";
    CommandProcessor * cp = new CommandProcessor();
    cp->attach(logger);
    Command* cmd = new Command(c);
    cp->saveCommand(c);

    // test command effect
    cmd->attach(logger);
    cmd->saveEffect("map loaded");

    delete cmd;
    cmd = NULL;

    delete cp;
    cp = NULL;

    delete logger;
    logger = NULL;


/*
    // create  territory, state, hand, orderlist and player to test
    vector<Territory *> t;
    Territory *t6 = new Territory("Bulgaria", 6, 3, 0);
    //ExecuteordersState *executeordersState = new ExecuteordersState("executeorders");
    auto *executeordersState = new ExecuteordersState();
    Hand *h = new Hand();
    OrdersList *o = new OrdersList;
    t.push_back(t6);
    //Player *p = new Player(t, h, o, 1, executeordersState);
    Player *p = new Player(t, h, o, 1);
    Deploy *deploy = new Deploy(p, t6, 3);
    deploy->setValid(true);

    // attach modal to view 
    deploy->attach(logger);
    // trigger execution of order
    deploy->execute();

    // attach modal to view 
    o->attach(logger);
    // add the order to the player's orderlist 
    p->issuesOrder(deploy); // should call Order::addOrder and notify the observer

    delete t6;
    t6 = NULL;

    delete p; // will delete all items that were passed to players constructor such as territories, hand, orderlist and state
    p = NULL;


*/
}


// TODO: when merged
// CommandProcessor::saveCommand() - TODO
// Command::saveEffect() - TODO 
// Order::execute() --> DONE, BUT THE EFFECT ISNT READY, SO NEED TO ADD IT WHEN WE MERGE
// OrderList::addOrder() --> DONE
// GameEngine::transition() - TODO

//todo: extend the following classes when merged:
// Order - DONE 
// OrderList -DONE
/// TODO:
// GameEngine 
// Command
// CommandProcessor
