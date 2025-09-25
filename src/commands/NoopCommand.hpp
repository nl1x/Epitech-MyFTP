/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** NoopCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef NOOPCOMMAND_HPP
    #define NOOPCOMMAND_HPP
    #include "abstract/ACommand.hpp"

namespace ftp
{   
    class NoopCommand final : public ACommand
    {
    public:
        explicit NoopCommand(Server &server);
    protected:
        bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //NOOPCOMMAND_HPP
