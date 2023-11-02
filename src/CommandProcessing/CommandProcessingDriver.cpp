#include "CommandProcessing.h"

void testCommandProcessor(){
    CommandProcessor* cp = new CommandProcessor();
    Command* retrievedCommand = cp->getCommand();
    cout << "------TEST-----" << retrievedCommand->getCommand();
    delete cp;
    cp = NULL;
}