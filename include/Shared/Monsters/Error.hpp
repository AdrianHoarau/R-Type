/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Error.hpp
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <fstream>

class Error : public std::exception
{
    private:
        const std::string _message;

    public:
        Error(std::string const& message);
        Error(const Error& other) = default;
        const char *what() const noexcept override;
        Error& operator=(const Error& other) = default;
        ~Error() = default;
};

class ErrorDLLoader : public Error
{
    public:
        ErrorDLLoader(const std::string& err);
        ErrorDLLoader(const ErrorDLLoader& other) = default;
        ErrorDLLoader& operator=(const ErrorDLLoader& other) = default;
        ~ErrorDLLoader() = default;
};

class ErrorArgs : public Error
{
    public:
        ErrorArgs(const std::string& err);
        ErrorArgs(const ErrorArgs& other) = default;
        ErrorArgs& operator=(const ErrorArgs& other) = default;
        ~ErrorArgs() = default;
};

class ErrorNbArgs : public ErrorArgs
{
    public:
        ErrorNbArgs();
        ErrorNbArgs(const ErrorNbArgs& other) = default;
        ErrorNbArgs& operator=(const ErrorNbArgs& other) = default;
        ~ErrorNbArgs() = default;
};

class ErrorDirPath : public ErrorArgs
{
    public:
        ErrorDirPath();
        ErrorDirPath(const ErrorDirPath& other) = default;
        ErrorDirPath& operator=(const ErrorDirPath& other) = default;
        ~ErrorDirPath() = default;
};

class ErrorConfigPath : public ErrorArgs
{
    public:
        ErrorConfigPath();
        ErrorConfigPath(const ErrorConfigPath& other) = default;
        ErrorConfigPath& operator=(const ErrorConfigPath& other) = default;
        ~ErrorConfigPath() = default;
};

class ErrorNoMonsters : public Error
{
    public:
        ErrorNoMonsters();
        ErrorNoMonsters(const ErrorNoMonsters& other) = default;
        ErrorNoMonsters& operator=(const ErrorNoMonsters& other) = default;
        ~ErrorNoMonsters() = default;
};

namespace ECS {

    class ErrorECS : public Error
    {
        public:
            ErrorECS(const std::string&);
            ErrorECS(const ErrorECS& other) = default;
            ErrorECS& operator=(const ErrorECS& other) = default;
            ~ErrorECS() = default;
    };

    class ErrorEntitiesNumber : public ErrorECS
    {
        public:
            ErrorEntitiesNumber();
            ErrorEntitiesNumber(const ErrorEntitiesNumber& other) = default;
            ErrorEntitiesNumber& operator=(const ErrorEntitiesNumber& other) = default;
            ~ErrorEntitiesNumber() = default;
    };
}
#endif /*ERROR_HPP_*/