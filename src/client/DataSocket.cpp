/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** DataSocket.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <cstring>
#include <sstream>
#include <utility>
#include "server/Server.hpp"
#include "client/DataSocket.hpp"

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

ftp::DataSocket::DataSocket(std::string host, const int port):
    host_m(std::move(host)), port_m(port), mode_m(ACTIVE)
{}

ftp::DataSocket::DataSocket(const int port):
    port_m(port), mode_m(PASSIVE)
{
    this->address_.sin_family = AF_INET; // AF_INET = IPv4
    this->address_.sin_port = htons(port); // htons convert the machine byte order to the network byte order
    this->address_.sin_addr.s_addr = INADDR_ANY; // To listen to every ip addresses

    if (bind(this->pollfd_.fd, this->getAddress(), sizeof(this->address_)) == -1)
        throw BindError("An error occurred while binding the server: " + std::string(strerror(errno)));
    listen(this->pollfd_.fd, MAX_QUEUE_SIZE);
}

void ftp::DataSocket::connect()
{
    this->connection_ = std::make_unique<Socket>();
    this->connection_->getAddressIn().sin_family = AF_INET;
    this->connection_->getAddressIn().sin_addr.s_addr = inet_addr(this->host_m.c_str());
    this->connection_->getAddressIn().sin_port = htons(this->port_m);

    if (::connect(this->connection_->getFileDescriptor(), this->connection_->getAddress(), *this->connection_->getAddressSize()) == -1) {
        std::stringstream s("Cannot connect to " + this->host_m + ":");

        s << this->port_m << ".";
        throw ConnectionError(s.str());
    }
}

void ftp::DataSocket::accept()
{
    connection_ = std::make_unique<Socket>();
    const int newClientFd = ::accept(this->pollfd_.fd, connection_->getAddress(), connection_->getAddressSize());
    if (newClientFd == -1)
        return;
    connection_->setFileDescriptor(newClientFd);
    connection_->getPollFd().events = POLLIN;
}

std::string ftp::DataSocket::read() const
{
    return this->connection_->read();
}

void ftp::DataSocket::send(const std::string& data) const
{
    this->connection_->sendRaw(data);
}

void ftp::DataSocket::openConnection(const std::shared_ptr<Client> &executor)
{
    executor->send("150 Opening data connection...");
    if (this->mode_m == ACTIVE)
        this->connect();
    else
        this->accept();
}

void ftp::DataSocket::closeConnection(const std::shared_ptr<Client>& executor)
{
    this->connection_ = nullptr;
    executor->send("226 Transfer complete.");
}
