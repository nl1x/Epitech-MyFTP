/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PortCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/PortCommand.hpp"
#include <sstream>

ftp::PortCommand::PortCommand(Server& server):
    ACommand(server, "PORT", "Open data socket in active mode.", {
        CommandArgument("host_port", false, CommandArgument::STRING)
    }, true)
{}

bool ftp::PortCommand::run(const std::shared_ptr<Client> &executor, std::map<std::string, std::string> args)
{
    std::stringstream stream(args["host_port"]);
    std::stringstream portStream;
    std::string garbage, h1, h2, h3, h4, p1, p2;
    std::string host;
    int port, port1, port2;

    getline(stream, h1, ',');
    getline(stream, h2, ',');
    getline(stream, h3, ',');
    getline(stream, h4, ',');
    getline(stream, p1, ',');
    getline(stream, p2, ',');

    if (!isNumber(h1) || !isNumber(h2) || !isNumber(h3) || !isNumber(h4) || !isNumber(p1) || !isNumber(p2)) {
        executor->send("501 Syntax error in parameters or arguments.");
        return true;
    }

    host = h1 + "." + h2 + "." + h3 + "." + h4;
    port1 = toNumber(p1);
    port2 = toNumber(p2);
    port = port1 * 256 + port2;

    executor->openDataSocket(host, port);
    executor->send("200 Okay.");
    return true;
}
