#include "Map.h"

using namespace std;

/************************************************************ Map ************************************************************/
Map::Map() {};

/// <summary>
/// will be stored in a key value pair ex: (1, Contient)
/// </summary>
void Map::addContinent(Continent* continent) {
    continents[continent->getId()] = continent;
}

/// <summary>
/// will be stored in a key value pair ex: (1, Territory)
/// </summary>
void Map::addTerritory(Territory* territory) {
    territories[territory->getId()] = territory;
}

/************************************************************ Continent ************************************************************/
  /// <summary>
  /// Default Constructor
  /// </summary>
Continent::Continent() {}
/// <summary>
/// Param constructor
/// </summary>
Continent::Continent(string n, int i) {
    name = n;
    id = i;
}

string Continent::getName() const {
    return name;
}

int Continent::getId() const {
    return id;
}
/************************************************************ Territory ************************************************************/
  /// <summary>
  /// Default Constructor
  /// </summary>
Territory::Territory() {}

/// <summary>
/// Param constructor
/// </summary>
Territory::Territory(string n, int i, int ci) {
    name = n;
    id = i;
    continentId = ci;
}

string Territory::getName() const {
    return name;
}

int Territory::getId() const {
    return id;
}

/// <summary>
/// imagine we have A,B,C which are all objects of territory
/// if we call A.addAdjacentTerritory(B) then:
/// 1. We will keep track of B from A
/// 2. Keep track of A from B
/// hence we keep track of adjecent territories
/// </summary>
void Territory::addAdjacentTerritory(Territory* destination) {
    // current object's adjeceny list
    this->adjacencyList.push_back(destination);
    // the destination object's adjecey list
    destination->adjacencyList.push_back(this);
}
/************************************************************ MapLoader ************************************************************/


void MapLoader::loadMap(string filename) {
    cout << "...Loading the map..." << endl;
    // Define the needed params
    vector<Continent*> continents;
    Map* loadedMap = new Map();
    map<Territory*, vector<string>> territoryAdjacencyMap;
    map<string, Territory*> territoryMap;

    // Start reading the file by opening it
    ifstream inputFile;
    inputFile.open(filename);

    // Check if the file was successfully opened
    if (!inputFile.is_open()) {
        cout << "...Error: Failed to open the file..." << endl;
        return; // Exit the program
    }

    // Go line by line and create territories
    string line;
    // While there exists lines in the file
    while (getline(inputFile, line) && !inputFile.eof()) {
        // Go over the contintents (if we found the word "Continents" the start index of the line should be 0)
        if (line.find("[Continents]") == 0) {
            // keep track of the # of continents we created to use it as their ID
            int continentId = 0;
            // while we havent not reached a space (to the next section)
            while (getline(inputFile, line) && line.length() != 0) {
                // create a vector of words that were split by a equals (look the map file for details)
                vector<string> words = MapLoader::split(line, "=");
                // the line should contain the name and number of territories that belong to the continent (hence 2 words)
                if (words.size() != 2) {
                    cout << "...Error: Invalid continent information..." << endl;
                    return;
                }
                string continentName = words[0];
                // create a new contintent with an auto incrementing id
                Continent* continent = new Continent(continentName, ++continentId);
                loadedMap->addContinent(continent);
                // keep track of the list of continents we created thus far
                continents.push_back(continent);
            }
        }
        // Go over the territories (if we found the word "Territories" the start index of the line should be 0)
        else if (line.find("[Territories]") == 0) {
            int territoryId = 0;
            // continue reading the input file
            while (getline(inputFile, line)) {
                // if there is a space between the territories, skip that line and go to the next one
                if (line.length() == 0) {
                    continue;
                }
                // create a vector of words that were split by a comma
                vector<string> words = MapLoader::split(line, ",");
                // there is a minimum requirement of name, x-coord, y-coord, and continent (hence 4 words)
                if (words.size() < 4) {
                    cout << "...Error: Invalid territory information..." << endl;
                    return;
                }
                string territoryName = words[0];
                string territoryContinentName = words[3]; // the continent that the territory belongs to
                // we have access to the continent name by reading the file, but not the id
                // hence we need to loop through our priviously created list of continents and find the id of the continent by the given name
                int continentId;
                for (int i = 0; i < continents.size(); i++) {
                    if (continents.at(i)->getName() == territoryContinentName) {
                        continentId = continents.at(i)->getId();
                    }
                }
                // create a new territory
                Territory* territory = new Territory(territoryName, ++territoryId, continentId);
                loadedMap->addTerritory(territory);
                // anything past index 3 is what is connected to our territory
                for (int i = 4; i < words.size(); i++) {
                    // create an adjeceny map list
                    /**
                    * territoryAdjacencyMap structure:
                    * (id, name) --> vector of adjecent territories (id, name)
                    * Terr1 --> [Terr2,Terr3]
                    * Terr2 --> [Terr1]
                    */
                    territoryAdjacencyMap[territory].push_back(words[i]);
                    // keep track of all the territories like so: (name, Territory), will be used in the adjecency proccess
                    territoryMap[territory->getName()] = territory;

                }
                cout << "\n";
            }
        }

        // going over the adjacency list to add the territories the adjacencyList of the territory
        for (auto const& territory : territoryAdjacencyMap)
            /**
             * territoryAdjacencyMap structure:
             * (id, name) --> vector of adjecent territories (id, name)
             * Terr1 --> [Terr2,Terr3]
             * Terr2 --> [Terr1]
             * */
        {
            // TODO: fix the bug where the map is out of bounds 
            // the territory
            cout << territory.first->getId() << "  -->  " << territory.first->getName() << "\n";
            // loop through all the adjecent territories
            for (int i = 0; i < territory.second.size(); i++) {
                // cout << "       -            " << territory.second.size() << "    -   " << i  << "\n\n";
                string key = territory.second.at(i);
                // create linckage 
                territory.first->addAdjacentTerritory(territoryMap.at(key));
                cout << "------adjecent------" << territoryMap.at(key)->getId() << "   " << territoryMap.at(key)->getName() << "\n";

            }
        }
    }

    // Close the file
    inputFile.close();
    cout << "...Successfully loaded the Map..." << "\n";

    /// <summary>
    /// Print out the map
    /// </summary>


     /// <summary>
    /// Validate the map
    /// </summary>
}

/// <summary>
/// Must split each line of the map as each line has the following stuctor ex:
///  Sun1,83,81,SUN,Sun2,Sun3,Sun4,Sun5,Mercury1
/// we want to create a vector of those words ["Sun1", "83"...]
/// </summary>
vector<string> MapLoader::split(string line, string delim) {

    vector<string> words;
    int start = 0;
    string word;

    // continue while a delimiter is found
    while ((start = line.find(delim)) != string::npos) {
        // remove the delimiter
        word = line.substr(0, start);
        // if word exists, add it to the array of words to return
        if (word != "") {
            words.push_back(word);
        }
        // remove the stuff I have already found
        line.erase(0, start + delim.length());
    }

    // for the last word (ex: 1̶,̶2̶,̶3) where "1,2," were already covered
    if (!line.empty()) {
        words.push_back(line);
    }

    return words;
}