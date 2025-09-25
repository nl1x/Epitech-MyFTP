/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PasvCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <sstream>
#include "commands/PasvCommand.hpp"

#include <iostream>

ftp::PasvCommand::PasvCommand(Server& server):
    ACommand(server, "PASV", "Open data socket in passive mode.", {}, true)
{}

bool ftp::PasvCommand::run(const std::shared_ptr<Client> &executor, [[maybe_unused]] std::map<std::string, std::string> args)
{
    const int bookedPort = this->server_.bookPort();
    const std::string hostname = this->server_.getHostname();
    std::stringstream hstream(hostname);
    std::stringstream ip;

    std::string h1;
    std::string h2;
    std::string h3;
    std::string h4;
    int port1 = bookedPort / 256;
    int port2 = bookedPort % 256;

    getline(hstream, h1, '.');
    getline(hstream, h2, '.');
    getline(hstream, h3, '.');
    getline(hstream, h4, '.');

    ip << "(" << h1 << "," << h2 << "," << h3 << "," << h4 << "," << port1 << "," << port2 << ")";

    executor->openDataSocket(bookedPort);
    executor->send("227 Entering Passive Mode " + ip.str() + ".");
    return true;
}
