#include "Map.h"

using namespace std;
//namespace fs = filesystem;

class Map {
private:
    map<string, vector<string>> adjacencyList;

public:
    // add 'bidirectional' edge between two vertices
    void addEdge(const string vertex1, const string vertex2) {
        adjacencyList[vertex1].push_back(vertex2);
        adjacencyList[vertex2].push_back(vertex1);
    }

    // print adjacency list
    void printMap() {
        for (const auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            for (const string& neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // delete dynamically allocated strings
    void cleanup() {
        adjacencyList.clear();
    }

    // destructor
    ~Map() {
        cleanup();
    }

    void readMap(string map_name) {
        ifstream mapFile("../maps/" + map_name);
    
        vector<string*> continents;
        vector<string*> territories;

        string line;
        bool readContinents, readTerritories;

        while (!mapFile.eof()) {
            getline(mapFile, line);
            if (line == "[Continents]\r") {
                readContinents = true;
                getline(mapFile, line);
            }
            if (line == "[Territories]\r") {
                readTerritories = true;
                readContinents = false;
                getline(mapFile, line);
            }
            if (readContinents && line != "\r")
                continents.push_back(new string(line));
            if (readTerritories && line != "\r")
                territories.push_back(new string(line));
    }

        mapFile.close();

        /*// print to console
        cout << "Continents ->\n";
        for (auto file_line : continents) {
            cout << *file_line << endl;
        }
        cout << "\nTerritories ->\n";
        for (auto file_line : territories) {
            cout << *file_line << endl;
        }*/

        string input = "Mozambique,482,496,Southern Africa,Tanzania,Malawi,Madagascar,Zambia,Zimbabwe,South Africa";

        vector<string*> result;
        stringstream ss(input);
        string word;

        // split line into words
        while (getline(ss, word, ',')) {
            result.push_back(new string(word));
        }

        // remove coordinates values from vector
        result.erase(next(result.begin(), 1), next(result.begin(), 3));

        // print to console
        for (const string* s : result) {
            cout << *s << endl;
        }

        // file reader memory clean up
        for (auto file_line : continents) {
            delete file_line;
            file_line = NULL;
        }
        for (auto file_line : territories) {
            delete file_line;
            file_line = NULL;
        }
        // Clean up memory by deleting the dynamically allocated strings
        for (string* s : result) {
            delete s;
        }
        result.clear(); // Clear the vector
    }

};

/*class Territory {
public:
    string name;
    string continent;
    vector<string*> adjacency_list;

    // Constructor
    Territory() {}

    // Destructor to clean up dynamically allocated memory
    ~Territory() {
        for (string* adj : adjacency_list) {
            delete adj;
        }
    }
};*/

class Continents {
public:
    string name;
    int value;

    // constructor
    Continents(const string& continentName, int continentValue)
        : name(continentName), value(continentValue) {}

    // destructor
    ~Continents() {}
};

int MapDriver() {
    // display directory contents
    /*string path = "../maps";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path().filename() << endl;
    }

    cout << "\nChoose a file to open:" << endl;*/
    
    Map m;
    m.readMap("Africa.map");

    // Add vertices and edges to create a connected graph
    m.addEdge("A", "B");
    m.addEdge("A", "C");
    m.addEdge("B", "D");
    m.addEdge("C", "E");
    m.addEdge("D", "E");

    // Print Map's adjacency list
    m.printMap();

    // dynamically allocated strings memory clean up
    m.cleanup();

	return 0;
}