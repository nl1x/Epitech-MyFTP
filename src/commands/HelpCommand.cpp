/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** HelpCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/HelpCommand.hpp"

ftp::HelpCommand::HelpCommand(Server& server):
    ACommand(server, "HELP", "List all commands", {
        CommandArgument("command", true, CommandArgument::STRING)
    }, true)
{}

bool ftp::HelpCommand::run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args)
{
    auto commands = this->server_.getCommands();
    std::string msg;

    if (commands.find(args["command"]) != commands.end()) {
        msg = "214 Usage of " + args["command"] + " : ";
        msg += commands[args["command"]]->getUsage();
    } else {
        msg = "214 Commands: ";
        for (const auto &[name, command] : commands) {
            msg += command->getName();
            if ((commands.find(name)++) != commands.end())
                msg += " - ";
        }
    }
    executor->send(msg);
    return true;
}
