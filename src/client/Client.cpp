/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Client.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "client/Client.hpp"
#include "commands/interface/ICommand.hpp"
#include "file/File.hpp"
#include <utility>

ftp::Client::Client(std::string workingDirectory):
    workingDirectory_(workingDirectory), rootDirectory_(std::move(workingDirectory)), isLoggedIn_(false), dataSocket_(nullptr)
{}

void ftp::Client::setUsername(const std::string& username)
{
    this->username_ = username;
}

std::string ftp::Client::getUsername()
{
    return this->username_;
}

bool ftp::Client::isLoggedIn() const
{
    return this->isLoggedIn_;
}

bool ftp::Client::login(const std::string &password)
{
    this->isLoggedIn_ = this->username_ == "Anonymous" && password.empty();
    return this->isLoggedIn_;
}

bool ftp::Client::changeWorkingDirectory(const std::string &path)
{
    std::string destinationPath;

    if (path.find('/') == 0)
        destinationPath = this->rootDirectory_ + path;
    else
        destinationPath = this->workingDirectory_ + "/" + path;

    try {
        const File file(destinationPath);

        if (!file.isInDirectory(this->rootDirectory_))
            return false;
        this->workingDirectory_ = file.getAbsolutePath();
    } catch (const File::FileNotFoundError &err) {
        return false;
    }
    return true;
}

std::string ftp::Client::getRealWorkingDirectory() const
{
    return this->workingDirectory_;
}

bool ftp::Client::hasPendingCommands() const
{
    return this->buffer_.find(FTP_EOF) != std::string::npos;
}

std::string ftp::Client::getCommand() const
{
    return this->command_;
}

std::string ftp::Client::nextCommand()
{
    const size_t end_position = this->buffer_.find(FTP_EOF);

    this->command_ = this->buffer_.substr(0, end_position);
    this->buffer_ = this->buffer_.substr(end_position + 2, this->buffer_.length() - end_position + 2);
    return this->command_;
}

std::string ftp::Client::getWorkingDirectory() const
{
    std::string workingDir = this->workingDirectory_.substr(this->workingDirectory_.find(this->rootDirectory_) == 0 ? this->rootDirectory_.length() : 0);

    if (workingDir.empty())
        workingDir = '/';
    return workingDir;
}

void ftp::Client::openDataSocket(std::string host, int port)
{
    this->dataSocket_ = std::make_shared<DataSocket>(host, port);
}

void ftp::Client::openDataSocket(int port)
{
    this->dataSocket_ = std::make_shared<DataSocket>(port);
}

bool ftp::Client::isDataSocketOpen() const
{
    return this->dataSocket_ != nullptr;
}

pollfd ftp::Client::getDataTransferPollFd() const
{
    if (!this->isDataSocketOpen())
        return pollfd{};
    return this->dataSocket_->getPollFd();
}

std::shared_ptr<ftp::DataSocket> ftp::Client::getDataSocket()
{
    return this->dataSocket_;
}
