#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph {
private:
    map<string, vector<string>> adjacencyList;

public:
    // add bidirectional edge between two vertices
    void addEdge(const string& vertex1, const string& vertex2) {
        string* v1 = new string(vertex1);
        string* v2 = new string(vertex2);
        adjacencyList[*v1].push_back(*v2);
        adjacencyList[*v2].push_back(*v1);
    }

    // print the graph
    void printGraph() {
        for (const auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            for (const string& neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // cleanup method to delete dynamically allocated strings
    void cleanup() {
        adjacencyList.clear();
    }

    // destructor to ensure cleanup
    ~Graph() {
        cleanup();
    }
};

int main() {
    Graph g;

    // add vertices and edges to create a connected graph
    g.addEdge("Aa", "Bc");
    g.addEdge("Aa", "Ce");
    g.addEdge("Bc", "Dd");
    g.addEdge("Ce", "Ef");
    g.addEdge("Dd", "Ef");
    g.addEdge("Ef", "Aa");

    // print the graph's adjacency list
    g.printGraph();

    // clean up dynamically allocated strings
    g.cleanup();

    return 0;
}