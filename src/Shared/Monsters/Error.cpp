/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Error.cpp
*/

#include "Error.hpp"

Error::Error(const std::string& err) : _message(err)
{
}

const char *Error::what() const noexcept
{
    return (_message.c_str());
}

ErrorDLLoader::ErrorDLLoader(const std::string& err) : Error(err)
{
}

ErrorArgs::ErrorArgs(const std::string& err) : Error(err)
{
}

ErrorNbArgs::ErrorNbArgs() : ErrorArgs("Error: wrong number of arguments.")
{
}

ErrorDirPath::ErrorDirPath() : ErrorArgs("Error: the path given as argument isn't a directory.")
{
}

ErrorNoMonsters::ErrorNoMonsters() : Error("Error: there is no monsters available.")
{
}

ErrorConfigPath::ErrorConfigPath(): ErrorArgs("Error: the file given as argument isn't valid.")
{
}

ECS::ErrorECS::ErrorECS(const std::string& err) : Error(err)
{
}

ECS::ErrorEntitiesNumber::ErrorEntitiesNumber() : ErrorECS("Error: invalid number of entities has been reached.")
{
}

/*Client_err::ErrorClientNetwork::ErrorClientNetwork() : ErrorClient("Error: ")
{
}*/