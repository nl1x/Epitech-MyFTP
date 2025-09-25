/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ChangeWorkingDirectoryCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/CwdCommand.hpp"

ftp::CwdCommand::CwdCommand(Server& server):
    ACommand(server, "CWD", "Change working directory.", {
        CommandArgument("pathname", false, CommandArgument::STRING)
    }, true)
{}

bool ftp::CwdCommand::run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args)
{
    if (!executor->changeWorkingDirectory(args["pathname"])) {
        executor->send("550 Directory not found: " + args["pathname"]);
    } else {
        executor->send("250 Requested file action okay, completed.");
    }
    return true;
}
