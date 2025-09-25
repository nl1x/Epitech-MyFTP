/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PasvCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef PASVCOMMAND_HPP
    #define PASVCOMMAND_HPP
    #include "abstract/ACommand.hpp"

namespace ftp
{
    class PasvCommand final : public ACommand
    {
        public:
            explicit PasvCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //PASVCOMMAND_HPP
