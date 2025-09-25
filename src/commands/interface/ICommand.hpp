/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ICommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef ICOMMAND_HPP
    #define ICOMMAND_HPP
    #define FTP_EOF "\r\n"
    #define FTP_EOT 4
    #define FTP_EOF_USAGE "<CRLF>"
    #define FTP_NEW_LINE_START(code) code "- "
    #define FTP_NEW_LINE_END(code) code " "
    #include "client/Client.hpp"
    #include <memory>
    #include <map>
    #include <string>

namespace ftp
{
    class ICommand
    {
        public:
            virtual ~ICommand() = default;
            virtual bool execute(const std::shared_ptr<Client> &executor, std::string command) = 0;
            [[nodiscard]] virtual std::string getName() const = 0;
            [[nodiscard]] virtual std::string getDescription() const = 0;
            [[nodiscard]] virtual std::string getUsage() const = 0;
            [[nodiscard]] virtual bool isAuthRequired() const = 0;
            [[nodiscard]] virtual bool isDataSocketRequired() const = 0;
        protected:
            virtual bool run(const std::shared_ptr<Client> &executor, std::map<std::string, std::string> args) = 0;
    };
}

#endif //ICOMMAND_HPP
