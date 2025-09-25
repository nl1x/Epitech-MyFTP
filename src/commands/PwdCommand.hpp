/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PwdCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef PWDCOMMAND_HPP
    #define PWDCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class PwdCommand final : public ACommand
    {
        public:
            explicit PwdCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //PWDCOMMAND_HPP
