/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PwdCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/PwdCommand.hpp"

ftp::PwdCommand::PwdCommand(Server& server):
    ACommand(server, "PWD", "Print working directory.", {}, true)
{}

bool ftp::PwdCommand::run(const std::shared_ptr<Client>& executor, [[maybe_unused]] std::map<std::string, std::string> args)
{
    executor->send("257 " + executor->getWorkingDirectory());
    return true;
}
