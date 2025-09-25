/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** CommandManager.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef COMMANDMANAGER_HPP
    #define COMMANDMANAGER_HPP
    #include <unordered_map>
    #include "commands/interface/ICommand.hpp"

namespace ftp
{
    class Server;
    
    class CommandManager
    {
        public:
            void registerCommand(const std::shared_ptr<ICommand> &command);
            std::shared_ptr<ICommand> getCommand(const std::string& name);
            std::unordered_map<std::string, std::shared_ptr<ICommand>> getCommands();
        private:
            std::unordered_map<std::string, std::shared_ptr<ICommand>> commands_m{};
    };
}

#endif //COMMANDMANAGER_HPP
