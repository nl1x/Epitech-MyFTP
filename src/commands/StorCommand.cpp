/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** StorCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/StorCommand.hpp"

#include <iostream>
#include <unistd.h>

#include "file/File.hpp"

ftp::StorCommand::StorCommand(Server& server):
    ACommand(server, "STOR", "Upload a file.", {
        CommandArgument("pathname", false, CommandArgument::STRING)
    }, true, true)
{}

bool ftp::StorCommand::run(const std::shared_ptr<Client> &executor, std::map<std::string, std::string> args)
{
    std::string path;

    if (args["pathname"].find('/') == 0)
        path = this->server_.getRootDirectory() + args["pathname"];
    else
        path = executor->getRealWorkingDirectory() + "/" + args["pathname"];

    const File storedFile(path, true);
    const std::shared_ptr<DataSocket> dataSocket = executor->getDataSocket();

    if (!storedFile.hasPermission(W_OK)) {
        executor->send("550 Missing permissions.");
        return true;
    }

    dataSocket->openConnection(executor);
    const std::string fileContent = dataSocket->read();
    storedFile.write(fileContent);
    dataSocket->closeConnection(executor);

    return true;
}
