/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** ListCommand.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include "commands/ListCommand.hpp"
#include "file/File.hpp"
#include <unistd.h>
#include <filesystem>
#include <iostream>

ftp::ListCommand::ListCommand(Server& server):
    ACommand(server, "LIST", "List directories.", {
        CommandArgument("path", true, CommandArgument::STRING)
    }, true, true)
{}

// Pourquoi envoyer "150 Opening..." avant accept() ?
// Respect du protocole FTP : RFC 959 indique que le serveur doit signaler l’intention d’ouvrir la connexion avant d’attendre réellement la connexion du client.
// Éviter un blocage côté client : si le serveur attend avec accept() avant d’envoyer "150...", le client pourrait ne pas comprendre pourquoi la commande semble bloquée.
// Meilleure gestion des erreurs : si le client ne se connecte pas dans un délai raisonnable, le serveur peut envoyer une erreur (425 Can't open data connection).

bool ftp::ListCommand::run(const std::shared_ptr<Client>& executor, std::map<std::string, std::string> args)
{
    std::string path;
    std::stringstream data;

    const std::shared_ptr<DataSocket> dataSocket = executor->getDataSocket();

    if (args["path"].empty())
        path = executor->getRealWorkingDirectory();
    else if (args["path"].find('/') == 0)
        path = this->server_.getRootDirectory() + args["path"];
    else
        path = executor->getRealWorkingDirectory() + "/" + args["path"];

    try {
        File file(path);

        if (file.isDirectory()) {
            for (const auto &entry : std::filesystem::directory_iterator(path)) {
                File f(entry);
                data << f.getFileInfos();
            }
        } else
            data << file.getFileInfos();
    } catch ([[maybe_unused]] const File::FileNotFoundError &err) {
        executor->send("450 File not found.");
        return true;
    } catch (const std::exception &err) {
        std::cerr << "Error [" << path << "]:: " << err.what() << std::endl;
    }

    dataSocket->openConnection(executor);
    dataSocket->send(data.str());
    dataSocket->closeConnection(executor);
    return true;
}
