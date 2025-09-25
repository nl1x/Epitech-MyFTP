/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ACommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/abstract/ACommand.hpp"
#include "file/File.hpp"
#include <utility>
#include <sstream>
#include <unistd.h>

ftp::ACommand::ACommand(Server &server, std::string name, std::string description, const std::list<CommandArgument> &args, const bool requireAuth, const bool requireDataSocket):
    server_(server), name_m(std::move(name)), description_m(std::move(description)), args_definition_m(args), requireAuth_m(requireAuth), requireDataSocket_m(requireDataSocket)
{}

std::string ftp::ACommand::getName() const
{
    return this->name_m;
}

std::string ftp::ACommand::getDescription() const
{
    return this->description_m;
}

std::string ftp::ACommand::getUsage() const
{
    std::string usage;

    for (auto &argDef : this->args_definition_m) {
        usage += argDef.isOptional() ? "[<" : "<";
        usage += argDef.getName();
        usage += argDef.isOptional() ? ">] " : "> ";
    }
    return this->name_m + " " + usage;
}

bool ftp::ACommand::isAuthRequired() const
{
    return this->requireAuth_m;
}

bool ftp::ACommand::isDataSocketRequired() const
{
    return this->requireDataSocket_m;
}

bool ftp::ACommand::execute(const std::shared_ptr<Client> &executor, std::string command)
{
    std::map<std::string, std::string> args;
    std::stringstream s(command);
    std::string arg;

    s >> arg; // Remove the command name
    if (this->isAuthRequired() && !executor->isLoggedIn()) {
        executor->send("530 Unauthenticated request");
        return true;
    }
    if (this->isDataSocketRequired()) {
        if (!executor->isDataSocketOpen()) {
            executor->send("425 Can't open data connection.");
            return true;
        }

        const int pid = fork();
        if (pid == -1)
            throw ForkError("An error occurred while trying to fork in the LIST command.");
        if (pid != 0)
            return true;
        RUNNING = false; // Stop the server in the child process
    }

    for (const auto &argDef : this->args_definition_m) {
        arg = "";
        s >> arg;
        if (arg.empty() && !argDef.isOptional())
            throw InvalidCommandArgumentError(command, argDef.getName());
        if (argDef.getType() != CommandArgument::INT || isNumber(arg))
            args.insert({argDef.getName(), arg});
        else
            throw InvalidCommandArgumentError(command, arg);
    }
    return this->run(executor, args);
}

int ftp::ACommand::toNumber(const std::string &str)
{
    std::stringstream stream(str);
    int num;

    stream >> num;
    return num;
}

bool ftp::ACommand::isNumber(std::string str)
{
    if (str.empty())
        return false;
    for (const char i : str) {
        if (i > '9' || i < '0')
            return false;
    }
    return true;
}
