//#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
//#include "Map.h"
#include "../Player/Player.h"
#include "../CardsDeck/Cards.h"
#include "../OrdersList/Orders.h"
//-------------------------------------------Class State---------------------------------------------------------------
// A State object holds a string such as start, maploaded, playersadded etc...
class State{
public:	
	string* stateName;                                  // State's name

	State();                                         // Default constructor

	State(const string &name);                            // Parameterized constructor

    State& operator=(const State& other);         // Assignment Operator

	State(const State& other);                  // Copy constructor

};

//-------------------------------------------Class Transition----------------------------------------------------------
// A Transition object contains pointers from one state to another as well as its required command
class Transition{
public:	
	State* currentState;         // current state
	string* command;            // required command to perform transition
    State* nextState;           // next state

	Transition();           // Default Constructor
	
	Transition(const State& initial, const string& requiredcommand, const State&  final);         // Parameterized Constructor

	Transition& operator=(const Transition& other);                           // Assignment Operator

    Transition(const Transition& other);                                    // Copy constructor
};
void initialize();
void testGameStates();