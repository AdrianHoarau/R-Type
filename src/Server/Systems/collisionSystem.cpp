/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** collisionSystem.cpp
*/

#include "collisionSystem.hpp"
#include "ECSEngine.hpp"
#include "Bomb.hpp"
#include <iostream>

ECS::collisionSystem::collisionSystem() : ECS::ASystem()
{
}

void ECS::collisionSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    std::vector<entityType> playerCollisionTypes = {entityType::ALIEN_SHOOT, entityType::PIRATE, entityType::SPACESHIP, entityType::UFO, entityType::SPACESHIP_SHOOT};
    std::vector<entityType> playerShootCollisionTypes = {entityType::ALIEN_SHOOT, entityType::PIRATE, entityType::SPACESHIP, entityType::UFO, entityType::SPACESHIP_SHOOT};

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (engine.getStorage(ECS::PLAYER)->hasComponent(ent) == true) {
            checkCollision(ent, entities, engine, playerCollisionTypes);
            checkBonusCollision(ent, engine);
        } else if (details._type == PLAYER_SHOOT) {
            checkCollision(ent, entities, engine, playerShootCollisionTypes);
            if (engine.getComponent<ECS::Position>(ent, ECS::POSITION)._x >= 2000)
                details._toUpdate = false;
        }
    }
}

void ECS::collisionSystem::checkCollision(const Entity ent, std::vector<Entity>& entities, ECS::ECSEngine& engine, std::vector<entityType>& collisionTypes)
{
    auto& playerPos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
    auto& playerDim = engine.getComponent<ECS::Dimensions>(ent, ECS::DIMENSIONS);

    Position playerPosMax(playerPos._x + static_cast<int>(playerDim._x), playerPos._y + static_cast<int>(playerDim._y));
    int posXMax = 0;
    int posYMax = 0;
    for (auto obstacle = entities.begin(); obstacle != entities.end(); obstacle++) {
        if (engine.getStorage(ECS::PLAYER)->hasComponent(*obstacle) != true) {
            auto& pos = engine.getComponent<ECS::Position>(*obstacle, ECS::POSITION);
            auto& dim = engine.getComponent<ECS::Dimensions>(*obstacle, ECS::DIMENSIONS);
            auto& details = engine.getComponent<ECS::entityDetails>(*obstacle, ECS::ENTITY_DETAILS);
            if (isPossibleCollision(details._type, collisionTypes) == true && details._toUpdate == true) {
                posXMax = pos._x + static_cast<int>(dim._x);
                posYMax = pos._y + static_cast<int>(dim._y);
                Position interPos = findIntersection(playerPos, playerPosMax, pos, Position(posXMax, posYMax));
                if (interPos._x != -1) {
                    looseHp(ent, *obstacle, engine);
                    destroyEntity(ent, *obstacle, engine);
                    createBomb(interPos, engine);
                }
            }
        }
    }
}

bool ECS::collisionSystem::isPossibleCollision(const entityType type, std::vector<entityType>& types)
{
    for (auto& cType : types) {
        if (cType == type)
            return (true);
    }
    return (false);
}

void ECS::collisionSystem::looseHp(const Entity ent, const Entity obstacle, ECS::ECSEngine& engine)
{
    if (engine.getStorage(ECS::LIFE)->hasComponent(obstacle)) {
        auto& life = engine.getComponent<ECS::Life>(obstacle, ECS::LIFE);
        if (life._hp != 0)
            life._hp -= 1;
    }
    if (engine.getStorage(ECS::LIFE)->hasComponent(ent)) {
        auto& life = engine.getComponent<ECS::Life>(ent, ECS::LIFE);
        if (life._hp != 0)
            life._hp -= 1;
    }
}

void ECS::collisionSystem::destroyEntity(const Entity ent, const Entity obstacle, ECS::ECSEngine& engine)
{
    auto& detailsObs = engine.getComponent<ECS::entityDetails>(obstacle, ECS::ENTITY_DETAILS);
    auto& detailsEnt = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);

    if (isExplodable(detailsObs._type))
        detailsObs._toUpdate = false;
    if (isExplodable(detailsEnt._type))
        detailsEnt._toUpdate = false;
}

bool ECS::collisionSystem::isExplodable(const entityType type)
{
    if (type == entityType::SPACESHIP_SHOOT || type == entityType::PLAYER_SHOOT)
        return (true);
    return (false);
}

ECS::Position ECS::collisionSystem::findIntersection(const Position& playerPos, const Position& playerMaxpos, const Position& entPos, const Position& entMaxPos) const
{
    int x5 = std::max(playerPos._x, entPos._x);
    int y5 = std::max(playerPos._y, entPos._y);
    int x6 = std::min(playerMaxpos._x, entMaxPos._x);
    int y6 = std::min(playerMaxpos._y, entMaxPos._y);

    if (x5 > x6 || y5 > y6) {
        return (Position(-1, -1));
    }
    return (Position((x5 + x6) / 2, (y5 + y6) / 2));
}

void ECS::collisionSystem::createBomb(Position& pos, ECS::ECSEngine& engine)
{
    Entity ent = engine.getNewEntity();

    engine.addComponent(ent, pos, ECS::POSITION);
    engine.addComponent(ent, ECS::Bomb(), ECS::BOMB);
    engine.addComponent(ent, ECS::entityDetails(entityType::BOMB, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}

void ECS::collisionSystem::checkBonusCollision(const Entity ent, ECS::ECSEngine& engine)
{
    auto& playerPos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
    auto& playerVel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
    auto& playerDim = engine.getComponent<ECS::Dimensions>(ent, ECS::DIMENSIONS);

    Position playerPosMax(playerPos._x + static_cast<int>(playerDim._x), playerPos._y + static_cast<int>(playerDim._y));
    int posXMax = 0;
    int posYMax = 0;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    for (auto& enti : entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(enti, ECS::ENTITY_DETAILS);
        if (details._type == ITEMSPEED) {
            auto& pos = engine.getComponent<ECS::Position>(enti, ECS::POSITION);
            auto& dim = engine.getComponent<ECS::Dimensions>(enti, ECS::DIMENSIONS);
            posXMax = pos._x + static_cast<int>(dim._x);
            posYMax = pos._y + static_cast<int>(dim._y);
            Position interPos = findIntersection(playerPos, playerPosMax, pos, Position(posXMax, posYMax));
            if (interPos._x != -1) {
                details._toUpdate = false;
                playerVel._vx += 5;
                playerVel._vy += 5;
            }
        }
    }
}
