/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** TypeCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef TYPECOMMAND_HPP
    #define TYPECOMMAND_HPP
    #include "abstract/ACommand.hpp"

namespace ftp
{
    class TypeCommand final : public ACommand
    {
    public:
        explicit TypeCommand(Server &server);
    protected:
        bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //TYPECOMMAND_HPP
