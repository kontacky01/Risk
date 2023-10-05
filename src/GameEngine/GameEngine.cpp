#include "GameEngine.h"

//-------------------------------------------Class State---------------------------------------------------------------

// Default constructor
State::State(){}

State::~State(){}

// Parameterized constructor
State::State(string name){
    stateName = name;
}

//Assignment Operator
State& State::operator=(const State& other){
    this->stateName = other.stateName;
    return *this;
}

// Copy constructor
State::State(const State& other) {
    this->stateName = other.stateName;
}

string State::getState(){
    return stateName;
}

//-------------------------------------------Class Transition----------------------------------------------------------

// Default Constructor
Transition::Transition(){}

Transition::~Transition() {}
	
// Parameterized Constructor
Transition::Transition(string requiredcommand, State* final){
    this->command = requiredcommand;
    this->nextState =final;
}

//Assignment Operator
Transition& Transition::operator=(const Transition& other){
    this->command = other.command;
    this->nextState = other.nextState;
    return *this;
}

// Copy Constructor
Transition::Transition(const Transition& other){
    this->command = other.command;
    this->nextState = other.nextState;
}

string Transition::getCommand(){
    return command;
}

State * Transition::getNextState(){
    return nextState;
}

void Transition::deletePointerNextState(){
    delete this->nextState;
    this->nextState = NULL;
}
