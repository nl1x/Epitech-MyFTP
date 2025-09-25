/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** TypeCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/TypeCommand.hpp"

ftp::TypeCommand::TypeCommand(Server& server):
    ACommand(server, "TYPE", "Unknown command behaviour.", {
        CommandArgument("typecode", true, CommandArgument::STRING)
    }, true)
{}

bool ftp::TypeCommand::run(const std::shared_ptr<Client>& executor, [[maybe_unused]] std::map<std::string, std::string> args)
{
    executor->send("200 Ok.");
    return true;
}
