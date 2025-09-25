/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Server.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef SERVER_HPP
    #define SERVER_HPP
    #define MAX_QUEUE_SIZE 10
    #define DEFAULT_PORT 4221
    #define PORT_RANGE_START 50000
    #define PORT_RANGE_END 60000
    #include <queue>
    #include <list>
    #include <memory>
    #include <unordered_map>
    #include "client/Client.hpp"
    #include "client/DataSocket.hpp"
    #include "manager/CommandManager.hpp"
    #include "socket/Socket.hpp"

namespace ftp
{
    inline volatile bool RUNNING = true;

    class Server final : public Socket
    {
        public:

            class SocketNotFoundError final : public Error
            {
                public:
                    explicit SocketNotFoundError(const std::string &msg) noexcept: Error(msg) {}
            };

            explicit Server(int port = -1, const std::string& root = ".");
            void closeConnection(const std::shared_ptr<Client> &socket);
            std::unordered_map<std::string, std::shared_ptr<ICommand>> getCommands();
            [[nodiscard]] std::string getRootDirectory() const;
            [[nodiscard]] int bookPort();
            void run();
        protected:
            void initSocket(int port);
            void initRootDirectory(const std::string& rootDir);
            void registerCommands();
        
            void handleClient(pollfd pollFd_);
            void handleClientBuffer(const std::shared_ptr<Client> &client);
            void handleServer(pollfd pollFd_);
        
            void dispatchActions(pollfd pollFd_);

            [[nodiscard]] std::vector<pollfd> getPollFds() const;
            [[nodiscard]] std::shared_ptr<Client> getSocketByPollFd(pollfd pollFd_) const;
        
            CommandManager commandManager_;
            std::string rootDirectory_;
            std::shared_ptr<Socket> serverSocket_;
            std::list<std::shared_ptr<Client>> sockets_;

        private:
            std::unordered_map<int, std::string> pollErrorMessages_;
            std::list<int> dataSocketUsedPorts_;
            static void handleStop(int signum);
            std::string getPollErrorMessage(int error);
            bool hasPollFailed(int error);
    };
}

#endif //SERVER_HPP
