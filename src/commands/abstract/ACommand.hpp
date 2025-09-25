/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ACommand.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef ACOMMAND_HPP
    #define ACOMMAND_HPP
    #include "commands/argument/CommandArgument.hpp"
    #include "commands/interface/ICommand.hpp"
    #include "server/Server.hpp"

namespace ftp
{
    class ACommand : public ICommand
    {
        public:
            explicit ACommand(Server &server, std::string name, std::string description = "No description provided.", const std::list<CommandArgument> &args = {}, bool requireAuth = false, bool requireDataSocket = false);

            bool execute(const std::shared_ptr<Client>& executor, std::string command) override;
            [[nodiscard]] std::string getName() const override;
            [[nodiscard]] std::string getDescription() const override;
            [[nodiscard]] std::string getUsage() const override;
            [[nodiscard]] bool isAuthRequired() const override;
            [[nodiscard]] bool isDataSocketRequired() const override;

        protected:
            Server &server_;
            [[nodiscard]] static int toNumber(const std::string& str);
            [[nodiscard]] static bool isNumber(std::string str);
        private:

            const std::string name_m;
            const std::string description_m;
            const std::list<CommandArgument> args_definition_m;
            const bool requireAuth_m;
            const bool requireDataSocket_m;
    };
}

#endif //ACOMMAND_HPP
