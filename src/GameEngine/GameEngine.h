#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

//#include "Map.h"
/*
#include "../Player/Player.h"
#include "../CardsDeck/Cards.h"
#include "../OrdersList/Orders.h"
*/

//-------------------------------------------Class State---------------------------------------------------------------
// A State object holds a string such as start, maploaded, playersadded etc...
class State{
public:	
	State();                                         // Default constructor

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
	Transition(string requiredcommand, State*  final);         // Parameterized Constructor
	Transition& operator=(const Transition& other);                           // Assignment Operator
    Transition(const Transition& other);                                    // Copy constructor
    string getCommand();
    State * getNextState();
private:
    string command;            // required command to perform transition
    State* nextState;           // next state
};
void initialize();
void testGameStates();