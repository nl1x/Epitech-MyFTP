/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** QuitCommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef QUITCOMMAND_HPP
    #define QUITCOMMAND_HPP
    #include "abstract/ACommand.hpp"

namespace ftp
{   
    class QuitCommand final : public ACommand
    {
        public:
            explicit QuitCommand(Server &server);
        protected:
            bool run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args) override;
    };
}

#endif //QUITCOMMAND_HPPb
