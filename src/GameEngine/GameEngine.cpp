#include "GameEngine.h"

/**
 * Default Constructor
 */
GameEngine::GameEngine() : currentState(nullptr) {

    auto *s1 = new StartState();
    auto *s2 = new MaploadedState();
    auto *s3 = new MapvalidatedState();
    auto *s4 = new PlayersaddedState();
    auto *s5 = new AssignreinforcementState();
    auto *s6 = new IssueordersState();
    auto *s7 = new ExecuteordersState();
    auto *s8 = new WinState();
    auto *s9 = new EndState();

    auto *t1 = new Transition(s1, "loadmap", s2);
    auto *t2 = new Transition(s2, "loadmap", s2);
    auto *t3 = new Transition(s2, "validatemap", s3);
    auto *t4 = new Transition(s3, "addplayer", s4);
    auto *t5 = new Transition(s4, "addplayer", s4);
    auto *t6 = new Transition(s4, "gamestart", s5);
    auto *t7 = new Transition(s5, "issueorder", s6);
    auto *t8 = new Transition(s6, "issueorder", s6);
    auto *t9 = new Transition(s6, "endissueorders", s7);
    auto *t10 = new Transition(s7, "execorder", s7);
    auto *t11 = new Transition(s7, "win", s8);
    auto *t12 = new Transition(s7, "endexecorders", s5);
    auto *t13 = new Transition(s8, "replay", s1);
    auto *t14 = new Transition(s8, "quit", s9);

    addTransition(t1);
    addTransition(t2);
    addTransition(t3);
    addTransition(t4);
    addTransition(t5);
    addTransition(t6);
    addTransition(t7);
    addTransition(t8);
    addTransition(t9);
    addTransition(t10);
    addTransition(t11);
    addTransition(t12);
    addTransition(t13);
    addTransition(t14);

    // Initialize with the starting state
    setState(s1);

    playerNum = int(0);
    playerOrder;
    deck = new Deck();
    //map = new Map();
    //firstRound = true;
}

/**
 * This function initializes game transitions
*/
void GameEngine::addTransition(Transition *transition) {
    transitions.push_back(transition);
}

vector<Transition *> GameEngine::getTransitions() {
    return transitions;
}

/**
 * This functions informs the user what state they are in and the valid commands
*/
void GameEngine::displayAvailableCommands() {
    if (currentState) {
        cout << "\nThe valid Command in this state is: ";
        for (int i = 0; i < transitions.size(); i++) {
            if (currentState == transitions[i]->getCurrentState()) {
                cout << i + 1 << ")" << transitions[i]->getCommand() << "  ";
            }
        }
    }
}

/**
 * This function executes a valid command
*/
void GameEngine::executeCommand(const string &command) {
    if (currentState) {
        currentState->processCommand(*this, command);
    }
}

/**
 * This method sets the gameEngine'state or the current state to the new state
 * since gameEngine object controls the game flow
*/
void GameEngine::setState(State *newState) {
    if (currentState) {
        currentState->onExit(*this);
    }
    currentState = newState;
    if (currentState) {
        currentState->onEnter(*this);
    }
}

/**
 * This function checks if the current is executeorders -- to be used in Orders class
*/
bool GameEngine::isCurrentStateExecuteordersState() {
    return dynamic_cast<ExecuteordersState *>(currentState) != nullptr;
}

/************************************************************ State **************************************************************/
Map *GameEngine::gameMap() {
    return currentGameMap;
}

void GameEngine::setGameMap(Map* map) {
    currentGameMap = map;
}

/************************************************************ State **************************************************/
/**
 * Default Constructor
 */
State::State() = default;

/**
 * Destructor
 */
State::~State() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void State::onEnter(GameEngine &engine) {
    cout << "Entered a State\n";
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void State::onExit(GameEngine &engine) {
    cout << "Exited a State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void State::processCommand(GameEngine &engine, const string &command) {
    cout << "Command processed\n";
}

/************************************************************ StartState *********************************************/
/**
 * Default Constructor
 */
StartState::StartState() = default;

/**
 * Destructor
 */
StartState::~StartState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void StartState::onEnter(GameEngine &engine) {
    cout << "Entered Start State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void StartState::onExit(GameEngine &engine) {
    cout << "Exited Start State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void StartState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();

    // Find the position of the first space in the command
    size_t spacePos = command.find(' ');
    // Check if a space was found
    if (spacePos != string::npos) {
        // Extract the command and filename using substr
        string cmd = command.substr(0, spacePos);
        string filename = command.substr(spacePos + 1);

        if (cmd == "loadmap") {
            Map* gameMap = gameLoadMap("src/Map/MapFolder/" + filename);
            engine.setGameMap(gameMap); // Set the loaded map in the engine
            engine.setState(t[1]->getNextState());
        } else {
            cout << "Invalid command in Start State\n";
            engine.displayAvailableCommands();
        }
    } else {
        cout << "Invalid command format. Use 'loadmap filename'\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ MaploadedState *****************************************/
/**
 * Default Constructor
 */
MaploadedState::MaploadedState() = default;

/**
 * Destructor
 */
MaploadedState::~MaploadedState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void MaploadedState::onEnter(GameEngine &engine) {
    cout << "Entered Maploaded State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void MaploadedState::onExit(GameEngine &engine) {
    cout << "Exited Maploaded State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void MaploadedState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();

    //cout << "command: " << command << endl;
    // Find the position of the first space in the command
    size_t spacePos = command.find(' ');
    // Check if a space was found
    if (spacePos != string::npos) {
        // Extract the command and filename using substr
        string cmd = command.substr(0, spacePos);
        string filename = command.substr(spacePos + 1);
        if (cmd == "loadmap") {
            Map* gameMap = gameLoadMap("src/Map/MapFolder/" + filename);
            engine.setGameMap(gameMap); // Set the loaded map in the engine
            engine.setState(t[1]->getNextState());
        } else {
            cout << "Invalid command in Maploaded State\n";
            engine.displayAvailableCommands();
        }
    } else if (command == "validatemap") {
        validateMap(*engine.gameMap());
        engine.setState(t[2]->getNextState());
    } else {
        cout << "Invalid command in Maploaded State\n";
        engine.displayAvailableCommands();
    }    
}

/************************************************************ MapvalidatedState **************************************/
/**
 * Default Constructor
 */
MapvalidatedState::MapvalidatedState() = default;

/**
 * Destructor
 */
MapvalidatedState::~MapvalidatedState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void MapvalidatedState::onEnter(GameEngine &engine) {
    cout << "Entered Mapvalidated State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void MapvalidatedState::onExit(GameEngine &engine) {
    cout << "Exited Mapvalidated State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void MapvalidatedState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();
    if (command == "addplayer") {
        engine.setState(t[3]->getNextState());
    } else {
        cout << "Invalid command in Mapvalidated State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ PlayersaddedState **************************************/
/**
 * Default Constructor
 */
PlayersaddedState::PlayersaddedState() = default;

/**
 * Destructor
 */
PlayersaddedState::~PlayersaddedState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void PlayersaddedState::onEnter(GameEngine &engine) {
    cout << "Entered Playersadded State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void PlayersaddedState::onExit(GameEngine &engine) {
    cout << "Exited Playersadded State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void PlayersaddedState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();
    if (command == "addplayer") {
        engine.setState(t[4]->getNextState());
    } else if (command == "gamestart") {
        engine.setState(t[5]->getNextState());
    } else {
        cout << "Invalid command in Playersadded State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ AssignreinforcementState *******************************/
/**
 * Default Constructor
 */
AssignreinforcementState::AssignreinforcementState() = default;

/**
 * Destructor
 */
AssignreinforcementState::~AssignreinforcementState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void AssignreinforcementState::onEnter(GameEngine &engine) {
    cout << "Entered Assignreinforcement State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void AssignreinforcementState::onExit(GameEngine &engine) {
    cout << "Exited Assignreinforcement State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void AssignreinforcementState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();
    if (command == "issueorder") {
        engine.setState(t[6]->getNextState());
    } else {
        cout << "Invalid command in Assignreinforcement State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ IssueordersState ***************************************/
/**
 * Default Constructor
 */
IssueordersState::IssueordersState() = default;

/**
 * Destructor
 */
IssueordersState::~IssueordersState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void IssueordersState::onEnter(GameEngine &engine) {
    cout << "Entered Issueorders State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void IssueordersState::onExit(GameEngine &engine) {
    cout << "Exited Issueorders State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void IssueordersState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();
    if (command == "issueorder") {
        engine.setState(t[7]->getNextState());
    } else if (command == "endissueorders") {
        engine.setState(t[8]->getNextState());
    } else {
        cout << "Invalid command in Issueorders State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ ExecuteordersState *************************************/
/**
 * Default Constructor
 */
ExecuteordersState::ExecuteordersState() = default;

/**
 * Destructor
 */
ExecuteordersState::~ExecuteordersState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void ExecuteordersState::onEnter(GameEngine &engine) {
    cout << "Entered Executeorders State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void ExecuteordersState::onExit(GameEngine &engine) {
    cout << "Exited Executeorders State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void ExecuteordersState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();
    if (command == "execorder") {
        engine.setState(t[9]->getNextState());
    } else if (command == "win") {
        engine.setState(t[10]->getNextState());
    } else if (command == "endexecorders") {
        engine.setState(t[11]->getNextState());
    } else {
        cout << "Invalid command in Executeorders State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ WinState ***********************************************/
/**
 * Default Constructor
 */
WinState::WinState() = default;

/**
 * Destructor
 */
WinState::~WinState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void WinState::onEnter(GameEngine &engine) {
    cout << "Entered Win State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void WinState::onExit(GameEngine &engine) {
    cout << "Exited Win State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void WinState::processCommand(GameEngine &engine, const string &command) {
    vector<Transition *> t = engine.getTransitions();
    if (command == "replay") {
        engine.setState(t[12]->getNextState());
    } else if (command == "quit") {
        engine.setState(t[13]->getNextState());
    } else {
        cout << "Invalid command in Win State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ EndState ***********************************************/
/**
 * Default Constructor
 */
EndState::EndState() = default;

/**
 * Destructor
 */
EndState::~EndState() = default;

/**
 * This functions informs the user what state they are in and the valid commands
*/
void EndState::onEnter(GameEngine &engine) {
    cout << "Entered End State\n";
    engine.displayAvailableCommands();
}

/**
 * This functions informs the user which state they are existing after processing their command
*/
void EndState::onExit(GameEngine &engine) {
    cout << "Exited End State\n";
}

/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
void EndState::processCommand(GameEngine &engine, const string &command) {
    cout << "Invalid command in End State\n";
}

/************************************************************ Transition *********************************************/
/**
 * Destructor
 */
Transition::~Transition() = default;

/**
 * Constructor with with an argument(s)
 */
Transition::Transition(State *fromState, const string &command, State *toState) {
    this->currentState = fromState;
    this->command = command;
    this->nextState = toState;
}

/**
 * Assignment Operator
 */
Transition &Transition::operator=(const Transition &other) = default;

/**
 * Copy Constructor
 */
Transition::Transition(const Transition &other) {
    this->currentState = other.currentState;
    this->command = other.command;
    this->nextState = other.nextState;
}

/**
 * override Stream insertion operator
 */
ostream &operator<<(ostream &out, Transition &t) {
    cout << "Here print whatever as place holder. not sure if i need this stream insertion\n";
    return out;
}

string Transition::getCommand() {
    return command;
}

State *Transition::getCurrentState() {
    return currentState;
}

State *Transition::getNextState() {
    return nextState;
}

/***************************************************** GameEngine **************************************************/
/**
 * Default constructor
 **/

/**
 * Destructor
 **/
GameEngine::~GameEngine() {
    for (auto &player: players) {
        delete player;
    }
    players.clear();
    playerOrder.clear();
}

void GameEngine::start() {
    //start(startupPhase()map);
    //GameEngine();
}

void GameEngine::setPlayers(vector<Player *> p) {
    players = std::move(p);
    //players = p;
}

vector<Player *> GameEngine::getPlayers() {
    return {};
    //return players;
}

int GameEngine::getPlayerNum() const {
    return playerNum;
}

/************************************************* Helper functions **************************************************/
void printPlayerReinforcement(const Player *player) {
    std::cout << "[NEW] Reinforcement Pool of Player " << player->getID() << ": ";
    std::cout << player->getReinforcement() << std::endl;
}

struct InlineLoggable : public ILoggable {
    std::string logMessage;

    explicit InlineLoggable(std::string msg) : logMessage(std::move(msg)) {}

    std::string stringToLog() override {
        return logMessage;
    }
};

InlineLoggable createLogMessage(const std::string &message) {
    return InlineLoggable(message);
}

/***************************************************** MainGameLoop **************************************************/

void GameEngine::reinforcementPhase() {
    // loop through every player
    for (auto &player: players) {
        // set player's game phase status to the current "Reinforcement" phase
        player->setGamePhase("Reinforcement");

        // notify log of phase status change
        InlineLoggable logMessage = createLogMessage(
                "Player " + to_string(player->getID()) + " is now in the [Reinforcement] phase of the game.");
        //player->notify(&logMessage);

        // display current reinforcement pool of player
        cout << "Reinforcement Pool of Player " << player->getID() << ": " << player->getReinforcement() << endl;

        // calculate base reinforcement based on territories owned, with a minimum of 3 (rounded down)
        int baseReinforcement = max(3, static_cast<int>(player->getTerritories().size() / 3));
        player->setReinforcement(player->getReinforcement() + baseReinforcement);

        // if player owns continent, award control bonus value
        vector<int> continentBonuses = player->continentOwnershipComplete();
        for (int bonus: continentBonuses) {
            player->setReinforcement(player->getReinforcement() + bonus);
        }
        printPlayerReinforcement(player);
    }
}

void GameEngine::issueOrdersPhase() {
    // loop through all players in the game
    for (auto &player: players) {
        // player is now in "issue order" phase of the game loop, notify log
        player->setGamePhase("Issuing Orders");

        // log phase status change
        InlineLoggable logMessage("Player: " + to_string(player->getID()) +
                                  " is now in the \"Issuing Orders\" phase of the game.");
        //player->notify(&logMessage);
        // get current player's id and hand to determine what orders they are allowed to issue
        bool continueIssuingOrders = true;
        while (continueIssuingOrders) {
            string userInput;
            cout << "Player " << player->getID() << ", would you like to issue an order? (YES/NO): ";
            cin >> userInput;
            // transform input to lowercase
            transform(userInput.begin(), userInput.end(), userInput.begin(),
                      [](unsigned char c) { return toupper(c); });

            if (userInput == "YES") {
                player->issueOrder();
                // keep asking user to issue orders
            } else if (userInput == "NO") {
                continueIssuingOrders = false; // stop asking
            } else {
                std::cout << "Invalid input! Please enter YES or NO." << endl;
            }
        }
        // display order list of player
        cout << player->orderList << endl;
    }
}

/*void mainGameLoop() {
    GameEngine gameEngine;
    gameEngine.reinforcementPhase();
    gameEngine.issueOrdersPhase();
}*/

void testMainGameLoop() {
    //cout << "Nothing to see here" << endl;
    Player *player[3];
    string gamePhase = "Reinforcement";

    // initialize 3 players
    for (int i = 0; i < 3; ++i) {
        player[i] = new Player(); // create new player
        player[i]->orderList = new OrdersList(); // create player's orders list
        player[i]->setReinforcement(50); // give player 50 army units
        cout << player[i]->getReinforcement() << endl; // output the units
        player[i]->setGamePhase(gamePhase); // set game phase
    }

    string phase = player[1]->getGamePhase();
    cout << phase << endl;

    // issue orders and add them to orders list
    bool continueIssuingOrders = true;
    while (continueIssuingOrders) {
        string userInput;
        cout << "Player " << player[1]->getID() << ", would you like to issue an order? (YES/NO): ";
        cin >> userInput;
        transform(userInput.begin(), userInput.end(), userInput.begin(),
                  [](unsigned char c) { return toupper(c); });
        if (userInput == "YES") {
            player[1]->issueOrder();

        } else if (userInput == "NO") {
            continueIssuingOrders = false;
        } else {
            std::cout << "Invalid input! Please enter YES or NO." << endl;
        }
    }
    // display order list of player
    cout << player[1]->orderList << endl;
}

void testStartupPhase() {
    testMainGameLoop();
//    deleteMap(gameMap);
};