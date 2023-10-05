#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>
#include <map>

using namespace std;

/************************************************************ Continent ************************************************************/

class Continent {
private:
    int id;
    string name;

public:

    /// <summary>
    /// Default Constructor
    /// </summary>
    Continent();
    /// <summary>
    /// Param Constructor
    /// </summary>
    Continent(string, int);

    // Destructor
    ~Continent();

    // Getter for name
    string getName() const;

    // Getter for value
    int getId() const;
};

/************************************************************ Territory ************************************************************/


class Territory {
private:
    int id;
    int continentId;
    string name;
    vector<Territory*> adjacency_list;
public:
    /// <summary>
    /// Helper method to list attack/defended territories
    /// </summary>
    Territory();

    /// <summary>
    /// Helper method to list attack/defended territories
    /// </summary>
    Territory(string name, int id, int continentId);

    // Getter for name
    string getName() const;

    // Getter for value
    int getId() const;

    void addAdjacentTerritory(Territory*);
};
/************************************************************ Map ************************************************************/

class Map {
private:
    map<int, Territory*> territories;
    map<int, Continent*> continents;

public:
    Map();
    ~Map();

    void addContinent(Continent*);
    void addTerritory(Territory*);
};



/************************************************************ MapDriver ************************************************************/

void testLoadMaps();

/************************************************************ MapLoader ************************************************************/


class MapLoader {
public:
    void loadMap(string);
    vector<string> split(string s, string delim);
};