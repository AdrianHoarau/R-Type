/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** bombSystem.cpp
*/

#include "bombSystem.hpp"
#include "ECSEngine.hpp"
#include "Bomb.hpp"
#include <iostream>

ECS::bombSystem::bombSystem() : ECS::ASystem()
{
}

void ECS::bombSystem::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::BOMB)
            updateBomb(dt, ent, engine, details);
        else if (details._type == entityType::PLAYER_SHOOT)
            updateShoot(dt, ent, engine, details);
        else if (details._type == entityType::SPACESHIP_SHOOT)
            updateSpaceshipShoot(dt, ent, engine, details);
    }
}

void ECS::bombSystem::updateBomb(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details)
{
    auto& bomb = engine.getComponent<ECS::Bomb>(ent, ECS::BOMB);

    bomb._dt += dt;
    if (bomb._dt >= 60 && bomb._dt < 120)
        details._state = animationState::ANIMATION_1;
    else if (bomb._dt >= 120 && bomb._dt < 180)
        details._state = animationState::ANIMATION_2;
    else if (bomb._dt >= 180 && bomb._dt < 240)
        details._state = animationState::ANIMATION_3;
    else if (bomb._dt >= 240 && bomb._dt < 300)
        details._state = animationState::ANIMATION_4;
    else if (bomb._dt >= 360 && bomb._dt < 420)
        details._state = animationState::ANIMATION_5;
    else if (bomb._dt >= 480) {
        details._toUpdate = false;
    }
}

void ECS::bombSystem::updateShoot(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details)
{
    auto& bomb = engine.getComponent<ECS::Bomb>(ent, ECS::BOMB);

    bomb._dt += dt;
    if (bomb._dt >= 300 && bomb._dt < 600)
        details._state = animationState::ANIMATION_1;
    else if (bomb._dt >= 600 && bomb._dt < 900)
        details._state = animationState::ANIMATION_2;
    else if (bomb._dt >= 900) {
        details._state = animationState::ANIMATION_3;
    }
}

void ECS::bombSystem::updateSpaceshipShoot(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details)
{
    auto& bomb = engine.getComponent<ECS::Bomb>(ent, ECS::BOMB);

    bomb._dt += dt;
    if (bomb._dt >= 150 && bomb._dt < 300)
        details._state = animationState::ANIMATION_1;
    else if (bomb._dt >= 300 && bomb._dt < 450)
        details._state = animationState::ANIMATION_2;
    else if (bomb._dt >= 450 && bomb._dt < 600)
        details._state = animationState::ANIMATION_3;
    else if (bomb._dt >= 600 && bomb._dt < 750)
        details._state = animationState::ANIMATION_4;
    else if (bomb._dt >= 750)
        details._state = animationState::ANIMATION_5;
}