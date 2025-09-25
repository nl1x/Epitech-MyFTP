/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PortCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef PORTCOMMAND_HPP
    #define PORTCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class PortCommand final : public ACommand
    {
        public:
            explicit PortCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}


#endif //PORTCOMMAND_HPP
