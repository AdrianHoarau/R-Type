/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** monsterSystem.hpp
*/


#ifndef MONSTERSYSTEM_HPP_
#define MONSTERSYSTEM_HPP_

#include "ASystem.hpp"
#include "DLLoader.hpp"
#include "AMonster.hpp"

namespace ECS {
    class monsterSystem : public ASystem {
    public:
        monsterSystem(const std::string& libPath);
        monsterSystem(const monsterSystem& other) = default;
        monsterSystem& operator=(const monsterSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        ~monsterSystem() = default;
    private:
        std::unique_ptr<DLLoader>& selectRandomMonster();
        std::unique_ptr<DLLoader>& selectUfoMonster();
        std::unique_ptr<DLLoader>& selectPirateMonster();
        std::unique_ptr<DLLoader>& selectSpaceShipMonster();
        std::vector<std::unique_ptr<DLLoader>> _loaders;
        std::vector<std::unique_ptr<IMonster>> _monsters;
    };
}

#endif /* !MONSTERSYSTEM_HPP_ */
