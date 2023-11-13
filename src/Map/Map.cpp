#include <stack>
#include "Map.h"

using namespace std;

/************************************************************ Map ************************************************************/
/**
* Default constructor
*/
Map::Map() {}

/**
* Copy constructor
*/
Map::Map(const Map& m) {
    cout << "...Testing the copy constructor...\n";
    territories = m.territories;
    continents = m.continents;
}

/**
* Param constructor
*/
Map::Map(map<int, Continent*> c, map<int, Territory*> t) {
    continents = c;
    territories = t;
}

/**
* Destructor
*/
Map::~Map() {
    // delete all territories
    for (pair<int, Territory*> territory : territories){
        delete territory.second;
        territory.second = NULL;
    }


    // delete all continents
     for (pair<int, Continent*> continent : continents){
        delete continent.second;
        continent.second = NULL;
    }
}

map<int, Territory*> Map::getterritories() { return this->territories;}

// Modify the Map class to include this member function
vector<Territory*> Map::getTerritories(int playerID) {
    vector<Territory*> territoriesOwnedByPlayer;
    for (const auto& territoryPair : territories) {
        Territory* territory = territoryPair.second;
        if (territory->getOwnerId() == playerID) {
            territoriesOwnedByPlayer.push_back(territory);
        }
    }
    return territoriesOwnedByPlayer;
}

string Territory::getContinentName()
{
    return continentName;
}

Territory* Map::getTerritory(string tName){
    for (auto const& t : this->getterritories()) {
        if (t.second->getName().compare(tName) == 0) {
            return t.second;
        }
    }
    return NULL;
}

/**
* Will be stored in a key value pair ex: (1, Continent)
*/
void Map::addContinent(Continent* continent) {
    continents[continent->getId()] = continent;
}

/**
* Will be stored in a key value pair ex: (1, Territory)
*/
void Map::addTerritory(Territory* territory) {
    territories[territory->getId()] = territory;
}

/**
* Print the summary of map
*/
void Map::printMapSummary() {
    cout << "\n" << "Continents of the loaded map: \n" << "-------------------\n";
    for (auto const& continent : continents) {
        cout << "ID: " << continent.second->getId() << "   |  Name:" << continent.second->getName() <<"\n";
        cout << "---------------------------\n";

    }
    cout << "\n" << "Territories of the loaded map: \n" << "-------------------\n";
    for (auto const& territory : territories) {
        cout << "ID: " << territory.second->getId() << "  |  Name: " << territory.second->getName() << " ---> Connected to: ";
        for(Territory* connected : territory.second->getAdjacencyList()) {
            cout << connected->getName() << " ";
        }
        cout << "\n---------------------------\n";
    }
}

/**
* Validate the map structure
* 1) the map is a connected graph
* 2) continents are connected subgraphs 
* 3) each country belongs to one and only one continent
*/
bool Map::validate() {
    cout << "...Validate the map...\n";
    // 1) confirm that the graph is NOT fully connected
    // 2) find a continent that is not connected
    map<int, bool> visited;
    map<int, bool> visitedContinent;
    stack<Territory*> territoryStack;

    territoryStack.push(territories.find(1)->second);
    while (!territoryStack.empty()) {
        Territory* current = territoryStack.top();
        territoryStack.pop();

        // check if the key exists in visited
        if (visited.count(current->getId()) == 0) {
            visited[current->getId()] = true;
            // check if adjacent territories have a key in visited and if not add them to the territoryStack to test them next
            for (Territory* neighbor : current->getAdjacencyList()) {
                if (visited.count(neighbor->getId()) == 0) {
                    territoryStack.push(neighbor);
                }
            }
        }
        // repeat the same logic for continents
        if (visitedContinent.count(current->getId()) == 0) {
            visitedContinent[current->getContinentId()] = true;
        }

    }
    // loop through territories and see if they have been visited
    for(int i = 1 ; i < territories.size() + 1 ; i++){
        if(visited.count(territories.find(i)->second->getId()) == 0){
            cout << "...Error: not ALL territories have been visited and hence the graph is NOT connected...\n";
            cout << "...Territory " << territories.find(i)->second->getName() << " is NOT connected...\n\n\n";

            return false;
        }
    }
    // loop through continents and see if they have been visited
    for(int i = 1 ; i < continents.size() + 1 ; i++){
        if(visitedContinent.count(continents.find(i)->second->getId()) == 0){
            cout << "...Error: not ALL continents have been visited and hence the graph is NOT connected...\n";
            cout << "...Continent " << continents.find(i)->second->getName() << " is NOT connected...\n\n\n";
            return false;
        }
    }

    // 3) ensure country belongs to only one and only continent
    // make a copy of the adjacency list
    // Finding duplicates confirms that a territory belongs to multiple continents because when creating the map,
    // the territory instance will only ever contain one continent
     for(int i = 1 ; i < territories.size() + 1; i++){
        for(int j = i + 1; j < territories.size() + 1; j++) {
            if(territories.at(i)->getName().compare(territories.at(j)->getName()) == 0) {
                //found duplicate (two territories have the same name)
                cout << "...Error: non unique name for territory\n\n";
                return false;
            }
        }
     }
    cout << "...Success! Map has been validated\n\n";
    return true;

}

/************************************************************ Continent ************************************************************/
/**
* Default Constructor
*/
Continent::Continent() {}

/**
* Param constructor
*/
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
/**
* Default Constructor
*/
Territory::Territory() {ownerId = 0;}

/**
* Param constructor
*/
Territory::Territory(string n, int i, int ci, int a) {
    name = n;
    id = i;
    continentId = ci;
    armyCount = a;
    ownerId = 0;
}

string Territory::getName(){
    return name;
}

int Territory::getId() const{
    return id;
}

int Territory::getContinentId() const{
    return continentId;
}

int Territory::getOwnerId() const{
    return ownerId;
}

void Territory::setOwnerId(int newOwner){
    this->ownerId = newOwner;
}

int Territory::getArmyCount() const{
    return armyCount;
}

void Territory::setArmyCount(int newCount){
    this->armyCount = newCount;
}

void Territory::addToArmyCount(int x) {
    this->armyCount = this->armyCount + x;
}

void Territory::subFromArmy(int x){
    this->armyCount = this->armyCount - x;
}

vector<Territory*> Territory::getAdjacencyList() {
    return adjacencyList;
}

/**
* Per example we have A,B,C which are all objects of territory
* If we call A.addAdjacentTerritory(B) then:
* 1. We will keep track of B from A
* 2. Keep track of A from B
* Hence we keep track of adjacent territories
*/
void Territory::addAdjacentTerritory(Territory* destination) {
    // current object's adjacency list
    this->adjacencyList.push_back(destination);
    // the destination object's adjacency list
    destination->adjacencyList.push_back(this);
}


ostream& operator << (ostream& out, Territory* t)
{
    out << "Territory: " << (t->getName())
        << " | ID: " << t->getId()
        << " | ContinentID: " << t->getContinentId()
        << " | Owner: " << t->getOwnerId()
        << " | Army Count: " << t->getArmyCount() << "\n\n";
    return out;
}

/************************************************************ MapLoader ************************************************************/

/**
* Will read the map file (will handle errors if file doesnt exist or can't open)
* Will parse line by line
* The file is divided in to two important sections: Continents & Territories
* Continents look like so: 
* continentName=howManyTerritoriesItHas
* Territories look like so: 
* territoryName, coord-x, coord-y, continent, listOfAdjacentTerritories seperated by commas
*/
Map* MapLoader::loadMap(string filename) {
    cout << "...Loading the map...\n";
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
        cout << "...Error: Failed to open the file...\n";
        return loadedMap; // Exit the program
    }

    // Go line by line and create territories
    string line;
    // While there exists lines in the file
    while (getline(inputFile, line) && !inputFile.eof()) {
        // Go over the continents (if we found the word "Continents" the start index of the line should be 0)
        if (line.find("[Continents]") == 0) {
            // Keep track of the # of continents we created to use it as their ID
            int continentId = 0;
            // While we have not reached a space (to the next section)
            while (getline(inputFile, line) && line.find("[Territories]") != 0) {
                // if there is return carriage character at the end of a line, erase it, to facilitate Conquest Map processing
                if (line.find("\r") == line.length() - 1) {
                    line = line.substr(0, line.length() - 1);
                }
                // if there is a space between the continents we can continue to search for them all the way until we reach territories
                if (line.length() == 0) {
                    continue;
                }
                // Create a vector of words that were split by an equals (look the map file for details)
                vector<string> words = MapLoader::split(line, "=");

                // The line should contain the name and number of territories that belong to the continent (hence 2 words)
                if (words.size() != 2) {
                    cout << "...Error: Invalid continent information...\n";
                    return loadedMap;
                }

                string continentName = words[0];
                int controlBonusValue;
                try {
                    controlBonusValue = stoi(words[1]);
                } catch (const std::invalid_argument& e) {
                    cout << "...Error: Not an integer...\n";
                    return loadedMap;
                } catch (const std::out_of_range& e) {
                    cout << "...Error: Out of range for an int...\n";
                    return loadedMap;
                }
                // Create a new continent with an auto incrementing id
                auto* continent = new Continent(continentName, ++continentId);
                loadedMap->addContinent(continent);
                continentsAndBonus.insert(std::pair<int, Continent*>(controlBonusValue, continent));
                // Keep track of the list of continents we created thus far
                continents.push_back(continent);
            }
        }

        // Go over the territories (if we found the word "Territories" the start index of the line should be 0)
        if (line.find("[Territories]") == 0 && !inputFile.eof()) {
            int territoryId = 0;
            // While we have not reached the end of the file
            while (getline(inputFile, line)) {
                // if there is return carriage character at the end of a line, erase it, to facilitate Conquest Map processing
                if (line.find("\r") == line.length() - 1) {
                    line = line.substr(0, line.length() - 1);
                }
                // If there is a space between the territories, skip that line and go to the next one
                if (line.length() == 0) {
                    continue;
                }
                // Create a vector of words that were split by a comma
                vector<string> words = MapLoader::split(line, ",");
                // There is a minimum requirement of name, x-coord, y-coord, and continent (hence 4 words)
                if (words.size() < 4) {
                    cout << "...Error: Invalid territory information...\n";
                    return loadedMap;
                }
                string territoryName = words[0];
                string territoryContinentName = words[3]; // the continent that the territory belongs to
                // We have access to the continent name by reading the file, but not the id
                // hence we need to loop through our previously created list of continents and find the id of the continent by the given name
                int continentId = -1;
                for (int i = 0; i < continents.size(); i++) {
                    if (continents.at(i)->getName() == territoryContinentName) {
                        continentId = continents.at(i)->getId();
                    }
                }

                // If continent isn't found, then there is an error in parsing the continents
                if (continentId == -1) {
                    cout << "...Error: Invalid continent/territory information...\n";
                    return loadedMap;
                }
                // Create a new territory
                auto* territory = new Territory(territoryName, ++territoryId, continentId, 0);
                loadedMap->addTerritory(territory);
                // Anything past index 3 is what is connected to our territory
                for (int i = 4; i < words.size(); i++) {
                    // Create an adjacency map list
                    territoryAdjacencyMap[territory].push_back(words[i]);
                    // Keep track of all the territories like so: (name, Territory), will be used in the adjacency process
                    territoryMap[territory->getName()] = territory;

                }
            }
        }

        // Going over the adjacency list to add the territories the adjacencyList of the territory
        for (auto const& territory : territoryAdjacencyMap) {
            // Loop through all the adjacent territories
            for (int i = 0; i < territory.second.size(); i++) {
                string key = territory.second.at(i);
                // create linkage
                territory.first->addAdjacentTerritory(territoryMap.at(key));

            }
        }
    }

    // Close the file
    inputFile.close();
    cout << "...Successfully loaded the Map...\n";
    return loadedMap;
}

/**
* Must split each line of the map as each line has the following stuctor ex:
* Sun1,83,81,SUN,Sun2,Sun3,Sun4,Sun5,Mercury1
* we want to create a vector of those words ["Sun1", "83"...]
*/
vector<string> MapLoader::split(string line, string delim) {

    vector<string> words;
    int start = 0;
    string word;

    // Continue while a delimiter is found
    while ((start = line.find(delim)) != string::npos) {
        // Remove the delimiter
        word = line.substr(0, start);
        // If word exists, add it to the array of words to return
        if (word != "") {
            words.push_back(word);
        }
        // Remove the stuff I have already found
        line.erase(0, start + delim.length());
    }

    // For the last word (ex: 1̶,̶2̶,̶3) where "1,2," were already covered
    if (!line.empty()) {
        words.push_back(line);
    }

    return words;
}
