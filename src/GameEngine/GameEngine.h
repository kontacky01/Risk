#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

//-------------------------------------------Class State---------------------------------------------------------------
// A State object holds a string such as start, maploaded, playersadded etc...
class State{
public:	
    State();                                         // Default constructor
    ~State();                                       // Destructor
    State(string name);                            // Parameterized constructor
    State& operator=(const State& other);         // Assignment Operator
    State(const State& other);                  // Copy constructor
    string getState();
   
private:
    string stateName;                                  // State's name
};

//-------------------------------------------Class Transition----------------------------------------------------------
// A Transition object contains pointers from one state to another as well as its required command
class Transition{
public:	
	Transition();           // Default Constructor
    ~Transition();          // Destructor
	Transition(string requiredCommand, State*  finalState);         // Parameterized Constructor
	Transition& operator=(const Transition& other);                           // Assignment Operator
    Transition(const Transition& other);                                    // Copy constructor
    string getCommand();
    State * getNextState();
    void deletePointerNextState();
private:
    string command;            // required command to perform transition
    State* nextState;           // next state
};

//-------------------------------------------Class GameEngineDriver----------------------------------------------------------

void testGameStates();