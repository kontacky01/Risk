#include "Map.h"

using namespace std;
//namespace fs = filesystem;

// class Map {
// private:
//     map<string, vector<string>> adjacencyList;

// public:
//     // add 'bidirectional' edge between two vertices
//     void addEdge(const string vertex1, const string vertex2) {
//         adjacencyList[vertex1].push_back(vertex2);
//         adjacencyList[vertex2].push_back(vertex1);
//     }

//     // print adjacency list
//     void printMap() {
//         for (const auto& pair : adjacencyList) {
//             cout << pair.first << " -> ";
//             for (const string& neighbor : pair.second) {
//                 cout << neighbor << " ";
//             }
//             cout << endl;
//         }
//     }

//     // delete dynamically allocated strings
//     void cleanup() {
//         adjacencyList.clear();
//     }

//     // destructor
//     ~Map() {
//         cleanup();
//     }

//     void readMap(string map_name) {
//         ifstream mapFile("../maps/" + map_name);
    
//         vector<string*> continents;
//         vector<string*> territories;

//         string line;
//         bool readContinents, readTerritories;

//         while (!mapFile.eof()) {
//             getline(mapFile, line);
//             if (line == "[Continents]\r") {
//                 readContinents = true;
//                 getline(mapFile, line);
//             }
//             if (line == "[Territories]\r") {
//                 readTerritories = true;
//                 readContinents = false;
//                 getline(mapFile, line);
//             }
//             if (readContinents && line != "\r")
//                 continents.push_back(new string(line));
//             if (readTerritories && line != "\r")
//                 territories.push_back(new string(line));
//     }

//         mapFile.close();

//         /*// print to console
//         cout << "Continents ->\n";
//         for (auto file_line : continents) {
//             cout << *file_line << endl;
//         }
//         cout << "\nTerritories ->\n";
//         for (auto file_line : territories) {
//             cout << *file_line << endl;
//         }*/

//         string input = "Mozambique,482,496,Southern Africa,Tanzania,Malawi,Madagascar,Zambia,Zimbabwe,South Africa";

//         vector<string*> result;
//         stringstream ss(input);
//         string word;

//         // split line into words
//         while (getline(ss, word, ',')) {
//             result.push_back(new string(word));
//         }

//         // remove coordinates values from vector
//         result.erase(next(result.begin(), 1), next(result.begin(), 3));

//         // print to console
//         for (const string* s : result) {
//             cout << *s << endl;
//         }

//         // file reader memory clean up
//         for (auto file_line : continents) {
//             delete file_line;
//             file_line = NULL;
//         }
//         for (auto file_line : territories) {
//             delete file_line;
//             file_line = NULL;
//         }
//         // Clean up memory by deleting the dynamically allocated strings
//         for (string* s : result) {
//             delete s;
//         }
//         result.clear(); // Clear the vector
//     }

// };

// /*class Territory {
// public:
//     string name;
//     string continent;
//     vector<string*> adjacency_list;

//     // Constructor
//     Territory() {}

//     // Destructor to clean up dynamically allocated memory
//     ~Territory() {
//         for (string* adj : adjacency_list) {
//             delete adj;
//         }
//     }
// };*/

// class Continents {
// public:
//     string name;
//     int value;

//     // constructor
//     Continents(const string& continentName, int continentValue)
//         : name(continentName), value(continentValue) {}

//     // destructor
//     ~Continents() {}
// };

// int MapDriver() {
//     // display directory contents
//     /*string path = "../maps";
//     for (const auto & entry : fs::directory_iterator(path)) {
//         cout << entry.path().filename() << endl;
//     }

//     cout << "\nChoose a file to open:" << endl;*/
    
//     Map m;
//     m.readMap("Africa.map");

//     // Add vertices and edges to create a connected graph
//     m.addEdge("A", "B");
//     m.addEdge("A", "C");
//     m.addEdge("B", "D");
//     m.addEdge("C", "E");
//     m.addEdge("D", "E");

//     // Print Map's adjacency list
//     m.printMap();

//     // dynamically allocated strings memory clean up
//     m.cleanup();

// 	return 0;
// }

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
/************************************************************ MapLoader ************************************************************/


void MapLoader::loadMap(string filename) {
     cout << "...Loading the map..." << endl;
    //read the file
    ifstream inputFile;
    inputFile.open(filename);
    vector<Continent*> continents;

    // Check if the file was successfully opened
    if (!inputFile.is_open()) {
        std::cout << "...Error: Failed to open the file..." << endl;
        return; // Exit 
    }

    // Go line by line and create territories
    string line;
    while (getline(inputFile, line)) {
        if (line.find("[Continents]") == 0) {
            int continentId = 0;
            // while we havent not reached a space (to the next section)
            while(getline(inputFile, line) && line.length() != 0) {
                // create a vector of words that were split by a equals
                vector<string> words = MapLoader::split(line, "=");
                // the line should contain the name and number of territories that belong to the continent
                if(words.size() != 2) {
                    cout << "...Error: Invalid continent information..." << endl;
                    return;
                }
                string continentName = words[0];
                // create a new contintent with an auto incrementing id
                Continent *continent = new Continent(continentName, ++continentId);
                // keep track of the list of continents we created thus far
                continents.push_back(continent);
            }
            
        // return 0 of the first matching char
        } else if (line.find("[Territories]") == 0){
            int territoryId = 0;
            // while we havent not reached a space (to the next section)
            while(getline(inputFile, line) && !inputFile.eof()) {
                // if there is a space between the territories, skip that line and go to the next one
                if(line.length() == 0) {
                    continue;
                }
                // create a vector of words that were split by a comma
                vector<string> words = MapLoader::split(line, ",");
                // there is a minimum requirement of name, x-coord, y-coord, and continent
                if(words.size() < 4) {
                    cout << "...Error: Invalid territory information..." << endl;
                    return;
                }

                string territoryName = words[0];
                string continentName = words[3];
                // get the continents Id by the name
                int continentId;
                for(int i = 0; i < continents.size() ; i++){
                    if(continents.at(i)->getName() == continentName){
                        continentId = continents.at(i)->getId();
                    }
                }
                Territory *t = new Territory(territoryName, ++territoryId, continentId);
                // anything past index 3 is what is connected to our territory
                for(int i = 4; i < words.size(); i++) {
                    cout << words[i];
                }
                cout << endl;
            }
        }
    }

    // Close the file
    inputFile.close();
    cout << "...Successfully loaded the Map..." << endl;

    //with the territories create the adjacency list
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