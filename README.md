# MyFTP

MyFTP est une implémentation d'un serveur FTP en C++ réalisée dans le cadre du projet Epitech.  
Ce serveur respecte les principales commandes du protocole FTP et permet la gestion de multiples clients.

## Fonctionnalités

- Authentification utilisateur (USER, PASS)
- Navigation dans l'arborescence (CWD, CDUP, PWD)
- Transfert de fichiers (RETR, STOR, DELE)
- Listage de répertoires (LIST)
- Modes actif et passif (PORT, PASV)
- Commandes utilitaires (NOOP, HELP, QUIT, TYPE)

## Structure du projet

- `src/` : Contient l'ensemble du code source
    - `core/` : Logique principale du serveur
    - `server/` : Gestion du serveur FTP
    - `client/` : Gestion des clients et sockets de données
    - `commands/` : Implémentation des commandes FTP
    - `manager/` : Gestionnaire des commandes
    - `file/` : Gestion des fichiers
    - `socket/` : Abstraction des sockets
    - `error/` : Gestion des erreurs

## Compilation

Pour compiler le projet, utilisez la commande suivante :

```sh
make
```
L'exécutable généré sera nommé `myftp`.


Utilisation
Lancez le serveur avec :
```sh
./myftp <port> <path>
```
- `<port>`: Port d'écoute du serveur FTP
- `<path>`: Répertoire racine du serveur

# Auteurs
|                                                                                                                                    |
|:----------------------------------------------------------------------------------------------------------------------------------:|
| <a href="https://github.com/nl1x">**Nathan JEANNOT** <br><img src="https://avatars.githubusercontent.com/u/83085376?s=128&v4"></a> |
