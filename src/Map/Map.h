#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>
#include <map>

class Continents {
public:
    // Constructor
    Continents(const string& continentName, int continentValue);

    // Destructor
    ~Continents();

    // Getter for name
    string getName() const;

    // Getter for value
    int getValue() const;

private:
    string name;
    int value;
};

/*class Territory {
public:
    Territory(); // Constructor
    ~Territory(); // Destructor

    // Data members
    string name;
    string continent;
    vector<string*> adjacency_list;
};*/

void testLoadMaps();




#endif