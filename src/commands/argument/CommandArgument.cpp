/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** CommandArgument.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <utility>
#include "commands/argument/CommandArgument.hpp"

ftp::CommandArgument::CommandArgument(std::string name, const bool isOptional, const ArgType type):
    name_m(std::move(name)), optional_m(isOptional), type_m(type)
{}

std::string ftp::CommandArgument::getName() const
{
    return this->name_m;
}

ftp::CommandArgument::ArgType ftp::CommandArgument::getType() const
{
    return this->type_m;
}

bool ftp::CommandArgument::isOptional() const
{
    return this->optional_m;
}
