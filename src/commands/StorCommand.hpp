/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** StorCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef STORCOMMAND_HPP
    #define STORCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class StorCommand final : public ACommand
    {
        public:
            explicit StorCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //STORCOMMAND_HPP
