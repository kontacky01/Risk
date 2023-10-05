#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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

/*int main() {
    string input = "Northern Africa=4";
    vector<string> parts;

    stringstream ss(input);
    string token;

    while (getline(ss, token, '=')) {
        parts.push_back(token);
    }

    Continents* continent = nullptr;

    if (parts.size() == 2) {
        continent = new Continents(parts[0], stoi(parts[1]));

        cout << "Name: " << continent->name << endl;
        cout << "Value: " << continent->value << endl;
    } else {
        cout << "Invalid input format." << endl;
    }

    // clean up
    delete continent;

    return 0;
}
*/