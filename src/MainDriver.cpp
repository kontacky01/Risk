#include "Map/Map.h"
#include "Player/Player.h"
#include "OrdersList/Orders.h"
#include "CardsDeck/Cards.h"
#include "GameEngine/GameEngine.h"
#include "LoggingObserver/LoggingObserver.h"

int main() {
    /* 
    * Assignment 1
    */
    //testLoadMaps();
    //testOrdersLists();
    //testPlayers();
    //testCards();
    testGameStates();

    /*
    * Assignment 2
    */

    //testCommandProcessor(); //part 1 in CommandProcessingDriver.cpp
    //testStartupPhase();  //part2 in GameEngineDriver.cpp
    //testMainGameLoop();  //part3 in GameEngineDriver.cpp
    //testOrderExecution();  //part4 in OrdersDriver.cpp
    //testLoggingObserver(); //part5 in LoggingObserverDriver.cpp
  
    return 0;
}
