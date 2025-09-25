/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** DeleCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/DeleCommand.hpp"
#include "file/File.hpp"
#include <ostream>

ftp::DeleCommand::DeleCommand(Server& server):
    ACommand(server, "DELE", "Delete a file on the server.", {
        CommandArgument("path", false, CommandArgument::STRING)
    }, true)
{}

bool ftp::DeleCommand::run(const std::shared_ptr<Client> &executor, std::map<std::string, std::string> args)
{
    std::string path;

    if (args["path"].find('/') == 0)
        path = this->server_.getRootDirectory() + "/" + args["path"];
    else
        path = executor->getRealWorkingDirectory() + "/" + args["path"];

    try {
        File file(path);

        if (!file.isInDirectory(this->server_.getRootDirectory()))
            executor->send("550 File not found.");
        else if (file.isDirectory())
            executor->send("550 File is a directory.");
        else {
            if (!file.dele())
                executor->send("550 Cannot delete this file.");
            else
                executor->send("250 Requested file action okay, completed.");
        }
    } catch (const File::FileNotFoundError &err) {
        executor->send("550 File not found.");
        return false;
    }
    return true;
}
