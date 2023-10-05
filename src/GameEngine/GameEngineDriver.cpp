// free func testGameStates()
#include "GameEngine.h"


void testGameStates(){

    //-------------------------------------initializing states----------------------------------------
    
    cout << "\n\n---------> Test 1: intializing states <---------" << "\n\n\n";
    //startup
    State* startState = new State("start");
    State* maploadedState = new State("maploaded");
    State* mapvalidatedState = new State("mapvalidated");
    State* playersaddedState = new State("playersadded");
    //play
    State* assignreinforcementState = new State("assignreinforcement");
    State* issueordersState = new State("issueorders");
    State* executeordersState = new State("executeorders");
    State* winState = new State("win");
    //end
    State* endState = new State("end");
    cout <<"..Getting start state...";
    cout << startState->getState() <<"\n";
    cout <<"state state has been printed\n\n.";

    Transition* t1 = new Transition(startState, "loadmap", maploadedState);
    Transition* t2 = new Transition(maploadedState, "loadMap", maploadedState);

    cout << "\n\n---------> Test 2: string command comparsion <---------" << "\n\n\n";

    cout<<"...Testing command comparision...\n";
    string testLoadMapCommand = "loadmap";
    if (testLoadMapCommand.compare(t1->getCommand())==0) {
        cout << "testLoadMapCommand equals t1 command";
    }
    else{
        cout << "testLoadMapCommand does NOT equal t1 command";
    }



    
/*
//----------------------------------initializing transitions--------------------------------------
    Transition* t1 = new Transition(startState, "loadmap", maploadedState);
    Transition* t2 = new Transition(maploadedState, "loadmap", maploadedState);
    Transition* t3 = new Transition(maploadedState, "validate", mapvalidatedState);
    Transition* t4 = new Transition(mapvalidatedState, "addplayer", playersaddedState);
    Transition* t5 = new Transition(playersaddedState, "addplayer", playersaddedState);
    Transition* t6 = new Transition(playersaddedState, "assigncountries", assignreinforcementState);
    Transition* t7 = new Transition(assignreinforcementState, "issueorder", issueordersState);
    Transition* t8 = new Transition(issueordersState, "issueorder", issueordersState);
    Transition* t9 = new Transition(issueordersState, "endissueorders", executeordersState);
    Transition* t10 = new Transition(executeordersState, "execorder", executeordersState);
    Transition* t11 = new Transition(executeordersState, "endexecorders", assignreinforcementState);
    Transition* t12 = new Transition(executeordersState, "win", winState);
    Transition* t13 = new Transition(winState, "play", startState);
    Transition* t14 = new Transition(winState, "end", endState);

//adding initialized transitions to the vector of transitions
    vector<Transition*> gameTransitions;
    gameTransitions.push_back(t1);gameTransitions.push_back(t2);gameTransitions.push_back(t3);
    gameTransitions.push_back(t4);gameTransitions.push_back(t5);gameTransitions.push_back(t6);
    gameTransitions.push_back(t7);gameTransitions.push_back(t8);gameTransitions.push_back(t9);
    gameTransitions.push_back(t10);gameTransitions.push_back(t11);gameTransitions.push_back(t12);
    gameTransitions.push_back(t13);gameTransitions.push_back(t14);
*/
  
    

    //checking user input commands against game catalogue to allow or deny switch of states

    /*
     State* nowState = new State("start");
      while (nowState != endState) {
        string userCommand;
        cout << "Enter action among\n loadmap\n validatemap\n addplayer\n assigncountries\n issueorder\n endissueorders\n execorder\n endexecorders\n";
        cin >> userCommand;

        for (int i = 0; i < gameTransitions.size(); i++) {
            if (userCommand == gameTransitions[i].command) { // string command
                nowState = gameTransitions[i].nextState; // assign oldstate to newState
            }
            else {
                cout << "The command entered is invalid. Try Again.\n"
            }
        }
    }
    */
   
  


}