#pragma once

#include <iostream>
#include <fstream>
#include <list>

#include "C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/GameEngine/GameEngine.h"
#include "C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/Map/Map.h"
#include "C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/OrdersList/Orders.h"
#include "C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/CardsDeck/Cards.h"
#include "C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/Player/Player.h"
#include "C:/Users/konta/OneDrive/Desktop/COMP 345/Risk/src/CommandProcessing/CommandProcessing.h"

using namespace std;

/************************************************************ ILoggable ************************************************************/
class ILoggable {
// ? : does this need a constructor and destructor
public:
    virtual string stringToLog() = 0;
};

/************************************************************ Observer ************************************************************/
class Observer {
public:
    virtual void update(ILoggable *loggable) = 0;
};

/************************************************************ LogObserver ************************************************************/
class LogObserver : public Observer {
public:
    void update(ILoggable *loggable);

private:
    void printToFileHelper(string log);
};

/************************************************************ Subject ************************************************************/
class Subject {
public:
    /**
     * Attach to view
     */
    void attach(Observer *observer);

    /**
     * Detach from view
     */
    void detach(Observer *observer);

    /**
     * Notify all observers that a change has been made in the state
     */
    void notify(ILoggable *loggable);

private:
    list<Observer *> observers;
};


/************************************************************ LoggingDriver ************************************************************/
void testLoggingObserver();