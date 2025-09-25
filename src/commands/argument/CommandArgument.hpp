/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** IArgument.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef IARGUMENT_HPP
    #define IARGUMENT_HPP
    #include <string>

namespace ftp
{
    class CommandArgument
    {
        public:

            enum ArgType
            {
                INT, STRING
            };

            explicit CommandArgument(std::string name, bool isOptional, ArgType type);
            [[nodiscard]] std::string getName() const;
            [[nodiscard]] ArgType getType() const;
            [[nodiscard]] bool isOptional() const;

        private:
            const std::string name_m;
            const bool optional_m;
            const ArgType type_m;
    };

}

#endif //IARGUMENT_HPP
