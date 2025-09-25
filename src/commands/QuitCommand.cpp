/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ExitCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/QuitCommand.hpp"
#include "core/Core.hpp"
#include <iostream>

ftp::QuitCommand::QuitCommand(Server &server):
    ACommand(server, "QUIT", "Disconnect from the server.", {}, true)
{}

bool ftp::QuitCommand::run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args)
{
    (void) args;
    executor->send("221" FTP_EOF);
    this->server_.closeConnection(executor);
    return true;
}


