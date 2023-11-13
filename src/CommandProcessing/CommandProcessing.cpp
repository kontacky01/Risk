#include "CommandProcessing.h"

/************************************************************ Command **************************************************************/
/**
 * Destructor
 */
    Command::~Command(){
		cout << "\nCommand Destructor was called";
	}
/**
 * Constructor with an argument(s)
 */
	Command::Command(string& cmd){
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
	
	string Command::getEffect(){
        return this->effect;
    }
    
    void Command::saveEffect(string effect){
        this->effect = effect;
        notify(this);
    }

/**
 * Override the string to log
*/
    string Command::stringToLog(){
        return "\n\n----------------------------------------- Logger -----------------------------------------\n\nCommand with name: " + command + " was saved with the following effect " +  effect + "\n\n------------------------------------------------------------------------------------------\n\n";
    }

/************************************************************ CommandProcessor **************************************************************/
/**
 * Default Constructor
 */
    CommandProcessor::CommandProcessor(){}
/**
 * Destructor
 */
    CommandProcessor::~CommandProcessor(){
		cout << "\nCommandProcessor Destructor was called";
	}
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
        cout << "command read";
        return out;
    }
/**
 * gets a command from the console as a string
 */
    string CommandProcessor::readCommand(){
        string commandstr;
        cout << "\nEnter a command:\n";
        cin >> commandstr;
        saveCommand(commandstr);
        return commandstr;
    }
/**
 * stores commands internally in a collection of Command objects
 */
    void CommandProcessor::saveCommand(string& commandstr){
        Command* commandObj = new Command(commandstr);
        commands.push_back(commandObj);
        notify(this);
    }
/**
 * public method for other objects such as the GameEngine or the Player
 */
    string CommandProcessor::getCommand(){
		string cmd = readCommand();
        return cmd;
    }
/**
 * checks if the command is valid in the current game state
 * let's say a players are in state issueorders but then give a command that belongs to executeorders
 * this command should be rejected
 * otherwise we update the state of the game
 */
    bool CommandProcessor::validate(GameEngine &engine, string& commandstr){
        if(engine.isCurrentStateStartState()){return commandstr == "loadmap";}
        else if(engine.isCurrentStateMaploadedState()){
            if(commandstr == "loadmap" || commandstr == "validatemap"){return true;}
            else{return false;}
        }
        else if(engine.isCurrentStateMapvalidatedState()){return commandstr == "addplayer";}
        else if(engine.isCurrentStatePlayersaddedState()){
            if(commandstr == "addplayer" || commandstr == "gamestart"){return true;}
            else{return false;}
        }
        else if(engine.isCurrentStateWinState()){
            if(commandstr == "replay" || commandstr == "quit"){return true;}
            else{return false;}
        }
        else{
            return false;
        }
    }

    vector<Command*> CommandProcessor::getCommands(){
        return this->commands;
    }
/**
 * Override the string to log
*/
    string CommandProcessor::stringToLog(){
        return "\n\n----------------------------------------- Logger -----------------------------------------\n\n" + commands.back()->getCommand() + " was saved to the collection of commands\n\n------------------------------------------------------------------------------------------\n\n";
    }

/*************************************************** FileCommandProcessorAdapter ***************************************************/
    /**
     * Constructor with with an argument(s)
     */
    FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filename){
        
        ifstream filereader(filename);
        
        if (!filereader.is_open()) {
            cerr << "Error opening the file.\n";
        }
        string cmd;

        while (getline(filereader, cmd)) {
            cout << "Command " << cmd << " was read from file\n";
            saveCommand(cmd);
        }

        filereader.close();
    }
    /**
     * Destructor
     */
    FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
		cout << "FileCommandProcessorAdapter Destructor was called";
	}
    /**
     * overide Stream insertion operator
     */
    ostream& operator<<(ostream& out, FileCommandProcessorAdapter* fcpa){
		cout << "file read";
		return out;
	}