/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** UserCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/
#ifndef USERCOMMAND_HPP
    #define USERCOMMAND_HPP
    #include "abstract/ACommand.hpp"

namespace ftp
{   
    class UserCommand final : public ACommand
    {
        public:
            explicit UserCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //USERCOMMAND_HPP
