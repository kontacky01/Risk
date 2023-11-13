#include "CommandProcessing.h"

void testCommandProcessor(){
    cout << "\n************************************\nTesting Command Processing!!! \n************************************\n\n";
    
    bool validChoice = false;

    while(!validChoice){

        int choice = 0;
        string retrievedCommand;
        string file;
        vector<Command*> fileCommands;
        string positiveEffect = "Command executed :)";
        string negativeEffect = "Invalid command in current state :(";

        cout << "Would you like to\n1. enter commands from the console or,\n2. get commands from a file?\nPlease write 1 or 2 and hit ENTER: \n";
        cin >> choice;
        GameEngine engine;

        switch (choice){            
            case 1:{
                while(true){
                    CommandProcessor* cpObj = new CommandProcessor();
                    retrievedCommand = cpObj->getCommand();
                    if (retrievedCommand == "quit") {
                        cout << retrievedCommand << " command was read from console and is valid to execute. YOU\"LL EXIT THE GAME\n\n";
                        engine.setState(new EndState());
                        //cpObj->getCommands().back()->saveEffect(positiveEffect); //will be joined with LoggingObserver
                        break;
                    }
                    if(cpObj->validate(engine, retrievedCommand)){
                        cout <<"\n\n" << retrievedCommand << " command was read from console and is valid to execute in current game state.\n\n";
                        engine.executeCommand(retrievedCommand);
                        //cpObj->getCommands().back()->saveEffect(positiveEffect); //will be joined with LoggingObserver
                    }
                    else{
                        cout <<"\n\n" << retrievedCommand << " command was read from console and is NOT VALID to execute in current game state.\n\n";
                        //cpObj->getCommands().back()->saveEffect(negativeEffect); //will be joined with LoggingObserver
                    }

                    delete cpObj;
                    cpObj = NULL;
                }
                validChoice = true;
            break;
            }
            case 2:{
                cout << "\n\nYou choose to read commands from a file.\n\n";
                /**
                 * i can't seem to open a file by passing its name on the console
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
                        cout << retrievedCommand << " command was read from file and is valid to execute. YOU\"LL EXIT THE GAME\n\n";
                        engine.setState(new EndState());
                        //fileCommands[i]->saveEffect(positiveEffect); //will be joined with LoggingObserver
                        break;
                    }
                    if(fcpaObj->validate(engine, retrievedCommand)){
                        cout <<"\n\n" << retrievedCommand << " command was read from file and is valid to execute in current game state.\n\n";
                        engine.executeCommand(retrievedCommand);
                        //fileCommands[i]->saveEffect(positiveEffect); //will be joined with LoggingObserver
                    }
                    else{
                        cout <<"\n\n" << retrievedCommand << " command was read from file and is NOT VALID to execute in current game state.\n\n";
                        //fileCommands[i]->saveEffect(negativeEffect); //will be joined with LoggingObserver
                    }
                }

                delete fcpaObj;
                fcpaObj = NULL;

                validChoice = true;
            break;
            }
            default:
                cout << "The entered choice is invalid, TRY AGAIN!\n";
        }
    }
}