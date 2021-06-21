/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** winSystem.hpp
*/

#ifndef WINSYSTEM_HPP_
#define WINSYSTEM_HPP_

#include "ASystem.hpp"
#include "Life.hpp"

namespace ECS {
    class winSystem : public ASystem {
    public:
        winSystem(const std::shared_ptr<bool>& end);
        winSystem(const winSystem& other) = default;
        winSystem& operator=(const winSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        ~winSystem() = default;
    private:
        void createBonus(const Entity ent, ECS::ECSEngine& engine);
        std::shared_ptr<bool> _end;
    };
}

#endif /* !WINSYSTEM_HPP_ */
