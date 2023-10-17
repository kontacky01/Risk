#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

/************************************************************ State **************************************************************/
class State{
public:
/**
 * Default Constructor
 */
    State();
/**
 * Destructor
 */
    ~State();
/**
 * Constructor with an argument(s)
 */
    State(string name);
/**
 * Assignment Operator
 */
    State& operator=(const State& other);
/**
 * Copy Constructor
 */
    State(const State& other);
/**
 * overide Stream insertion operator
 */
    friend ostream& operator<<(ostream& out, State* s);
/**
 * This method returns a state's name
 */   
    string getStateName();

private:
    string stateName;
};

/************************************************************ Transition **************************************************************/
class Transition{
public:
/**
 * Default Constructor
 */
	Transition();
/**S
 * Destructor
 */
    ~Transition();
/**
 * Constructor with with an argument(s)
 */
	Transition(string requiredCommand, State*  finalState);
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
    friend ostream& operator<<(ostream& out, Transition* t);
/**
 * This method returns a command's name
 */ 
    string getCommand();
/**
 * This method returns the next state once the associated command has been called
 */ 
    State * getNextState();

private:
    string command;
    State* nextState;
};
/**
 * This method initializes the game states and then stores them in a Vector
 */
    vector<State*> initializeGameStates();
/**
 * This method initializes the game transitions and then stores them in a Vector
 */
    vector<Transition*> initializeGameTransitions();
/************************************************************ GameEngineDriver **************************************************************/
void testGameStates();