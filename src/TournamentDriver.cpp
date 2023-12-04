#include "CommandProcessing/CommandProcessing.h"
#include "GameEngine/GameEngine.h"
#include "Map/Map.h"
//#include "Player/Player.h"
//#include "OrdersList/Orders.h"
//#include "CardsDeck/Cards.h"
//#include "LoggingObserver/LoggingObserver.h"
//#include "PlayerStrategies/PlayerStrategies.h"

void testTournament() {
    cout << "\n************************************\nTesting Tournament Driver! \n************************************\n\n";
    GameEngine engine;
    string args;

    while (true) {
        cout << "\nEnter a command: ";
        getline(cin, args);

        if (args == "quit") {
            break;
        }     // Parse tournament command and validate parameters
        if (args.find("tournament") == 0) {
            args = args.substr(10);
            std::string maps;
            std::string playerStrategies;
            int numGames = 0;
            int maxTurns = 0;

            std::istringstream iss(args);
            std::string token;
            while (iss >> token) {
                if (token == "-M") {
                    iss >> maps;
                } else if (token == "-P") {
                    iss >> playerStrategies;
                } else if (token == "-G") {
                    iss >> numGames;
                } else if (token == "-D") {
                    iss >> maxTurns;
                }
            }

            if (maps.empty() || playerStrategies.empty() || numGames <= 0 || maxTurns <= 0) {
                std::cout << "Invalid tournament command. Please provide valid parameters.\n";
                continue;
            }

            // Execute the tournament
            runTournament(maps, playerStrategies, numGames, maxTurns);
        }
        }
        engine.executeCommand(args);
    }
