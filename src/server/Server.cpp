/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Server.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <memory>
#include <utility>
#include <poll.h>
#include <csignal>
#include <random>
#include <algorithm>
#include <climits>
#include "commands/QuitCommand.hpp"
#include "commands/UserCommand.hpp"
#include "commands/PassCommand.hpp"
#include "commands/NoopCommand.hpp"
#include "commands/HelpCommand.hpp"
#include "commands/CwdCommand.hpp"
#include "commands/CdupCommand.hpp"
#include "commands/PwdCommand.hpp"
#include "commands/DeleCommand.hpp"
#include "commands/PasvCommand.hpp"
#include "commands/ListCommand.hpp"
#include "commands/TypeCommand.hpp"
#include "commands/StorCommand.hpp"
#include "commands/RetrCommand.hpp"
#include "commands/PortCommand.hpp"
#include "server/Server.hpp"
#include "core/Core.hpp"
#include "file/File.hpp"

ftp::Server::Server(const int port, const std::string &root):
    pollErrorMessages_({
        { TIMEOUT, "Poll timed out" },
        { SYSERR, "poll failed" },
        { 0, "" },
    })
{
    this->initRootDirectory(root);
    this->initSocket(port);
    this->registerCommands();
}

// ==============================
// ===          INIT          ===
// ==============================

void ftp::Server::initSocket(const int port)
{
    this->serverSocket_ = std::make_shared<Socket>(*this);
    this->address_.sin_family = AF_INET; // AF_INET = IPv4
    this->address_.sin_port = htons(port); // htons convert the machine byte order to the network byte order
    this->address_.sin_addr.s_addr = INADDR_ANY; // To listen to every ip addresses

    this->serverSocket_->getPollFd().events = POLLIN; // Init server pollfd revents to POLLIN by default

    if (bind(this->pollfd_.fd, this->getAddress(), sizeof(this->address_)) == -1)
        throw BindError("An error occurred while binding the server: " + std::string(strerror(errno)));
    listen(this->pollfd_.fd, MAX_QUEUE_SIZE);
}

void ftp::Server::initRootDirectory(const std::string &rootDir)
{
    try {
        const File file(rootDir);

        if (!file.isDirectory())
            throw File::FileNotFoundError(rootDir);
        this->rootDirectory_ = file.getAbsolutePath();
    } catch ([[maybe_unused]] const File::FileNotFoundError &err) {
        throw InvalidPathError(rootDir);
    }
}

void ftp::Server::registerCommands()
{
    this->commandManager_.registerCommand(std::make_shared<QuitCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<UserCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<PassCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<NoopCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<HelpCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<CwdCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<CdupCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<PwdCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<DeleCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<PasvCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<ListCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<TypeCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<StorCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<RetrCommand>(*this));
    this->commandManager_.registerCommand(std::make_shared<PortCommand>(*this));
}

// ==============================
// ===         GLOBAL         ===
// ==============================

void ftp::Server::run()
{
    std::srand(time(nullptr));
    std::vector<pollfd> pollFds;
    int selectedPolls = 0;

    while (ftp::RUNNING) {
        pollFds = this->getPollFds();
        selectedPolls = poll(pollFds.data(), pollFds.size(), -1);
        if (hasPollFailed(selectedPolls))
            errExit(getPollErrorMessage(selectedPolls).c_str());
        for (const auto &clientPollFd : pollFds)
            this->dispatchActions(clientPollFd);
        std::signal(SIGINT, handleStop);
    }
}

int ftp::Server::bookPort()
{
    const float randomValue = static_cast<float>(random() % INT_MAX) / RAND_MAX;
    int randomPort = static_cast<int>(randomValue * (PORT_RANGE_END - PORT_RANGE_START) + PORT_RANGE_START);
    auto portFinderIter = std::find(this->dataSocketUsedPorts_.begin(), this->dataSocketUsedPorts_.end(), randomPort);

    while (portFinderIter != this->dataSocketUsedPorts_.end()) {
        randomPort = (randomPort + 1) % PORT_RANGE_END + PORT_RANGE_START;
        portFinderIter = std::find(this->dataSocketUsedPorts_.begin(), this->dataSocketUsedPorts_.end(), randomPort);
    }
    this->dataSocketUsedPorts_.push_back(randomPort);
    return randomPort;
}

void ftp::Server::closeConnection(const std::shared_ptr<Client>& socket)
{
    this->sockets_.remove(socket);
}

std::string ftp::Server::getRootDirectory() const
{
    return this->rootDirectory_;
}


// ==============================
// ===        INTERNAL        ===
// ==============================

void ftp::Server::handleStop(int signum)
{
    if (signum == SIGINT)
        ftp::RUNNING = false;
}

std::string ftp::Server::getPollErrorMessage(const int error)
{
    const auto &pollError = this->pollErrorMessages_.find(error);

    if (pollError == this->pollErrorMessages_.end())
        return "";
    return pollError->second;
}

bool ftp::Server::hasPollFailed(const int error)
{
    const auto &pollError = this->pollErrorMessages_.find(error);
    return pollError != this->pollErrorMessages_.end();
}

// ==============================
// ===        HANDLERS        ===
// ==============================

void ftp::Server::dispatchActions(const struct pollfd pollFd_)
{
    if (pollFd_.revents == 0) // No action to handle
        return;
    if (pollFd_.fd == this->pollfd_.fd)
        handleServer(pollFd_);
    else
        handleClient(pollFd_);
}

void ftp::Server::handleServer(const struct pollfd pollFd_)
{
    int newClientFd = -1;

    if (pollFd_.revents == POLLIN) {
        const auto client = std::make_shared<Client>(this->rootDirectory_);
        newClientFd = accept(this->pollfd_.fd, client->getAddress(), client->getAddressSize());
        if (newClientFd == -1)
            return;
        client->setFileDescriptor(newClientFd);
        client->getPollFd().events = POLLIN;
        this->sockets_.push_back(client);
        client->send("220 Connection established.");
    }
}

void ftp::Server::handleClient(const struct pollfd pollFd_)
{
    const auto client = this->getSocketByPollFd(pollFd_);

    if (pollFd_.revents & POLLHUP) {
        this->sockets_.remove(client);
    } else if (pollFd_.revents & POLLERR) {
        std::cerr << "error" << std::endl;
    } else {
        this->handleClientBuffer(client);
    }
}

void ftp::Server::handleClientBuffer(const std::shared_ptr<Client> &client)
{
    client->read();

    // if (!client->isBufferComplete()) {
    if (!client->hasPendingCommands()) {
        if (client->getBuffer().empty())
            this->sockets_.remove(client);
        return;
    }

    while (client->hasPendingCommands()) {
        try {
            std::stringstream s(client->nextCommand());
            std::string cmd;

            s >> cmd;
            this->commandManager_.getCommand(cmd)->execute(client, client->getCommand());
        } catch ([[maybe_unused]] const CommandNotFoundError &err) {
            client->send("500 Syntax error, command unrecognized.");
        } catch ([[maybe_unused]] const InvalidCommandArgumentError &err) {
            client->send("501 Syntax error in parameters or arguments.");
        }
        // client->resetBuffer();
    }
}

// ==============================
// ===         GETTER         ===
// ==============================

std::vector<pollfd> ftp::Server::getPollFds() const
{
    std::vector<pollfd> pollfds;

    pollfds.push_back(this->serverSocket_->getPollFd());
    for (const auto &client : this->sockets_)
        pollfds.push_back(client->getPollFd());
    return pollfds;
}

std::shared_ptr<ftp::Client> ftp::Server::getSocketByPollFd(const pollfd pollFd_) const
{
    for (auto client : this->sockets_)
        if (client->getPollFd().fd == pollFd_.fd)
            return client;
    throw SocketNotFoundError(std::string(__FUNCTION__) + " -> No socket has been found.");
}

std::unordered_map<std::string, std::shared_ptr<ftp::ICommand>> ftp::Server::getCommands()
{
    return this->commandManager_.getCommands();
}

