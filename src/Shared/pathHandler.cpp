/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pathHandler.cpp
*/

#include "pathHandler.hpp"
#include "boost/filesystem.hpp"

pathHandler::pathHandler(const pathType& type)
{
    if (type == pathType::REGULAR_FILE)
        _path = "../config.txt";
    else
        _path = "./lib/";
}

bool pathHandler::isDirValid() const
{
    return (boost::filesystem::is_directory(_path));
}

bool pathHandler::isFileValid() const
{
    return (boost::filesystem::is_regular_file(_path));
}

void pathHandler::setPath(const std::string& path)
{
    _path = path;
}

std::string pathHandler::getPath() const
{
    return (_path);
}