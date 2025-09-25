/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** HelpCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef HELPCOMMAND_HPP
    #define HELPCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{   
    class HelpCommand final : public ACommand
    {
    public:
        explicit HelpCommand(Server &server);
    protected:
        bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //HELPCOMMAND_HPP
