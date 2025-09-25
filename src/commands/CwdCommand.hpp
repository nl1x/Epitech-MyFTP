/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ChangeWorkingDirectoryCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef CHANGEWORKINGDIRECTORYCOMMAND_HPP
    #define CHANGEWORKINGDIRECTORYCOMMAND_HPP
    #include "commands/abstract/ACommand.hpp"

namespace ftp
{
    class CwdCommand final : public ACommand
    {
        public:
            explicit CwdCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //CHANGEWORKINGDIRECTORYCOMMAND_HPP
