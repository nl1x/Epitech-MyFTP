/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Socket.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef SOCKET_HPP
    #define SOCKET_HPP
    #define READSIZE 1024
    #include "error/Error.hpp"
    #include <string>
    #include <poll.h>
    #include <netinet/in.h>

namespace ftp
{
    
    class Socket
    {
        public:
            class BindError final : public Error
            {
                public:
                    explicit BindError(const std::string &msg) noexcept: Error(msg) {}
            };

            class InvalidWrite final : public Error
            {
                public:
                    explicit InvalidWrite(const std::string &msg) noexcept: Error(msg) {}
            };

            class InvalidRead final : public Error
            {
                public:
                    explicit InvalidRead(const std::string &msg) noexcept: Error(msg) {}
            };

            explicit Socket(int fd = -1);
            ~Socket();
            Socket &operator=(const Socket &rhs);

            void send(const std::string& data) const;
            void sendRaw(const std::string& data) const;
            std::string read();
            void resetBuffer();

            [[nodiscard]] bool isBufferComplete() const;

            void setFileDescriptor(int fd);

            [[nodiscard]] std::string getBuffer() const;
            [[nodiscard]] int getFileDescriptor() const;
            [[nodiscard]] sockaddr_in &getAddressIn();
            sockaddr *getAddress();
            socklen_t *getAddressSize();
            [[nodiscard]] std::string getHostname();
            [[nodiscard]] int getPort();
            [[nodiscard]] pollfd &getPollFd();

        protected:
            sockaddr_in address_;
            socklen_t addressSize_;
            struct pollfd pollfd_;
            std::string buffer_;
            std::string sanitizedBuffer_;
        private:
            void sanitizeBuffer();
    };
}

#endif //SOCKET_HPP
