/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** RetrCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/RetrCommand.hpp"

#include <unistd.h>

#include "file/File.hpp"

ftp::RetrCommand::RetrCommand(Server& server):
    ACommand(server, "RETR", "Download a file.", {
        CommandArgument("pathname", false, CommandArgument::STRING)
    }, true, true)
{}

bool ftp::RetrCommand::run(const std::shared_ptr<Client> &executor, std::map<std::string, std::string> args)
{
    std::string path;

    if (args["pathname"].find('/') == 0)
        path = this->server_.getRootDirectory() + args["pathname"];
    else
        path = executor->getRealWorkingDirectory() + "/" + args["pathname"];

    try {
        const File storedFile(path);
        const std::shared_ptr<DataSocket> dataSocket = executor->getDataSocket();

        if (!storedFile.hasPermission(R_OK)) {
            executor->send("550 Missing permissions.");
            return true;
        }
        dataSocket->openConnection(executor);
        const std::string content = storedFile.read();
        dataSocket->sendRaw(content);
        dataSocket->closeConnection(executor);
    } catch (const File::FileNotFoundError &err) {
        executor->send("550 No such file or directory.");
    }

    return true;
}
