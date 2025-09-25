/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** CommandManager.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "manager/CommandManager.hpp"
#include "error/Error.hpp"
#include <iostream>

void ftp::CommandManager::registerCommand(const std::shared_ptr<ICommand> &command)
{
    this->commands_m.insert({command->getName(), command});
}

std::shared_ptr<ftp::ICommand> ftp::CommandManager::getCommand(const std::string &name)
{
    auto toUpperCase = [](std::string str)
    {
        for (size_t i = 0; i < str.length(); i++)
            if (str[i] >= 'a' && str[i] <= 'z')
                str[i] += 'A' - 'a';
        return str;
    };

    const auto command = this->commands_m.find(toUpperCase(name));

    if (command == this->commands_m.end())
        throw CommandNotFoundError(name);
    return command->second;
}

std::unordered_map<std::string, std::shared_ptr<ftp::ICommand>> ftp::CommandManager::getCommands()
{
    return this->commands_m;
}
