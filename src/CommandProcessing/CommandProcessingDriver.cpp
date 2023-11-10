#include "CommandProcessing.h"

void testCommandProcessor(){
    cout << "\n************************************\nTesting Command Processing!!! \n************************************\n\n";
    
    bool validChoice = false;
    GameEngine engine;

    while(!validChoice){

        int choice = 0;
        string retrievedCommand;
        string file;
        vector<Command*> fileCommands;
        string positiveEffect = "Command executed :)";
        string negativeEffect = "Invalid command in current state :(";

        cout << "Would you like to\n1. enter commands from the console or,\n2. get commands from a file?\nPlease write 1 or 2 and hit ENTER: \n";
        cin >> choice;

        switch (choice){            
            case 1:{
                while(true){
                    CommandProcessor* cpObj = new CommandProcessor();
                    retrievedCommand = cpObj->getCommand();
                    if (retrievedCommand == "quit") {
                        engine.setState(new EndState());
                        //cpObj->getCommands().back()->saveEffect(positiveEffect); will be joined with LoggingObserver
                        break;
                    }
                    if(cpObj->validate(engine, retrievedCommand)){
                        engine.executeCommand(retrievedCommand);
                        //cpObj->getCommands().back()->saveEffect(positiveEffect); will be joined with LoggingObserver
                    }
                    else{
                        cout << "Invalid command in current game state\n";
                        //cpObj->getCommands().back()->saveEffect(negativeEffect); will be joined with LoggingObserver
                    }
                }
                validChoice = true;
            break;
            }
            case 2:{
                /**
                 * i can't seem to opena file by passing its name on the console
                 * so i hardcoded a file path instead of asking the user to enter the name of the file.
                */
                //cout << "Enter the file name: \n";
                //cin >> file; //
                cout << "\n/***********************************************************************************************************/\n";
                FileCommandProcessorAdapter* fcpaObj = new FileCommandProcessorAdapter("C:/Users/konta/OneDrive/Desktop/COMP 345//Risk/src/CommandProcessing/Commands.txt");
                fileCommands = fcpaObj->getCommands();
                for(int i=0; i<fileCommands.size(); i++){
                    retrievedCommand = fileCommands[i]->getCommand();
                    if(retrievedCommand == "quit"){
                        cout <<"\n" << retrievedCommand << " was read from file and is valid to execute\n";
                        engine.setState(new EndState());
                        //fileCommands[i]->saveEffect(positiveEffect); will be joined with LoggingObserver
                        break;
                    }
                    if(fcpaObj->validate(engine, retrievedCommand)){
                        cout <<"\n" << retrievedCommand << " was read from file and is valid to execute\n";
                        engine.executeCommand(retrievedCommand);
                        //fileCommands[i]->saveEffect(positiveEffect); will be joined with LoggingObserver
                    }
                    else{
                        cout << "\nInvalid command in current game state and is NOT VALID to execute\n";
                        //fileCommands[i]->saveEffect(negativeEffect); will be joined with LoggingObserver
                    }
                }
                validChoice = true;
            break;
            }
            default:
                cout << "The entered choice is invalid, TRY AGAIN!\n";
        }
    }
}