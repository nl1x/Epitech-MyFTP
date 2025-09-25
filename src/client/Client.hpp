/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Client.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef CLIENT_HPP
    #define CLIENT_HPP
    #include "socket/Socket.hpp"
    #include "client/DataSocket.hpp"
    #include <memory>

namespace ftp
{
    class Client : public Socket
    {
        public:
            explicit Client(std::string workingDirectory);
            void setUsername(const std::string &username);
            [[nodiscard]] std::string getUsername();
            bool login(const std::string& password);
            [[nodiscard]] bool hasPendingCommands() const;
            [[nodiscard]] std::string getCommand() const;
            std::string nextCommand();
            [[nodiscard]] bool isLoggedIn() const;
            [[nodiscard]] bool changeWorkingDirectory(const std::string& path);
            [[nodiscard]] std::string getRealWorkingDirectory() const;
            [[nodiscard]] std::string getWorkingDirectory() const;
            [[nodiscard]] bool isDataSocketOpen() const;
            [[nodiscard]] pollfd getDataTransferPollFd() const;
            [[nodiscard]] std::shared_ptr<DataSocket> getDataSocket();
            void openDataSocket(std::string host, int port);
            void openDataSocket(int port);
        private:
            std::string username_;
            std::string command_;
            std::string workingDirectory_;
            std::string rootDirectory_;
            bool isLoggedIn_;
            std::shared_ptr<DataSocket> dataSocket_;
    };
}

#endif //CLIENT_HPP
