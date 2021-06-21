/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** dirReader.cpp
*/
#include "dirReader.hpp"
#include <iostream>
dirReader::dirReader(const std::string& name) : _path(name)
{
}
void dirReader::pushLibPath(const std::string& name, std::vector<std::string>& dirPaths)
{
    if (name.find(".so") || name.find(".lib") <= name.length())
        dirPaths.push_back(_path + '/' + name);
}
std::vector<std::string> dirReader::findLibraries()
{
    std::vector<std::string> dirPaths;
    boost::filesystem::directory_iterator iterator(boost::filesystem::path(_path.c_str()));
    for (; iterator != boost::filesystem::directory_iterator(); ++iterator) {
        pushLibPath(iterator->path().filename().string(), dirPaths);
    }
    if (dirPaths.empty() == true)
        throw ErrorNoMonsters();
    return (dirPaths);
}
