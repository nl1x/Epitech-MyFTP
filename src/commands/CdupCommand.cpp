/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** CdupCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/CdupCommand.hpp"

ftp::CdupCommand::CdupCommand(Server& server):
    ACommand(server, "CDUP", "Change working directory to parent directory.", {}, true)
{}

bool ftp::CdupCommand::run(const std::shared_ptr<Client>& executor, [[maybe_unused]] std::map<std::string, std::string> args)
{
    if (!executor->changeWorkingDirectory("..")) {
        executor->send("550 Directory not found: ../");
    } else {
        executor->send("250 Requested file action okay, completed.");
    }
    return true;
}
