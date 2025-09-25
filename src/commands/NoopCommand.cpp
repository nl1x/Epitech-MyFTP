/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** NoopCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/NoopCommand.hpp"

ftp::NoopCommand::NoopCommand(Server& server):
    ACommand(server, "NOOP", "Does nothing.", {}, true)
{}

bool ftp::NoopCommand::run(const std::shared_ptr<Client>& executor, [[maybe_unused]] std::map<std::string, std::string> args)
{
    executor->send("200 Ok.");
    return true;
}
