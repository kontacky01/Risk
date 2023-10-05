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

/************************************************************ MapDriver ************************************************************/

void testLoadMaps();

/************************************************************ Territory ************************************************************/


class Territory {
private: 
    int id;
    int continentId;
    string name;
    vector<string*> adjacency_list;
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

    // // Destructor to clean up dynamically allocated memory
    // ~Territory() {
    //     for (string* adj : adjacency_list) {
    //         delete adj;
    //     }
    // }
};
/************************************************************ MapLoader ************************************************************/


class MapLoader {
public:
    void loadMap(string);
    vector<string> split(string s, string delim);
};