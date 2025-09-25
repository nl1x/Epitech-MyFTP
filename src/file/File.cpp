/*
** EPITECH PROJECT, 2025
** FTP
** File description:
** File.cpp
** Author: nathan.jeannot@epitech.eu
*/

#include <sys/stat.h>
#include <filesystem>
#include "file/File.hpp"
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

ftp::File::File(const std::string &path, bool createIfNotExists): isDeleted_(false)
{
    char *absolutePath = realpath(path.c_str(), nullptr);

    if (!absolutePath) {
        if (createIfNotExists) {
            std::ofstream fileStream(path);
            absolutePath = realpath(path.c_str(), nullptr);
            fileStream.close();
        } else
            throw FileNotFoundError(path);
    }
    this->absolutePath_ = std::string(absolutePath);
    free(absolutePath);

    this->entry_ = std::filesystem::directory_entry(this->absolutePath_);
}

ftp::File::File(const std::filesystem::directory_entry &entry):
    File(entry.path())
{
    this->entry_ = entry;
}

std::string ftp::File::getAbsolutePath() const
{
    return this->absolutePath_;
}

bool ftp::File::isInDirectory(const std::string &parentDir) const
{
    return this->absolutePath_.find(parentDir) == 0;
}

bool ftp::File::isDirectory() const
{
    return std::filesystem::is_directory(this->absolutePath_);
}

bool ftp::File::dele()
{
    if (this->isDeleted_)
        throw FileNotFoundError(this->absolutePath_);

    if (std::remove(this->absolutePath_.c_str()) != 0)
        return false;
    this->isDeleted_ = true;
    return true;
}

void ftp::File::write(const std::string &content) const
{
    std::ofstream fileStream(this->getAbsolutePath());

    fileStream << content;
    fileStream.close();
}

std::string ftp::File::read() const
{
    if (access(this->absolutePath_.c_str(), R_OK) != 0)
        throw FilePermissionError("Missing permissions to read the file.");
    std::ifstream fileStream(this->getAbsolutePath());
    std::stringstream content;

    content << fileStream.rdbuf();
    return content.str();
}

bool ftp::File::hasPermission(const int permission) const
{
    return access(this->absolutePath_.c_str(), permission) == 0;
}

std::string ftp::File::getFileInfos() const
{
    std::stringstream data;

    const auto fileStats = entry_.status();
    const auto filePerms = fileStats.permissions();
    auto getPerm = [=](const char op, const std::filesystem::perms perm)
    {
        return (std::filesystem::perms::none == (perm & filePerms) ? '-' : op);
    };

    struct stat fs{};
    std::string owner_name;
    std::string group_name;

    if (lstat(this->entry_.path().c_str(), &fs) != -1) {
        const passwd *pwd = getpwuid(fs.st_uid);
        owner_name = std::string(pwd->pw_name);
        const struct group *grp = getgrgid(fs.st_gid);
        group_name = grp->gr_name;
    }

    std::filesystem::file_time_type tp = this->entry_.last_write_time();
    time_t secs = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
    char buff[1024] = { 0 };

    strftime(buff, 20, "%b %d %H:%M", localtime(&secs));

    data
        << (this->entry_.is_directory() ? "d" : "-")
        << getPerm('r', std::filesystem::perms::owner_read)
        << getPerm('w', std::filesystem::perms::owner_write)
        << getPerm('x', std::filesystem::perms::owner_exec)
        << getPerm('r', std::filesystem::perms::group_read)
        << getPerm('w', std::filesystem::perms::group_write)
        << getPerm('x', std::filesystem::perms::group_exec)
        << getPerm('r', std::filesystem::perms::others_read)
        << getPerm('w', std::filesystem::perms::others_write)
        << getPerm('x', std::filesystem::perms::others_exec)

        << " " << this->entry_.hard_link_count()
        << " " + owner_name
        << " " + group_name

        << " " << (this->entry_.is_directory() ? 4096 : this->entry_.file_size())
        << " " << buff
        << " " << this->entry_.path().filename().string()
        << std::endl;

    return data.str();
}

