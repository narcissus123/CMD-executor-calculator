/**
 * command file defines all private and public attributes and methods of class Command.
 */
#ifndef MYcommand
#define MYcommand
#include <string>

/**
 * defining the Command class public and private attributes and methods
 * This class is defined to encapsulate and abstractly represent 
 * the commands that are going to be executed by our program.
 */
class Command{

    public:
        Command();
        std::string getCommand();
        int getReturnCode();
        std::string getResult();
        void setCommand(std::string& new_command);
        std::string executeCommand();

    private:
        std::string commandText;
        std::string result;
        int returnCode;
};

#endif