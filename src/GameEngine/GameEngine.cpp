#include "GameEngine.h"

/**
 * Default Constructor
 */
    GameEngine::GameEngine() : currentState(nullptr) {
        
        StartState* s1 = new StartState();
        MaploadedState* s2 = new MaploadedState();
        MapvalidatedState* s3 = new MapvalidatedState();
        PlayersaddedState* s4 = new PlayersaddedState();
        AssignreinforcementState* s5 = new AssignreinforcementState();
        IssueordersState* s6 = new IssueordersState();
        ExecuteordersState* s7 = new ExecuteordersState();
        WinState* s8 = new WinState();
        EndState* s9 = new EndState();
        
        Transition* t1 = new Transition(s1, "loadmap", s2);
        Transition* t2 = new Transition(s2, "loadmap", s2);
        Transition* t3 = new Transition(s2, "validatemap", s3);
        Transition* t4 = new Transition(s3, "addplayer", s4);
        Transition* t5 = new Transition(s4, "addplayer", s4);
        Transition* t6 = new Transition(s4, "gamestart", s5);
        Transition* t7 = new Transition(s5, "issueorder", s6);
        Transition* t8 = new Transition(s6, "issueorder", s6);
        Transition* t9 = new Transition(s6, "endissueorders", s7);
        Transition* t10 = new Transition(s7, "execorder", s7);
        Transition* t11 = new Transition(s7, "win", s8);
        Transition* t12 = new Transition(s7, "endexecorders", s5);
        Transition* t13 = new Transition(s8, "replay", s1);
        Transition* t14 = new Transition(s8, "quit", s9);

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
    }
/**
 * This function initializes game transitions
*/
    void GameEngine::addTransition(Transition* transition){
        transitions.push_back(transition);
    }
    vector<Transition*> GameEngine::getTransitions(){
        return transitions;
    }
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void GameEngine::displayAvailableCommands(){
        if (currentState) {
            cout << "\nThe valid Command in this state is: ";
            for(int i=0;i<transitions.size();i++){
                if(currentState == transitions[i]->getCurrentState()){
                    cout << i+1 << ")" << transitions[i]->getCommand() << "  ";
                }
            }
        }
    }
/**
 * This function executes a valid command
*/
    void GameEngine::executeCommand(const string& command){
        if (currentState) {
            currentState->processCommand(*this, command);
        }
    }
/**
 * This method sets the gameEngine'state or the current state to the new state
 * since gameEngine object controls the game flow
*/
    void GameEngine::setState(State* newState){
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
    bool GameEngine::isCurrentStateExecuteordersState(){
        return dynamic_cast<ExecuteordersState*>(currentState) != nullptr;
    }

/************************************************************ State **************************************************************/
/**
 * Default Constructor
 */
    State::State(){}
/**
 * Destructor
 */
    State::~State(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void State::onEnter(GameEngine& engine){
        cout << "Entered a State\n";
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void State::onExit(GameEngine& engine){
        cout << "Exited a State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void State::processCommand(GameEngine& engine, const string& command){
        cout << "Command processed\n";
    }

/************************************************************ StartState **************************************************************/
/**
 * Default Constructor
 */
    StartState::StartState(){}
/**
 * Destructor
 */
    StartState::~StartState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void StartState::onEnter(GameEngine& engine){
        cout << "Entered Start State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void StartState::onExit(GameEngine& engine){
        cout << "Exited Start State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void StartState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    MaploadedState::MaploadedState(){}
/**
 * Destructor
 */
    MaploadedState::~MaploadedState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void MaploadedState::onEnter(GameEngine& engine){
        cout << "Entered Maploaded State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void MaploadedState::onExit(GameEngine& engine){
        cout << "Exited Maploaded State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void MaploadedState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    MapvalidatedState::MapvalidatedState(){}
/**
 * Destructor
 */
    MapvalidatedState::~MapvalidatedState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void MapvalidatedState::onEnter(GameEngine& engine){
        cout << "Entered Mapvalidated State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void MapvalidatedState::onExit(GameEngine& engine){
        cout << "Exited Mapvalidated State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void MapvalidatedState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    PlayersaddedState::PlayersaddedState(){}
/**
 * Destructor
 */
    PlayersaddedState::~PlayersaddedState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void PlayersaddedState::onEnter(GameEngine& engine){
        cout << "Entered Playersadded State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void PlayersaddedState::onExit(GameEngine& engine){
        cout << "Exited Playersadded State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void PlayersaddedState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    AssignreinforcementState::AssignreinforcementState(){}
/**
 * Destructor
 */
    AssignreinforcementState::~AssignreinforcementState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void AssignreinforcementState::onEnter(GameEngine& engine){
        cout << "Entered Assignreinforcement State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void AssignreinforcementState::onExit(GameEngine& engine){
        cout << "Exited Assignreinforcement State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void AssignreinforcementState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    IssueordersState::IssueordersState(){}
/**
 * Destructor
 */
    IssueordersState::~IssueordersState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void IssueordersState::onEnter(GameEngine& engine){
        cout << "Entered Issueorders State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void IssueordersState::onExit(GameEngine& engine){
        cout << "Exited Issueorders State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void IssueordersState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    ExecuteordersState::ExecuteordersState(){}
/**
 * Destructor
 */
    ExecuteordersState::~ExecuteordersState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void ExecuteordersState::onEnter(GameEngine& engine){
        cout << "Entered Executeorders State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void ExecuteordersState::onExit(GameEngine& engine){
        cout << "Exited Executeorders State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void ExecuteordersState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    WinState::WinState(){}
/**
 * Destructor
 */
    WinState::~WinState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void WinState::onEnter(GameEngine& engine){
        cout << "Entered Win State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void WinState::onExit(GameEngine& engine){
        cout << "Exited Win State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void WinState::processCommand(GameEngine& engine, const string& command){
        vector<Transition*> t = engine.getTransitions();
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
    EndState::EndState(){}
/**
 * Destructor
 */
    EndState::~EndState(){}
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void EndState::onEnter(GameEngine& engine){
        cout << "Entered End State\n";
        engine.displayAvailableCommands();
    }
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void EndState::onExit(GameEngine& engine){
        cout << "Exited End State\n";
    }
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void EndState::processCommand(GameEngine& engine, const string& command){
        cout << "Invalid command in End State\n";
    }

/************************************************************ Transition **************************************************************/
/**
 * Destructor
 */
    Transition::~Transition(){}
/**
 * Constructor with with an argument(s)
 */
	Transition::Transition(State*  fromState, const string& command, State*  toState){
        this->currentState = fromState;
        this->command = command;
        this->nextState = toState;
    }
/**
 * Assignment Operator
 */
	Transition& Transition::operator=(const Transition& other){
        this->currentState = other.currentState;
        this->command = other.command;
        this->nextState = other.nextState;
        return *this;
    }
/**
 * Copy Constructor
 */
    Transition::Transition(const Transition& other){
        this->currentState = other.currentState;
        this->command = other.command;
        this->nextState = other.nextState;
    }
/**
 * overide Stream insertion operator
 */
    ostream& operator<<(ostream& out, Transition& t){
        cout << "Here print whatever as place holder. not sure if i need this stream insertion\n";
        return out;
    }

    string Transition::getCommand(){
        return command;
    }

    State * Transition::getCurrentState(){
        return currentState;
    }
    
    State * Transition::getNextState(){
        return nextState;
    }