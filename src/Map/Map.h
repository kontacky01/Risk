#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

/************************************************************ Territory ************************************************************/


class Territory {
private:
    string name;
    int id;
    int continentId;
    int ownerId;
    int armyCount;

    vector<Territory *> adjacencyList;

    friend ostream &operator<<(ostream &out, Territory *o); // override Stream insertion operator

public:
    /**
    * Default constructor
    */
    Territory();

    /**
    * Param constructor
    */
    Territory(string name, int id, int continentId, int armyCount);

    string getName() const;

    string getContinentName();

    int getId() const;

    int getContinentId() const;

    int getOwnerId() const;

    void setOwnerId(int newOwner);

    int getArmyCount() const;

    void setArmyCount(int newCount);

    void addToArmyCount(int x);

    void subFromArmy(int x);

    // Getter for adjacencyList
    vector<Territory *> getAdjacencyList();

    /**
    * imagine we have A,B,C which are all objects of territory
    * if we call A.addAdjacentTerritory(B) then:
    * 1. We will keep track of B from A
    * 2. Keep track of A from B
    * hence we keep track of adjacent territories
    */
    void addAdjacentTerritory(Territory *);
    string continentName;
};

/************************************************************ Continent ************************************************************/

class Continent {
private:
    int id;
    int controlBonusValue;
    string name;

public:

    /**
    * Default Constructor
    */
    Continent();

    /**
    * Param Constructor
    */
    Continent(string, int);

    string getName() const;

    int getId() const;

    int getControlBonusValue() const;

    vector<Territory *> territoriesInContinents;

    vector<Territory *> getTerritories();

    void addTerritory(Territory *territory);
};

/************************************************************ Map ************************************************************/

class Map {
private:
    map<int, Continent *> continents;

public:
    /**
    * Default Constructor
    */
    Map();

    /**
    * Copy constructor
    */
    Map(const Map &);

    /**
    * Param constructor
    */
    Map(map<int, Continent *> continents, map<int, Territory *> territories);


    /**
    * Destructor
    */
    ~Map();

    map<int, Territory *> getterritories();

    vector<Territory *> getTerritories();

    Territory *getTerritory(string tName);

    Continent* getContinentById(int continentId);

    void addContinent(Continent *);

    void addTerritory(Territory *);

    /**
    * Print the summary of map
    */
    void printMapSummary();

    /**
    * Validate the map structure
    */
    bool validate();

    vector<Continent *> continentList;
    vector<Continent *> getContinents();
    vector<Territory *> territoryList;
    map<int, Territory *> territories;
};


/************************************************************ MapDriver ************************************************************/

void testLoadMaps();

Map *gameLoadMap(string);

void validateMap(Map &map);

void deleteMap(Map *map);

/************************************************************ MapLoader ************************************************************/


class MapLoader {
public:
    Map *loadMap(string);

    /**
    * Parse the .map file the map is in, by separating each line with a delimiter
    * The method will return a vector of words
    * For ex: 123,232,353 will be [123,232,353] so we can manipulate each item in the vector as such v.at(i)
    */
    vector<string> split(string s, string delim);

    multimap<int, Continent *> continentsAndBonus;

    void printContinentsAndBonuses() {
        cout << "Continents and their control bonus values:" << endl;
        for (const auto &pair: continentsAndBonus) {
            cout << "Bonus Value: " << pair.first << " -> Continent: " << pair.second->getName() << endl;
        }
    }
};