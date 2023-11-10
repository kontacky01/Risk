#include "GameEngine.h"
#include "Player.h"
#include <algorithm>

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
}