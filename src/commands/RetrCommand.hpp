/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** RetrCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef RETRCOMMAND_HPP
    #define RETRCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class RetrCommand final : public ACommand
    {
        public:
            explicit RetrCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //RETRCOMMAND_HPP
