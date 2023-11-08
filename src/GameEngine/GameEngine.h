#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

/********************************************************** Game Engine ***********************************************************/
class State;// Forward declaration
class Transition;// Forward declaration
class GameEngine{
public:
/**
 * Default Constructor
 */
    GameEngine();
/**
 * This function initializes game transitions
*/
    void addTransition(Transition* transition);
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void displayAvailableCommands();
/**
 * This function executes a valid command
*/
    void executeCommand(const string& command);
/**
 * This method sets the gameEngine'state or the current state to the new state
 * since gameEngine object controls the game flow
*/
    void setState(State* newState);

    vector<Transition*> getTransitions();

private:
    State* currentState;
    vector<Transition*> transitions;
};
/************************************************************ State **************************************************************/
class State {
public:
/**
 * Default Constructor
 */
    State();
/**
 * Destructor
 */
    virtual ~State();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    virtual void onEnter(GameEngine& engine) = 0;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    virtual void onExit(GameEngine& engine) = 0;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    virtual void processCommand(GameEngine& engine, const string& command) = 0;
};
/************************************************************ StartupState **************************************************************/
class StartState : public State{
public:
/**
 * Default Constructor
 */
    StartState();
/**
 * Destructor
 */
    ~StartState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ MaploadedState **************************************************************/
class MaploadedState : public State{
public:
/**
 * Default Constructor
 */
    MaploadedState();
/**
 * Destructor
 */
    ~MaploadedState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ MapvalidatedState **************************************************************/
class MapvalidatedState : public State{
public:
/**
 * Default Constructor
 */
    MapvalidatedState();
/**
 * Destructor
 */
    ~MapvalidatedState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ PlayersaddedState **************************************************************/
class PlayersaddedState : public State{
public:
/**
 * Default Constructor
 */
    PlayersaddedState();
/**
 * Destructor
 */
    ~PlayersaddedState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ AssignreinforcementState **************************************************************/
class AssignreinforcementState : public State{
public:
/**
 * Default Constructor
 */
    AssignreinforcementState();
/**
 * Destructor
 */
    ~AssignreinforcementState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ IssueordersState **************************************************************/
class IssueordersState : public State{
public:
/**
 * Default Constructor
 */
    IssueordersState();
/**
 * Destructor
 */
    ~IssueordersState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ ExecuteordersState **************************************************************/
class ExecuteordersState : public State{
public:
/**
 * Default Constructor
 */
    ExecuteordersState();
/**
 * Destructor
 */
    ~ExecuteordersState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ WinState **************************************************************/
class WinState : public State{
public:
/**
 * Default Constructor
 */
    WinState();
/**
 * Destructor
 */
    ~WinState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ EndState **************************************************************/
class EndState : public State{
public:
/**
 * Default Constructor
 */
    EndState();
/**
 * Destructor
 */
    ~EndState();
/**
 * This functions informs the user what state they are in and the valid commands
*/
    void onEnter(GameEngine& engine) override;
/**
 * This functions informs the user which state they are existing after processing their command
*/
    void onExit(GameEngine& engine) override;
/**
 * This functions processes the user's command if it is valid and updates the state of the game
*/
    void processCommand(GameEngine& engine, const string& command) override;
};
/************************************************************ Transition **************************************************************/
class Transition{
public:
/**
 * Destructor
 */
    ~Transition();
/**
 * Constructor with with an argument(s)
 */
	Transition(State*  fromState, const string& command, State*  toState);
/**
 * Assignment Operator
 */
	Transition& operator=(const Transition& other);
/**
 * Copy Constructor
 */
    Transition(const Transition& other);
/**
 * overide Stream insertion operator
 */
    friend ostream& operator<<(ostream& out, Transition& t);

    string getCommand();

    State * getCurrentState();
    
    State * getNextState();

private:
    State* currentState;
    string command;
    State* nextState;
};
/************************************************************ GameEngineDriver **************************************************************/
void testGameStates();