#include "Map/Map.h"
#include "Player/Player.h"
#include "OrdersList/Orders.h"
#include "CardsDeck/Cards.h"
#include "GameEngine/GameEngine.h"
#include "LoggingObserver/LoggingObserver.h"

int main()
{
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
    testStartupPhase();
    //testOrderExecution();
    //testLoggingObserver();
    //mainGameLoop();
    //testMainGameLoop();

    return 0;
}
