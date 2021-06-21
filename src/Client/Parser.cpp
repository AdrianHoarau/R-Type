/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(std::string configFilePath) :_config()
{
    if (!openFile(configFilePath)) {
        return;
    }
    if(!linkEntitiesToSprites()) {
        return;
    }
}

bool Parser::openFile(std::string configFilePath)
{
    _config.open(configFilePath);
    if (!_config) {
        std::cerr << "Error: Incorrect config file\n";
        return false;
    }
    return true;
}

bool Parser::linkEntitiesToSprites()
{
    std::string line(""), code(""), path("");

    while (std::getline(_config, line, '\n')) {
        if (line.find("=") != line.npos) {
            code = line.substr(0, line.find("="));
            path = line.substr(line.find("=") + 1, line.size() - line.find("=") - 2);
            if (_key.find(code) == std::end(_key)) {
                std::cerr << "Error config file: the tag doesn't exist\n";
                return false;
            }
            _paths.insert(std::pair<entityType, std::string>(_key.find(code)->second, path));
        }
    }
    return true;
}

std::map<entityType, std::string> Parser::getPaths() const
{
    return _paths;
}