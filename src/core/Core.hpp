/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Core.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef CORE_HPP
    #define CORE_HPP
    #define ERROR 84
    #define SYSERR (-1)
    #define TIMEOUT 0
    #define SUCCESS 0
    #define errExit(msg) do { perror(msg); exit(ERROR); } while (0)
    #include "server/Server.hpp"

namespace ftp
{
    class Core
    {
        public:
            explicit Core(int port, const std::string& root);
            void run() const;
            std::shared_ptr<Server> getServer();
        
        private:
            std::shared_ptr<Server> server_;
    };
}

#endif //CORE_HPP
