/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** PassCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef PASSCOMMAND_HPP
    #define PASSCOMMAND_HPP
    #include "abstract/ACommand.hpp"

namespace ftp
{   
    class PassCommand final : public ACommand
    {
    public:
        explicit PassCommand(Server &server);
    protected:
        bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //PASSCOMMAND_HPP
