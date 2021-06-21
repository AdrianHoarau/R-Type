/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include "IEntity.hpp"

class Parser {
    public:
        Parser(std::string configFilePath = "../../ressources/config_file.txt");
        Parser(const Parser& other) = default;
        Parser& operator=(const Parser& other) = default;
        bool openFile(std::string configFilePath);
        bool linkEntitiesToSprites();
        std::map<entityType, std::string> getPaths() const;
        ~Parser() = default;
    protected:
        std::ifstream _config;
        std::map<entityType, std::string> _paths;
        const std::map<std::string, entityType> _key {
        {"player1", entityType::P1},
        {"player2", entityType::P2},
        {"player3", entityType::P3},
        {"player4", entityType::P4},
        {"background", entityType::BACKGROUND},
        {"planete", entityType::WALL},
        {"meteorite", entityType::OBSTACLE},
        {"player_shoot", entityType::PLAYER_SHOOT},
        {"alien", entityType::ALIEN},
        {"alien_shoot", entityType::ALIEN_SHOOT},
        {"ufo", entityType::UFO},
        {"ufo_shoot", entityType::UFO_SHOOT},
        {"spaceship", entityType::SPACESHIP},
        {"spaceship_shoot", entityType::SPACESHIP_SHOOT},
        {"pirate", entityType::PIRATE},
        {"pirate_shoot", entityType::PIRATE_SHOOT},
        {"bomb", entityType::BOMB},
        {"item_speed", entityType::ITEMSPEED},
    };
};

#endif /* !PARSER_HPP_ */
