#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "../LoggingObserver/LoggingObserver.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../OrdersList/Orders.h"
#include "../CardsDeck/Cards.h"
#include "../Player/Player.h"

using namespace std;

/************************************************************ Command **************************************************************/
class Command : public Subject, public ILoggable {
public:
    /**
     * Destructor
     */
    ~Command();

    /**
     * Constructor with an argument(s)
     */
    Command(string &cmd);

    /**
     * Assignment Operator
     */
    Command &operator=(const Command &other);

    /**
     * Copy Constructor
     */
    Command(const Command &other);

    /**
     * overide Stream insertion operator
     */
    friend ostream &operator<<(ostream &out, Command *c);

    string getCommand();

    string getEffect();

    void saveEffect(string effect);

/**
 * Override string to log (observer pattern)
*/
    string stringToLog();

private:
    string command;
    string effect;
};

/************************************************************ CommandProcessor **************************************************************/
class Command;// Forward declaration
class GameEngine;// Forward declaration
class CommandProcessor : public Subject, public ILoggable {
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
    CommandProcessor(vector<Command *> cmds);

    /**
     * Assignment Operator
     */
    CommandProcessor &operator=(const CommandProcessor &other);

    /**
     * Copy Constructor
     */
    CommandProcessor(const CommandProcessor &other);

    /**
     * overide Stream insertion operator
     */
    friend ostream &operator<<(ostream &out, CommandProcessor *cp);

    /**
     * stores commands internally in a collection of Command objects
     */
    void saveCommand(string &commandstr);

    /**
     * public method for other objects such as the GameEngine or the Player
     */
    string getCommand();

    /**
     * checks if the command is valid in the current game state
     */
    bool validate(GameEngine &engine, string &commandstr);

    vector<Command *> getCommands();

/**
 * Override string to log (observer pattern)
*/
    string stringToLog();

private:
    vector<Command *> commands;

    /**
     * gets a command from the console as a string
     */
    string readCommand();

};

/*************************************************** FileCommandProcessorAdapter ***************************************************/
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    /**
     * Constructor with with an argument(s)
     */
    FileCommandProcessorAdapter(string filename);

    /**
     * Destructor
     */
    ~FileCommandProcessorAdapter();

    /**
     * overide Stream insertion operator
     */
    friend ostream &operator<<(ostream &out, FileCommandProcessorAdapter *fcpa);
};

/************************************************************ CommandProcessingDriver **************************************************************/
void testCommandProcessor();