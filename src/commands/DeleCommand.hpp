/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** DeleCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef DELECOMMAND_HPP
    #define DELECOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class DeleCommand final : public ACommand
    {
        public:
            explicit DeleCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //DELECOMMAND_HPP
