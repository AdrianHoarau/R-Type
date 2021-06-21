/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** movementSystem.hpp
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ASystem.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Player.hpp"
#include "entityDetails.hpp"


namespace ECS {
    class movementSystem : public ASystem {
    public:
        movementSystem();
        movementSystem(const movementSystem& other) = default;
        movementSystem& operator=(const movementSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        ~movementSystem() = default;
    private:
        void applyPhysic(Position& pos, const Velocity& vel, const float dt);
        void applyPhysic(Position& pos, const Velocity& vel, entityDetails& details, Player& player);
        void manageAnimation(ECS::entityDetails& details, const ECS::currentMovement move);
    };
}

#endif /* !MOVEMENTSYSTEM_HPP_ */
