#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Territory {
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
};

int main() {
    string input = "Mozambique,482,496,Southern Africa,Tanzania,Malawi,Madagascar,Zambia,Zimbabwe,South Africa";

    vector<Territory*> territories; // Vector of pointers to Territory objects
    stringstream ss(input);
    string item;

    while (getline(ss, item, ',')) {
        Territory* territory = new Territory;

        territory->name = item;
        ss.ignore(); // Ignore the x_coord
        ss.ignore(); // Ignore the comma
        ss.ignore(); // Ignore the y_coord
        ss.ignore(); // Ignore the comma

        getline(ss, territory->continent, ',');

        // Store the remaining items as the adjacency list
        while (getline(ss, item, ',')) {
            territory->adjacency_list.push_back(new string(item));
        }

        territories.push_back(territory);
    }

    // Print the extracted information from the Territory objects
    for (const Territory* territory : territories) {
        cout << "Name: " << territory->name << endl;
        cout << "Continent: " << territory->continent << endl;
        cout << "Adjacency List: ";
        for (const string* adj : territory->adjacency_list) {
            cout << *adj << ", ";
        }
        cout << endl << endl;
    }

    // clean up dynamically allocated memory in territories vector
    for (Territory* territory : territories) {
        delete territory;
    }

    return 0;
}
