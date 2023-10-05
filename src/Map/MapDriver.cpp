#include "Map.h"

using namespace std;

void testLoadMaps() {
    cout << "\n" << "*************************************" << "\n"
        << "Test Map\n"
        << "*************************************" << "\n" << "\n";
    MapLoader* loader = new MapLoader();

    cout << "---------> Test 1: Load a valid map <---------" << "\n" << "\n";
    loader->loadMap("Map/MapFolder/cliff.map");


    cout << "---------> Test 2: Load an invalid map <---------" << "\n" << "\n";
    cout << "todo";

    cout << "---------> Test 3: Load a file that doesnt exist <---------" << "\n" << "\n";
    loader->loadMap("Map/MapFolder/idontexist.map");

    cout << "---------> Test 4: Validate map <---------" << "\n" << "\n";
    cout << "todo";
};