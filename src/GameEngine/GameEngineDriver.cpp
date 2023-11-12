#include "GameEngine.h"

void testGameStates() {
    cout << "\n************************************\nTesting Game Driver!!! \n************************************\n\n";
    GameEngine engine;
    string command;

    while (true) {
        cout << "\nEnter a command: ";
        getline(cin, command);

        if (command == "quit") {
            break;
        }
        engine.executeCommand(command);
    }
};

