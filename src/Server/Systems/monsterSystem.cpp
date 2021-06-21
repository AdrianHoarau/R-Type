/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** monsterSystem.cpp
*/

#include "monsterSystem.hpp"
#include "dirReader.hpp"
#include <memory>

ECS::monsterSystem::monsterSystem(const std::string& libPath)
{
    dirReader dir(libPath);
    std::vector<std::string> pathToDLL = dir.findLibraries();

    for (auto& path : pathToDLL) {
        _loaders.push_back(std::unique_ptr<DLLoader>{new DLLoader(path)});
    }
}

std::unique_ptr<DLLoader>& ECS::monsterSystem::selectRandomMonster()
{
    int toLoad = rand() % _loaders.size();

    return (_loaders.at(toLoad));
}

std::unique_ptr<DLLoader>& ECS::monsterSystem::selectUfoMonster()
{
    return (_loaders.at(0));
}

std::unique_ptr<DLLoader>& ECS::monsterSystem::selectPirateMonster()
{
    return (_loaders.at(1));
}

std::unique_ptr<DLLoader>& ECS::monsterSystem::selectSpaceShipMonster()
{
    return (_loaders.at(2));
}

void ECS::monsterSystem::update(const float dt, ECS::ECSEngine& engine)
{
    static unsigned int creationTimer = 0;
    static unsigned int lap = 0;
    static unsigned int step = 1;
    static unsigned int speed = 150;

    creationTimer++;
    if ((creationTimer % speed) == 0) {
        if (lap == 0) {
            if (step == 2) {
                step = 0;
                lap++;
            }
            step++;
        } else if (lap == 1) {
            if (step == 6) {
                step = 0;
                lap++;
            }
            step++;
            _monsters.push_back(selectUfoMonster()->getInstance<IMonster>("entryPoint"));
            _monsters.back()->init(engine);
        } else if (lap == 2) {
            if (step == 6) {
                step = 0;
                lap++;
                _monsters.push_back(selectSpaceShipMonster()->getInstance<IMonster>("entryPoint"));
                _monsters.back()->init(engine);
            }
            step++;
            _monsters.push_back(selectPirateMonster()->getInstance<IMonster>("entryPoint"));
            _monsters.back()->init(engine);
        } else {
            speed = 50;
            _monsters.push_back(selectRandomMonster()->getInstance<IMonster>("entryPoint"));
            _monsters.back()->init(engine);
        }
    }
    for (auto& monster : _monsters) {
        monster->update(dt, engine);
    }
}