/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** Error.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef ERROR_HPP
    #define ERROR_HPP
    #include <string>

namespace ftp
{

    class Error : public std::exception
    {
        public:
            explicit Error(std::string msg) noexcept : _msg(std::move(msg)) {};
            [[nodiscard]] const char *what() const noexcept override { return this->_msg.data(); }
        private:
            std::string _msg;
    };

    class ConnectionError final : public Error
    {
        public:
            explicit ConnectionError(const std::string &msg) noexcept : Error("Connection error: " + msg) {};
    };

    class CommandNotFoundError final : public Error
    {
        public:
            explicit CommandNotFoundError(const std::string &msg) noexcept : Error("Command not found: " + msg) {};
    };

    class InvalidCommandArgumentError final : public Error
    {
        public:
            explicit InvalidCommandArgumentError(const std::string &command, const std::string &argument) noexcept : Error(
                "Invalid argument:\n\tCommand: " + command + "\n\tArgument: " + argument
            ) {};
    };

    class MissingArgumentError final : public Error
    {
        public:
            explicit MissingArgumentError(const std::string &command, const std::string &argument) noexcept : Error(
                "Missing argument:\n\tCommand: " + command + "\n\tArgument: " + argument
            ) {};
    };

    class InvalidPathError final : public Error
    {
        public:
            explicit InvalidPathError(const std::string &path) noexcept : Error("Directory not found: " + path) {};
    };

    class ForkError final : public Error
    {
        public:
            explicit ForkError(const std::string &msg) noexcept : Error("Fork failed: " + msg) {};
    };

}

#endif //ERROR_HPP
