/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** CdupCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef CDUPCOMMAND_HPP
    #define CDUPCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class CdupCommand final : public ACommand
    {
    public:
        explicit CdupCommand(Server &server);
    protected:
        bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //CDUPCOMMAND_HPP
