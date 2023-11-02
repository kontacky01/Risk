#include "CommandProcessing.h"

/************************************************************ Command **************************************************************/
/**
 * Default Constructor
 */
	Command::Command(){}
/**S
 * Destructor
 */
    Command::~Command(){}
/**
 * Constructor with with an argument(s)
 */
	Command::Command(string cmd){
        this->command = cmd;
        this->effect = "";
    }
/**
 * Assignment Operator
 */
	Command& Command::operator=(const Command& other){
        this->command = other.command;
        this->effect = other.effect;
        return *this;
    }
/**
 * Copy Constructor
 */
    Command::Command(const Command& other){
        this->command = other.command;
        this->effect = other.effect;
    }
/**
 * overide Stream insertion operator
 */
    ostream& operator<<(ostream& out, Command* c){
        cout << "The " << c->command << " currently leads to the effect of : " << c->effect << "\n";
        return out;
    }

    string Command::getCommand(){
        return this->command;
    }
    
    void Command::saveEffect(string e){
        this->effect = e;
    }

/*************************************************** FileCommandProcessorAdapter ***************************************************/
/**
 * Default Constructor
 */
    FileCommandProcessorAdapter::FileCommandProcessorAdapter(){}
/**
 * Destructor
 */
    FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){}
/**
 * overide Stream insertion operator
 */
    ostream& operator<<(ostream& out, FileCommandProcessorAdapter* cp){
        //haven't decided what to printout so TODO!!!
        return out;
    }
/**
 * reads commands line by line from an input file and saves the commands internally in a collection of Command objects
 */
    string FileCommandProcessorAdapter::readCommand(string fileToRead){
        string commandstr;
        ifstream readCommands(fileToRead);
        getline(readCommands, commandstr);
        return commandstr;
    }

/************************************************************ CommandProcessor **************************************************************/
/**
 * Default Constructor
 */
    CommandProcessor::CommandProcessor(){}
/**
 * Destructor
 */
    CommandProcessor::~CommandProcessor(){}
/**
 * Constructor with with an argument(s)
 */
    CommandProcessor::CommandProcessor(vector<Command*> cmds){
        this->commands = cmds;
    }
/**
 * Assignment Operator
 */
    CommandProcessor& CommandProcessor::operator=(const CommandProcessor& other){
        this->commands = other.commands;
        return *this;
    }
/**
 * Copy Constructor
 */
    CommandProcessor::CommandProcessor(const CommandProcessor& other){
        this->commands = other.commands;
    }
/**
 * overide Stream insertion operator
 */
    ostream& operator<<(ostream& out, CommandProcessor* cp){
        //haven't decided what to printout so TODO!!!
        return out;
    }
/**
 * gets a command from the console as a string
 */
    string CommandProcessor::readCommand(){
        string commandstr;
        cout << "Enter a command:\n";
        cin >> commandstr;
        return commandstr;
    }
/**
 * stores commands internally in a collection of Command objects
 */
    Command* CommandProcessor::saveCommand(string commandstr){
        Command* commandobj = new Command(commandstr);
        commands.push_back(commandobj);
        return commandobj;
    }
/**
 * public method for other objects such as the GameEngine or the Player
 */
    Command* CommandProcessor::getCommand(){
    
        bool validChoice = false;
        string retrievedCommand = "";
        Command* cobj = nullptr;
        int choice;
        string file;

        while(!validChoice){
            cout << "Would you like 1. to enter commands from the console or 2. get commands from a file? Please write 1 or 2 and hit ENTER: \n";
            cin >> choice;
            switch (choice){
                case 1:
                    retrievedCommand = readCommand();
                    cobj = saveCommand(retrievedCommand);
                    cout << "The command "<< cobj->getCommand() << " was saved.\n\n";
                    validChoice = true;
                break;

                case 2: 
                    cout << "Enter the file name: \n";
                    cin >> file;
                    FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter();
                    retrievedCommand = fcpa->readCommand(file);
                    cobj = saveCommand(retrievedCommand);
                    cout << "The command "<< cobj->getCommand() << " was saved.\n\n";
                    validChoice = true;
                    delete fcpa;
                    fcpa = NULL;
                break;

                default:
                    cout << "The entered choice is invalid, TRY AGAIN!\n";
            }
        }
        return cobj;
    }
/**
 * checks if the command is valid in the current game state
 * let's say a player is in state issueorders but then gives a command that belongs to executeorders
 * this command should be rejected
 * otherwise we update the state of the player
 */
/*    void validate(Command* cmd, Player* p){
        bool isValid = false;
        vector<Transition*> transitions = initializeGameTransitions();
        for (int i = 0; i < transitions.size(); i++) {
            if (cmd->getCommand().compare(transitions[i]->getCommand()) == 0 
                    && transitions[i]->getCurrentState()->getStateName() == p->getState()->getStateName()) {
                        isValid = true;
                        p->setState(transitions[i]->getNextState());
                        cout << "this command is valid in the current game state.\n";
                        string effect = "Player was moved to "+transitions[i]->getNextState()->getStateName();
                        cmd->saveEffect(effect);
            }
            if (isValid && i == transitions.size() - 1) {
                cmd->saveEffect("Invalid Command Error");
                cout << "this command is NOT VALID in the current game state.\n";
            }
        }
    }
*/