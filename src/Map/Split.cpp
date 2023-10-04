#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int main() {
    string str = "Northern Africa=4";
    vector<string> v = split (str, '=');

    for (auto i : v) cout << i << endl;

    return 0;
}