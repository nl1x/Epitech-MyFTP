/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** UserCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/UserCommand.hpp"
#include "core/Core.hpp"
#include <sstream>

ftp::UserCommand::UserCommand(Server &server):
    ACommand(server, "USER", "Set the username for authentication.", {
        CommandArgument("username", false, CommandArgument::STRING)
    })
{}

bool ftp::UserCommand::run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args)
{
    executor->setUsername(args["username"]);
    executor->send("331 User name okay, need password.");
    return true;
}
