/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Socket.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <unistd.h>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket/Socket.hpp"
#include "server/Server.hpp"

ftp::Socket::Socket(const int fd):
    address_{},
    addressSize_{},
    pollfd_({
        .fd = fd == -1 ? socket(AF_INET, SOCK_STREAM, 0) : fd,
        0,
        0
    })
{}

ftp::Socket &ftp::Socket::operator=(const Socket& rhs)
{
    if (this == &rhs)
        return *this;
    this->address_ = rhs.address_;
    this->pollfd_ = rhs.pollfd_;
    this->addressSize_ = rhs.addressSize_;
    return *this;
}

void ftp::Socket::send(const std::string &data) const
{
    if (write(this->pollfd_.fd, (data + FTP_EOF).c_str(), (data.length() + 2) * sizeof(char)) == -1)
        throw InvalidWrite("Error while writing: " + std::string(strerror(errno)));
}

void ftp::Socket::sendRaw(const std::string &data) const
{
    if (write(this->pollfd_.fd, data.c_str(), data.length() * sizeof(char)) == -1)
        throw InvalidWrite("Error while writing: " + std::string(strerror(errno)));
}

void ftp::Socket::sanitizeBuffer()
{
    this->sanitizedBuffer_ = this->buffer_;
    if (this->buffer_.find(FTP_EOF) != std::string::npos)
        this->sanitizedBuffer_ = this->sanitizedBuffer_.replace(this->buffer_.find(FTP_EOF), 2, "\0");
    while (this->sanitizedBuffer_.find(FTP_EOT) != std::string::npos)
        this->sanitizedBuffer_ = this->sanitizedBuffer_.replace(this->buffer_.find(FTP_EOT), 1, "");
}

std::string ftp::Socket::read()
{
    const auto buffer = static_cast<char *>(malloc(sizeof(char) * READSIZE));
    size_t nread = 0;

    do {
        memset(buffer, 0, READSIZE);
        nread = ::read(this->pollfd_.fd, buffer, sizeof(char) * (READSIZE - 1));
        this->buffer_ += buffer;
    } while (nread >= READSIZE - 1);
    free(buffer);
    this->sanitizeBuffer();
    return this->sanitizedBuffer_;
}

void ftp::Socket::resetBuffer()
{
    this->buffer_ = this->buffer_.substr(this->buffer_.find(FTP_EOF) + 2);
}

bool ftp::Socket::isBufferComplete() const
{
    return *(this->buffer_.end() - 2) == '\r' && *(this->buffer_.end() - 1) == '\n';
}

void ftp::Socket::setFileDescriptor(const int fd)
{
    this->pollfd_.fd = fd;
}

std::string ftp::Socket::getBuffer() const
{
    return this->buffer_;
}

int ftp::Socket::getFileDescriptor() const
{
    return this->pollfd_.fd;
}

sockaddr *ftp::Socket::getAddress()
{
    return reinterpret_cast<struct sockaddr *>(&this->address_);
}

sockaddr_in &ftp::Socket::getAddressIn()
{
    return this->address_;
}

socklen_t *ftp::Socket::getAddressSize()
{
    this->addressSize_ = sizeof(this->getAddressIn());
    return &this->addressSize_;
}

std::string ftp::Socket::getHostname()
{
    return inet_ntoa(this->getAddressIn().sin_addr);
}

int ftp::Socket::getPort()
{
    return this->getAddressIn().sin_port;
}

pollfd &ftp::Socket::getPollFd()
{
    return this->pollfd_;
}

ftp::Socket::~Socket()
{
    close(this->pollfd_.fd);
}
