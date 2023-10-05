#include "Map/Map.h"
#include "Player/Player.h"
#include "OrdersList/Orders.h"
#include "CardsDeck/Cards.h"
#include "GameEngine/GameEngine.h"

int main()
{
    testLoadMaps();
    testPlayers();
    testOrdersLists();
    testCards();
    testGameStates();
    return 0;
}
