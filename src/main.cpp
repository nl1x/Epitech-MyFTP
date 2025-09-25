/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** main.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <string>
#include <sstream>
#include <iostream>
#include "core/Core.hpp"

int handleServer(char **av)
{
    std::stringstream s(av[1]);
    int port = 0;

    s >> port;
    if (port <= 0 || port > 65535) {
        std::cerr << "Invalid port: " << av[1] << std::endl;
        return 84;
    }

    try {
        const ftp::Core core(port, av[2]);
        core.run();
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 84;
    }
    return 0;
}

int showHelpMessage()
{
    std::cout << "USAGE: ./myftp port path" << std::endl;
    std::cout << "\tport is the port number on which the server socket listens" << std::endl;
    std::cout << "\tpath is the path to the home directory for the Anonymous user" << std::endl;
    return 0;
}

int main(const int ac, char **av)
{
    if (ac <= 1 || ac != 3)
        return showHelpMessage() ^ 84;
    if (std::string(av[1]) == "-help")
        return showHelpMessage();
    return handleServer(av);
}
