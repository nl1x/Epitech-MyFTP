/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** File.hpp
** Author: nathan.jeannot@epitech.eu
*/

#ifndef FILE_HPP
    #define FILE_HPP
    #define PRM_READ 0
    #define PRM_WRIT 1
    #define PRM_EXEC 2
    #include <string>
    #include "error/Error.hpp"
    #include <filesystem>

namespace ftp
{

    class File
    {

        public:
            class FileNotFoundError final : public Error
            {
                public:
                    explicit FileNotFoundError(const std::string &file) noexcept : Error("File not found: " + file) {};
            };

            class FilePermissionError final : public Error
            {
                public:
                    explicit FilePermissionError(const std::string &msg) noexcept : Error(msg) {};
            };

            explicit File(const std::string& path, bool createIfNotExists = false);
            explicit File(const std::filesystem::directory_entry &entry);
            void write(const std::string& content) const;
            bool hasPermission(int permission) const;
            [[nodiscard]] std::string read() const;
            [[nodiscard]] bool isDirectory() const;
            [[nodiscard]] std::string getAbsolutePath() const;
            [[nodiscard]] bool isInDirectory(const std::string& parentDir) const;
            [[nodiscard]] bool dele();
            [[nodiscard]] std::string getFileInfos() const;

        private:
            std::filesystem::directory_entry entry_;
            std::string absolutePath_;
            bool isDeleted_;
    };

}

#endif //FILE_HPP
