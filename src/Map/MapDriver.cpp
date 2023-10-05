#include "Map.h"

using namespace std;

void testLoadMaps() {
    cout << "\n" << "*************************************" << "\n"
        << "Test Map\n"
        << "*************************************" << "\n" << "\n";
    MapLoader* loader = new MapLoader();

    cout << "---------> Test 1: Load a valid map <---------\n\n";
    loader->loadMap("Map/MapFolder/cliff.map")->printMapSummary();


    cout << "\n\n---------> Test 2: Load a valid map <---------\n\n";
    Map*  m = new Map(*loader->loadMap("Map/MapFolder/solarSystem.map"));
    m->printMapSummary();


    cout << "\n\n---------> Test 3: Load an invalid map <---------\n\n";
    //loader->loadMap("Map/MapFolder/cliffInvalid.map")->printMapSummary();


    cout << "\n\n---------> Test 4: Load a file that doesnt exist <---------\n\n";
    loader->loadMap("Map/MapFolder/idontexist.map");

    cout << "\n\n---------> Test 5: Validate map <---------\n\n";
    cout << "TODO!!!!";

};