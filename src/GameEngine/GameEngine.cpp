#include "LoggingObserver.h"
#include "GameEngine.h"

#include <utility>
#include <memory>
#include <algorithm>


/**
 * Default Constructor
 */
GameEngine::GameEngine() : currentState(nullptr) {

    StartState *s1 = new StartState();
    MaploadedState *s2 = new MaploadedState();
    MapvalidatedState *s3 = new MapvalidatedState();
    PlayersaddedState *s4 = new PlayersaddedState();
    AssignreinforcementState *s5 = new AssignreinforcementState();
    IssueordersState *s6 = new IssueordersState();
    ExecuteordersState *s7 = new ExecuteordersState();
    WinState *s8 = new WinState();
    EndState *s9 = new EndState();

    Transition *t1 = new Transition(s1, "loadmap", s2);
    Transition *t2 = new Transition(s2, "loadmap", s2);
    Transition *t3 = new Transition(s2, "validatemap", s3);
    Transition *t4 = new Transition(s3, "addplayer", s4);
    Transition *t5 = new Transition(s4, "addplayer", s4);
    Transition *t6 = new Transition(s4, "gamestart", s5);
    Transition *t7 = new Transition(s5, "issueorder", s6);
    Transition *t8 = new Transition(s6, "issueorder", s6);
    Transition *t9 = new Transition(s6, "endissueorders", s7);
    Transition *t10 = new Transition(s7, "execorder", s7);
    Transition *t11 = new Transition(s7, "win", s8);
    Transition *t12 = new Transition(s7, "endexecorders", s5);
    Transition *t13 = new Transition(s8, "replay", s1);
    Transition *t14 = new Transition(s8, "quit", s9);

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
    currentGameMap = new Map();
    //currentGameMap = nullptr;
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
    if (currentState && !isCurrentStateEndState()) {
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
    notify(this);
    if (currentState) {
        currentState->onEnter(*this);
    }
}

/**
 * This function checks if the currentState is startstate
*/
bool GameEngine::isCurrentStateStartState() {
    return dynamic_cast<StartState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is maploadedstate
*/
bool GameEngine::isCurrentStateMaploadedState() {
    return dynamic_cast<MaploadedState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is mapvalidatedstate
*/
bool GameEngine::isCurrentStateMapvalidatedState() {
    return dynamic_cast<MapvalidatedState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is playersaddedstate
*/
bool GameEngine::isCurrentStatePlayersaddedState() {
    return dynamic_cast<PlayersaddedState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is assignreinforcementstate
*/
bool GameEngine::isCurrentStateAssignreinforcementState() {
    return dynamic_cast<AssignreinforcementState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is issueordersstate
*/
bool GameEngine::isCurrentStateIssueordersState() {
    return dynamic_cast<IssueordersState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is executeorders
*/
bool GameEngine::isCurrentStateExecuteordersState() {
    return dynamic_cast<ExecuteordersState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is winstate
*/
bool GameEngine::isCurrentStateWinState() {
    return dynamic_cast<WinState *>(currentState) != nullptr;
}

/**
 * This function checks if the currentState is endstate
*/
bool GameEngine::isCurrentStateEndState() {
    return dynamic_cast<EndState *>(currentState) != nullptr;
}

/**
 * Override the string to log
*/
string GameEngine::stringToLog() {
    string log;
    for (int i = 0; i < transitions.size(); i++) {
        if (currentState == transitions[i]->getNextState()) {
            log = transitions[i]->getCommand();
        }
    }
    return "\n\n----------------------------------------- Logger -----------------------------------------\n\nThe new state of the game is " +
           log +
           " state\n\n------------------------------------------------------------------------------------------\n\n";
}

/************************************************************ State **************************************************************/

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
StartState::~StartState() {}

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
    if (command == "loadmap") {
        engine.setState(t[1]->getNextState());
    } else {
        cout << "Invalid command in Start State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ MaploadedState **************************************************************/
/**
 * Default Constructor
 */
MaploadedState::MaploadedState() {}

/**
 * Destructor
 */
MaploadedState::~MaploadedState() {}

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
    if (command == "loadmap") {
        engine.setState(t[1]->getNextState());
    } else if (command == "validatemap") {
        engine.setState(t[2]->getNextState());
    } else {
        cout << "Invalid command in Maploaded State\n";
        engine.displayAvailableCommands();
    }
}

/************************************************************ MapvalidatedState **************************************************************/
/**
 * Default Constructor
 */
MapvalidatedState::MapvalidatedState() {}

/**
 * Destructor
 */
MapvalidatedState::~MapvalidatedState() {}

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

/************************************************************ PlayersaddedState **************************************************************/
/**
 * Default Constructor
 */
PlayersaddedState::PlayersaddedState() {}

/**
 * Destructor
 */
PlayersaddedState::~PlayersaddedState() {}

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

/************************************************************ AssignreinforcementState **************************************************************/
/**
 * Default Constructor
 */
AssignreinforcementState::AssignreinforcementState() {}

/**
 * Destructor
 */
AssignreinforcementState::~AssignreinforcementState() {}

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

/************************************************************ IssueordersState **************************************************************/
/**
 * Default Constructor
 */
IssueordersState::IssueordersState() {}

/**
 * Destructor
 */
IssueordersState::~IssueordersState() {}

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

/************************************************************ ExecuteordersState **************************************************************/
/**
 * Default Constructor
 */
ExecuteordersState::ExecuteordersState() {}

/**
 * Destructor
 */
ExecuteordersState::~ExecuteordersState() {}

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

/************************************************************ WinState **************************************************************/
/**
 * Default Constructor
 */
WinState::WinState() {}

/**
 * Destructor
 */
WinState::~WinState() {}

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

/************************************************************ EndState **************************************************************/
/**
 * Default Constructor
 */
EndState::EndState() {}

/**
 * Destructor
 */
EndState::~EndState() {}

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

/************************************************************ Transition **************************************************************/
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
Transition &Transition::operator=(const Transition &other) {
    this->currentState = other.currentState;
    this->command = other.command;
    this->nextState = other.nextState;
    return *this;
}

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

Map *GameEngine::gameMap() {
    return currentGameMap;
}

void GameEngine::setGameMap(Map *map) {
    currentGameMap = map;
}

void GameEngine::setPlayers(vector<Player *> p) {
    players = std::move(p);
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
    cout << "[NEW] Reinforcement Pool of Player " << player->getID() << ": ";
    cout << player->getReinforcement() << std::endl;
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

bool GameEngine::isGameOver() const {
    for (auto &player: players) {
        if (player->getTerritories().size() == currentGameMap->territoryList.size()) {
            // This player owns all territories, game over
            return true;
        }
    }
    return false;
}

/***************************************************** MainGameLoop **************************************************/
void GameEngine::mainGameLoop() {
    Map *map = currentGameMap;

        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();

        removePlayersWithoutTerritories();
    }


void GameEngine::cleanupResources() {
    for (Player *player: players) {
        delete player;
    }
    players.clear();

}

void GameEngine::reinforcementPhase() {
    cout << "\n\nEntering Reinforcement Phase" << endl;
    for (auto &player: players) {
        // set player's game phase status to the current "Reinforcement" phase
        player->setGamePhase("Reinforcement");

        // notify log of phase status change
        InlineLoggable logMessage = createLogMessage(
                "\nPlayer " + to_string(player->getID()) + " is now in the [Reinforcement] phase of the game.");
        player->notify(&logMessage);

        // display current reinforcement pool of player
        cout << "\nReinforcement Pool of Player " << player->getID() << ": " << player->getReinforcement() << endl;

        // calculate base reinforcement based on territories owned, with a minimum of 3 (rounded down)
        int baseReinforcement = std::max(3, static_cast<int>(player->getTerritories().size()) / 3);
        player->setReinforcement(player->getReinforcement() + baseReinforcement);

        // if player owns continent, award control bonus value
        vector<int> continentBonuses = player->continentOwnershipComplete();
        for (int bonus: continentBonuses) {
            player->setReinforcement(player->getReinforcement() + bonus);
        }
        printPlayerReinforcement(player);
        issueOrdersPhase();
    }
}

void GameEngine::issueOrdersPhase() {
    // loop through all players in the game
    for (auto &player: players) {
        // player is now in "issue order" phase of the game loop, notify log
        player->setGamePhase("Issuing Orders");

        // log phase status change
        InlineLoggable logMessage("\nPlayer: " + to_string(player->getID()) +
                                  " is now in the [Issuing Orders] phase of the game.");
        player->notify(&logMessage);

        // get current player's id and hand to determine what orders they are allowed to issue
        bool continueIssuingOrders = true;
        while (continueIssuingOrders) {
            string userInput;
            cout << "\nPlayer " << player->getID() << ", would you like to issue an order? (YES/NO): ";
            cin >> userInput;
            cout << "\n";
            // transform input to lowercase
            transform(userInput.begin(), userInput.end(), userInput.begin(),
                      [](unsigned char c) { return toupper(c); });

            if (userInput == "YES") {
                player->issueOrder();
                // keep asking user to issue orders
            } else if (userInput == "NO") {
                continueIssuingOrders = false; // stop asking
            } else {
                std::cout << "\nInvalid input! Please enter YES or NO." << endl;
            }
        }
        // display order list of player
        cout << player->orderList << endl;
    }
}

Player *GameEngine::checkForWinner() {
    Player *winner = nullptr;

    for (auto &player: players) {
        // Check if the player owns all territories
        if (player->getTerritories().size() == gameMap()->territoryList.size()) {
            winner = player;
            break; // Exit loop, we found a winner
        }
    }
    return winner;
    exit(0);
}

bool GameEngine::removePlayersWithoutTerritories() {
    bool playerRemoved = false;
    auto it = players.begin();
    while (it != players.end()) {
        if ((*it)->getTerritories().empty()) {
            // Player has no territories, remove them
            cout << "Player " << (*it)->getID() << " has been removed from the game." << endl;
            it = players.erase(it);
        } else {
            ++it; // Move to the next player
        }
    }
    return playerRemoved;
}

// helper function to execute orders for a player
void executeAssistForPlayer(Player *player, const string &orderName, const string &phase) {
    // check if player's order list is empty
    if (player->getOrdersList()->getSize() == 0) {
        return;
    }

    // setting the player's phase and notifying the log
    player->setGamePhase(phase);
    InlineLoggable logMessage("\nPlayer: " + to_string(player->getID()) +
                              " is now in the [" + phase + "] phase of the game.");
    player->notify(&logMessage);

    // getting the player's current order list
    OrdersList *currentPlayerOrdersList = player->getOrdersList();

    // retrieve the vector of orders
    vector<Order *> *ordersVector = currentPlayerOrdersList->getOL();

    // check if the ordersVector is not empty
    if (ordersVector != nullptr && !ordersVector->empty()) {
        for (int j = 0; j < ordersVector->size(); j++) {
            // retrieve the current order from the vector
            Order *currentOrder = (*ordersVector)[j];

            // check if the order matches the specified order name
            if (currentOrder != nullptr && currentOrder->getOrderName() == orderName) {
                // execute the order
                currentOrder->execute();
            }
        }
    }
}

void testStartupPhase() {
    //testMainGameLoop();
//    deleteMap(gameMap);
};

void GameEngine::executeOrdersPhase() {
    while (true) {
        // loop through each player
        for (auto currentPlayer: players) {
            // get a reference to the current player.
            // store the size of the player's territory list before executing deploy orders.
            int territoriesBefore = currentPlayer->getTerritories().size();

            // execute all "deploy" orders for the current player.
            executeAssistForPlayer(currentPlayer, "deploy", "~~~~~~ Executing [deploy] Orders");

            // store the size of the player's territory list after executing deploy orders.
            int territoriesAfter = currentPlayer->getTerritories().size();

            // check if the player has gained new territories (territory list size increased).
            if (territoriesAfter > territoriesBefore) {
                // if new territories were gained, draw a card from the deck for the player.
                Card *drawnCard = deck->draw();
                currentPlayer->getHand()->addCard(drawnCard);
            }

            // check if the player owns all territories on any continent
            for (auto &continent: gameMap()->continentList) {
                bool ownsAllTerritories = true;
                for (auto &territory: continent->territoriesInContinents) {
                    if (territory->getOwnerId() != currentPlayer->getID()) {
                        ownsAllTerritories = false;
                        break;
                    }
                }
                if (ownsAllTerritories) {
                    // award control bonus for owning all territories in the continent
                    int controlBonus = continent->getControlBonusValue();
                    currentPlayer->setReinforcement(controlBonus);
                }
            }
            // executes
            executeAssistForPlayer(currentPlayer, "advance", "~~~~~~ Executing [advance] Orders");
            executeAssistForPlayer(currentPlayer, "airlift", "~~~~~~ Executing [airlift] Orders");
            executeAssistForPlayer(currentPlayer, "blockade", "~~~~~~ Executing [blockade] Orders");
            executeAssistForPlayer(currentPlayer, "bomb", "~~~~~~ Executing [bomb] Orders");
            executeAssistForPlayer(currentPlayer, "negotiate", "~~~~~~ Executing [negotiate] Orders");
        }

        // Check for game end condition
        Player *winner = checkForWinner();
        if (winner != nullptr) {
            cout << "Player " << winner->getID() << " wins!" << endl;
            exit(0);
        }

        // Remove players without territories
        removePlayersWithoutTerritories();
        reinforcementPhase();
    }
}

void GameEngine::addPlayer(Player *player) {
    players.push_back(player);
}

Deck *GameEngine::getDeck() {
    return deck;
}