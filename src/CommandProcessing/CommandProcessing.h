#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>

#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../OrdersList/Orders.h"
#include "../CardsDeck/Cards.h"
#include "../GameEngine/GameEngine.h"

using namespace std;

/************************************************************ Command **************************************************************/
class Command{
    public:
    /**
     * Default Constructor
     */
    Command();
    /**S
     * Destructor
     */
    ~Command();
    /**
     * Constructor with with an argument(s)
     */
    Command(string cmd);
    /**
     * Assignment Operator
     */
    Command& operator=(const Command& other);
    /**
     * Copy Constructor
     */
    Command(const Command& other);
    /**
     * overide Stream insertion operator
     */
    friend ostream& operator<<(ostream& out, Command* c);

    string getCommand();
    
    void saveEffect(string e);

    private:
    string command;
    string effect;
};

/************************************************************ CommandProcessor **************************************************************/
class Command;  // Forward declaration for Command class
class Player;  // Forward declaration for Command class
class CommandProcessor{
    public:
    /**
     * Default Constructor
     */
    CommandProcessor();
    /**
     * Destructor
     */
    ~CommandProcessor();
    /**
     * Constructor with with an argument(s)
     */
    CommandProcessor(vector<Command*> cmds);
    /**
     * Assignment Operator
     */
    CommandProcessor& operator=(const CommandProcessor& other);
    /**
     * Copy Constructor
     */
    CommandProcessor(const CommandProcessor& other);
    /**
     * overide Stream insertion operator
     */
    friend ostream& operator<<(ostream& out, CommandProcessor* cp);
    /**
     * stores commands internally in a collection of Command objects
     */
    Command* saveCommand(string commandstr);    
    /**
     * public method for other objects such as the GameEngine or the Player
     */
    Command* getCommand();
    /**
     * checks if the command is valid in the current game state
     */
    void validate(Command* cmd, Player* p);

    private:
    vector<Command*> commands;
    /**
     * gets a command from the console as a string
     */
    string readCommand();

};

/*************************************************** FileCommandProcessorAdapter ***************************************************/
class FileCommandProcessorAdapter{
    public:
    /**
     * Default Constructor
     */
    FileCommandProcessorAdapter();
    /**
     * Destructor
     */
    ~FileCommandProcessorAdapter();
    /**
     * overide Stream insertion operator
     */
    friend ostream& operator<<(ostream& out, FileCommandProcessorAdapter* fcpa);
    /**
     * gets a command from the console as a string
    */
    string readCommand(string fileToRead);
};

/************************************************************ CommandProcessingDriver **************************************************************/
void testCommandProcessor();