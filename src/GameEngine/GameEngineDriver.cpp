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
    Map* gameMap = nullptr;
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

    // Sort the vector of map files and print the ordered list
    sort(mapFiles.begin(), mapFiles.end());
    for (size_t i = 0; i < mapFiles.size(); ++i) {
        cout << mapFiles[i] << endl;
    }

    while(true) {
        cout << "\nChoose a map file to open. Alternatively, enter \"quit\" to exit.\n";
        string userInput;
        cin >> userInput;
        
        if (userInput == "quit") {
            return;
        }
        
    // Validate the user input matching any map file
        auto it = find(mapFiles.begin(), mapFiles.end(), userInput);
        if (it != mapFiles.end()) {
            gameMap = gameLoadMap(directoryPath + "/" + *it);
            validateMap(*gameMap);
            break;
        } else {
            cout << "\nInvalid map file. Please choose a valid one." << endl;
        }
    }
    testMainGameLoop();
    deleteMap(gameMap);
};