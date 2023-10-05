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


    cout << "\n\n---------> Test 2: string command comparsion <---------" << "\n\n\n";
    
    cout << "...Creating t1 for maploadedState ...\n";
    Transition* t1 = new Transition("loadmap", maploadedState);
    cout << "maploadedState created.\n";
   

    cout<<"...Testing command comparision...\n";
    string testLoadMapCommand = "loadmap";
    if (testLoadMapCommand.compare(t1->getCommand())==0) {
        cout << "testLoadMapCommand equals t1 command\n";
    }

    cout << "...Testing Dummy Command...\n";
    string dummyCommand =  "patato";
    if (dummyCommand.compare(t1->getCommand()) != 0) {
        cout << "DummyCommand is NOT Valid\n";
    }
        

    cout << "\n\n---------> Test 3: assign currentState to newState <---------" << "\n\n\n";

    cout << "...Creating currentState as start ...\n";
    State* currentState = new State("start");
    cout <<"currentState created.\n\n";

    cout << "...Printing Contents of current State...\n";
    cout <<"Current state is : " << currentState->getState() <<"\n\n";

    cout << "...assigning currentState using t1 nextState :maploaded ...\n";
    currentState = t1->getNextState();
    cout << "Current state is : " << currentState->getState() << "\n\n";
    
    cout << "...Creating transition t4 for addplayer ...\n";
    Transition* t4 = new Transition("addplayer", playersaddedState);
    cout << "addplayer created.\n\n";

    cout << "...assigning currentState using t4 nextState :playersadded ...\n";
    currentState = t4->getNextState();
    cout << "Current state is : " << currentState->getState() << "\n\n";

    

    cout << "\n\n---------> Test 3: testing user Input <---------" << "\n\n\n";

    
    cout <<"..Creating all transitions for GameEngine...\n ";
    //----------------------------------initializing transitions--------------------------------------
    //Transition* t1 = new Transition("loadmap", maploadedState);
    Transition* t2 = new Transition("loadmap", maploadedState);
    Transition* t3 = new Transition("validate", mapvalidatedState);
    //Transition* t4 = new Transition("addplayer", playersaddedState);
    Transition* t5 = new Transition("addplayer", playersaddedState);
    Transition* t6 = new Transition("assigncountries", assignreinforcementState);
    Transition* t7 = new Transition("issueorder", issueordersState);
    Transition* t8 = new Transition("issueorder", issueordersState);
    Transition* t9 = new Transition("endissueorders", executeordersState);
    Transition* t10 = new Transition("execorder", executeordersState);
    Transition* t11 = new Transition( "endexecorders", assignreinforcementState);
    Transition* t12 = new Transition("win", winState);
    Transition* t13 = new Transition("play", startState);
    Transition* t14 = new Transition( "end", endState);
    cout <<"Game transitions have been made.\n\n";

    cout <<"...Creating and initializing vector list for all transitions...\n";
    //adding initialized transitions to the vector of transitions
    vector<Transition*> gameTransitions;
    gameTransitions.push_back(t1);gameTransitions.push_back(t2);gameTransitions.push_back(t3);
    gameTransitions.push_back(t4);gameTransitions.push_back(t5);gameTransitions.push_back(t6);
    gameTransitions.push_back(t7);gameTransitions.push_back(t8);gameTransitions.push_back(t9);
    gameTransitions.push_back(t10);gameTransitions.push_back(t11);gameTransitions.push_back(t12);
    gameTransitions.push_back(t13);gameTransitions.push_back(t14);
    cout << "Transitions Vector has been made.\n\n";

    cout <<"...checking user input commands against game catalogue to allow or deny switch of states...\n";
    cout <<"...creating start state...\n";
    State* cState = new State("start");
    cout << "start state created\n";
    cout << "...Taking user input...\n";
    
    bool transComplete;
    string userCommand = "";
    while (userCommand.compare("end")!=0) {
    cout << "Enter one of the follwing commands:\n"
    "----------------------------\n"
    " loadmap\n validate\n addplayer\n assigncountries\n issueorder\n "
    "endissueorders\n execorder\n endexecorders\n win\n play\n end - to exit!\n"
    "----------------\n";
    cin >> userCommand;
    cout <<"\n\n";
    transComplete = false;
        for (int i = 0; i < gameTransitions.size(); i++) {
            if (userCommand.compare(gameTransitions[i]->getCommand())==0) { // string command
                cState = gameTransitions[i]->getNextState(); // assign oldstate to newState
                userCommand = gameTransitions[i]->getCommand();
                transComplete = true;
                break;
            }
        }

        if(transComplete){
            cout << "Current state is : " << cState->getState() << "\n\n";
        }else if(userCommand.compare("end")==0){
            cout <<"...Exiting testGameStates()...";
        }else{
            cout << "The command entered: " <<userCommand << " is invalid. Try Again.\n\n";
        }
    }
    

}