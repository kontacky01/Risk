#pragma once
#include <iostream>
#include <fstream>
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

    string getName() const;

    int getId() const;
};

/************************************************************ Territory ************************************************************/


class Territory {
private:
    int id;
    int continentId;
    string name;
    vector<Territory*> adjacencyList;
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

    /// <summary>
    /// imagine we have A,B,C which are all objects of territory
    /// if we call A.addAdjacentTerritory(B) then:
    /// 1. We will keep track of B from A
    /// 2. Keep track of A from B
    /// hence we keep track of adjecent territories
    /// </summary>
    void addAdjacentTerritory(Territory*);
};
/************************************************************ Map ************************************************************/

class Map {
private:
    map<int, Territory*> territories;
    map<int, Continent*> continents;

public:
    /// <summary>
    /// Default Constructor
    /// </summary>
    Map();

    /// <summary>
    /// Copy constructor
    /// </summary>
    Map(const Map&);


    /// <summary>
    /// Decconstructor
    /// </summary>
    ~Map();

    void addContinent(Continent*);

    void addTerritory(Territory*);

    /// <summary>
    /// print the summary of map
    /// </summary>
    void printMapSummary();
};



/************************************************************ MapDriver ************************************************************/

void testLoadMaps();

/************************************************************ MapLoader ************************************************************/


class MapLoader {
public:
    Map* loadMap(string);
    /// <summary>
    /// Parse the .map file the map is in, by seperating each line with a delimiter 
    /// The method will return a vector of words
    /// For ex: 123,232,353 will be [123,232,353] so we can manupulate each item in the vector as such v.at(i)
    /// </summary>
    vector<string> split(string s, string delim);
};