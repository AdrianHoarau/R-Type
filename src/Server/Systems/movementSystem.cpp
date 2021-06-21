/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** movementSystem.cpp
*/

#include "movementSystem.hpp"
#include "ECSEngine.hpp"
#include <iostream>

ECS::movementSystem::movementSystem() : ECS::ASystem()
{
}

void ECS::movementSystem::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        if (engine.getStorage(ECS::PLAYER)->hasComponent(ent) == true)
            applyPhysic(engine.getComponent<ECS::Position>(ent, ECS::POSITION), engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY), engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS), engine.getComponent<ECS::Player>(ent, ECS::PLAYER));
        else
            applyPhysic(engine.getComponent<ECS::Position>(ent, ECS::POSITION), engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY), dt);
    }
}

void ECS::movementSystem::applyPhysic(ECS::Position& pos, const ECS::Velocity& vel, const float dt)
{
    (void)dt;
    pos._x += static_cast<int>(vel._vx);
    pos._y += static_cast<int>(vel._vy);
}

void ECS::movementSystem::applyPhysic(ECS::Position& pos, const ECS::Velocity& vel, entityDetails& details, ECS::Player& player)
{
    static unsigned int pass = 0;

    switch (player._direction) {
        case ECS::UP:
            pos._y += static_cast<int>(vel._vy);
            break;
        case ECS::DOWN:
            pos._y -= static_cast<int>(vel._vy);
            break;
        case ECS::RIGHT:
            pos._x += static_cast<int>(vel._vx);
            break;
        case ECS::LEFT:
            pos._x -= static_cast<int>(vel._vx);
            break;
        case ECS::NONE:
            break;
    }
    if (pass == 5 || details._state == animationState::ANIMATION_0)
        manageAnimation(details, player._direction);
    pass++;
    player._direction = ECS::NONE;
    if (pass == 6)
        pass = 0;
}

void ECS::movementSystem::manageAnimation(ECS::entityDetails& details, const ECS::currentMovement move)
{
    if (move == ECS::NONE) {
        details._state = animationState::ANIMATION_0;
    } else if (move == ECS::DOWN) {
        if (details._state == animationState::ANIMATION_3)
            details._state = animationState::ANIMATION_4;
        else
            details._state = animationState::ANIMATION_3;
    } else {
        if (details._state == animationState::ANIMATION_1)
            details._state = animationState::ANIMATION_2;
        else
            details._state = animationState::ANIMATION_1;
    }
}