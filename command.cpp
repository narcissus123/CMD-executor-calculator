/**
 * the Command class suppose to encapsulate and abstractly represent
 * the user entered commands that our program is going to execute.
 * The boost library is used in this class.
 */
#include "command.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/process.hpp>
namespace bp = boost::process;

/**
 * the constructor to initialize the attributes of class
 */
Command::Command()
{
    commandText = ""; // user input command
    result = "";      // result of executing the command at command prompt
    returnCode = 0;   // the returned integer from command prompt indicating whether the command succeeded
}

/**
 *method to retrieve the returnCode attributes
 *@ return returnCode an integer value that is returned from executing the user command
 */
int Command::getReturnCode()
{
    return returnCode;
}

/**
 * method to retrieve the entered user comment
 * @ return commandText the comment that the user want to be exeuted at command prompt
 */
std::string Command::getCommand()
{
    return commandText;
}

/**
 * method to retrieve the result of command execution
 * @ return result attribute of type string
 */
std::string Command::getResult()
{
    return result;
}

/**
 * method to set the user command
 * @ param &new_command the entered user command
 */
void Command::setCommand(std::string &new_command)
{
    commandText = new_command;
}

/**
 * method to execute the enetred user command
 * @ return the result of the command execution
 */
std::string Command::executeCommand()
{
    try
    {
        bp::ipstream pipe_stream;
        bp::child c(commandText, bp::std_out > pipe_stream);

        std::string line;
        while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        {
            std::vector<std::string> MyStrings;
            MyStrings.push_back(line);
            result = boost::algorithm::join(MyStrings, "\n");
        }
        returnCode = 0;
        c.wait();
    }
    catch (std::exception &e)
    {
        returnCode = -1;
        result = e.what();
    }
    return result;
}
