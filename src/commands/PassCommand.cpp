/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PassCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/PassCommand.hpp"

ftp::PassCommand::PassCommand(Server& server):
    ACommand(server, "PASS", "Login with password", {
        CommandArgument("password", true, CommandArgument::STRING)
    })
{}

bool ftp::PassCommand::run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args)
{
    if (executor->getUsername().empty())
        executor->send("332 Need account for login.");
    else if (executor->login(args["password"]))
        executor->send("230 User logged in, proceed.");
    else
        executor->send("530 Wrong password.");
    return true;
}
