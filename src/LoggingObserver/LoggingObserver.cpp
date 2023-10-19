#include "LoggingObserver.h"
#include "../OrdersList/Orders.h" // ? where should i put those files, h or cpp?
#include "../GameEngine/GameEngine.h"
/************************************************************ Subject ************************************************************/
    /**
     * Attach to view
     */
    void Subject::attach(Observer* observer){
        observers.push_back(observer);
    }

    /**
     * Detach from view
     */
    void Subject::detach(Observer* observer){
        observers.remove(observer);
    }

    /**
     * Notify all observers that a change has been made in the state
     */
    void Subject::notify(ILoggable* loggable){
        // create an iterator
        list<Observer*>::iterator i = observers.begin();
        for(;i != observers.end(); i++){
            (*i)->update(loggable);
        }
    }
/************************************************************ LogObserver ************************************************************/
void LogObserver::update(ILoggable* loggable) {
    cout << loggable->stringToLog();
}
/************************************************************ LoggingDriver ************************************************************/

void testLoggingObserver() {
    LogObserver* logger = new LogObserver();
    State* executeordersState = new State("executeorders");
    Deploy* deploy = new Deploy();
    deploy->attach(logger);

    // trigger execution of order
    deploy->execute(executeordersState);
    
    // todo: write to file
}