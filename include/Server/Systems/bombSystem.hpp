/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** bombSystem.hpp
*/

#ifndef BOMBSYSTEM_HPP_
#define BOMBSYSTEM_HPP_

#include "ASystem.hpp"
#include "entityDetails.hpp"

namespace ECS {
    class bombSystem : public ASystem {
    public:
        bombSystem();
        bombSystem(const bombSystem& other) = default;
        bombSystem& operator=(const bombSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        ~bombSystem() = default;
    private:
        void updateBomb(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details);
        void updateShoot(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details);
        void updateSpaceshipShoot(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details);
    };
}

#endif /* !BOMBSYSTEM_HPP_ */
