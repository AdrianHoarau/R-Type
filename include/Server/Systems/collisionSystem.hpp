/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** collisionSystem.hpp
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ASystem.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Dimensions.hpp"
#include "Life.hpp"
#include "entityDetails.hpp"
#include "Position.hpp"

using Position = ECS::Position;

namespace ECS {
    class collisionSystem : public ASystem {
    public:
        collisionSystem();
        collisionSystem(const collisionSystem& other) = default;
        collisionSystem& operator=(const collisionSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        ~collisionSystem() = default;
    private:
        void checkCollision(const Entity ent, std::vector<Entity>& entities, ECS::ECSEngine& engine, std::vector<entityType>& CollisionTypes);
        void createBomb(Position& pos, ECS::ECSEngine& engine);
        void looseHp(const Entity ent, const Entity obstacle, ECS::ECSEngine& engine);
        void destroyEntity(const Entity ent, const Entity obstacle, ECS::ECSEngine& engine);
        bool isPossibleCollision(const entityType type, std::vector<entityType>& types);
        bool isExplodable(const entityType type);
        Position findIntersection(const Position& playerPos, const Position& playerMaxpos, const Position& entPos, const Position& entMaxPos) const;
        void checkBonusCollision(const Entity ent, ECS::ECSEngine& engine);
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */
