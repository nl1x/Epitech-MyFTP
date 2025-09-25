/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** DataSocket.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef DATASOCKET_HPP
    #define DATASOCKET_HPP
    #include <memory>
    #include "socket/Socket.hpp"

namespace ftp
{

    class Client;

    class DataSocket final : public Socket
    {
        enum ConnectionType
        {
            PASSIVE, ACTIVE
        };

        public:
            explicit DataSocket(std::string host, int port);
            explicit DataSocket(int port);
            void accept();
            void connect();
            void send(const std::string& data) const;
            [[nodiscard]] std::string read() const;
            void openConnection(const std::shared_ptr<Client> &executor);
            void closeConnection(const std::shared_ptr<Client> &executor);
        private:
            const std::string host_m;
            const int port_m;
            const ConnectionType mode_m;
            std::unique_ptr<Socket> connection_;
    };
}

#endif //DATASOCKET_HPP
