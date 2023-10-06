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
    m->validate();


    cout << "\n\n---------> Test 3: Load an invalid map <---------\n\n";
    loader->loadMap("Map/MapFolder/cliffInvalid.map");


    cout << "\n\n---------> Test 4: Load a file that doesnt exist <---------\n\n";
    loader->loadMap("Map/MapFolder/idontexist.map");

    cout << "\n\n---------> Test 5: Valid map <---------\n\n";
    loader->loadMap("Map/MapFolder/cliff.map")->validate();

    cout << "\n\n---------> Test 6: Validate map (invalid territories due to duplicates) <---------\n\n";
    loader->loadMap("Map/MapFolder/cliffError.map")->validate();
    
    cout << "\n\n---------> Test 7: Validate map - disconected territories <---------\n\n";
    loader->loadMap("Map/MapFolder/solarSystemError.map")->validate();

    cout << "\n\n---------> Test 8: Validate map - disconected continents <---------\n\n";
    loader->loadMap("Map/MapFolder/solarSystemErrorContinent.map")->validate();

    // todo
    // pointer to remove
    // add player for map

};