/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Core.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "core/Core.hpp"

ftp::Core::Core(const int port, const std::string &root):
    server_(std::make_shared<Server>(port, root))
{}

std::shared_ptr<ftp::Server> ftp::Core::getServer()
{
    return server_;
}

void ftp::Core::run() const
{
    server_->run();
}
