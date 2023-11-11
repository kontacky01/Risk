#include "GameEngine.h"

void testGameStates() {
    cout << "\n************************************\nTesting Game Driver!!! \n************************************\n\n";
    GameEngine engine;
    string command;

    while (true) {
        cout << "\nEnter a command: ";
        cin >> command;

        if (command == "quit") {
            break;
        }

        engine.executeCommand(command);
    }
};

void testStartupPhase() {
    vector<string> mapFiles;
    string directoryPath = "src/Map/MapFolder";  // Update this to your directory path

    // Check if the directory exists
    ifstream dirCheck(directoryPath.c_str());
    if (!dirCheck.good()) {
        cerr << "Directory not found: " << directoryPath << endl;
        return;
    }
    dirCheck.close();

    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".map") {
            mapFiles.push_back(entry.path().filename());
        }
    }

    // Sort the vector of map files
    sort(mapFiles.begin(), mapFiles.end());

    // Print the ordered list
    for (size_t i = 0; i < mapFiles.size(); ++i) {
        cout << i << " - " << mapFiles[i] << endl;
    }
};