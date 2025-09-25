/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ListCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef LISTCOMMAND_HPP
    #define LISTCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class ListCommand final : public ACommand
    {
        public:
            explicit ListCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //LISTCOMMAND_HPP
