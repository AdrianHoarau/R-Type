/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** winSystem.cpp
*/

#include "winSystem.hpp"
#include "ECSEngine.hpp"
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include <iostream>

ECS::winSystem::winSystem(const std::shared_ptr<bool>& end) : ECS::ASystem(), _end(end)
{
}

void ECS::winSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::LIFE), engine.getEntites());

    for (auto& ent : entities) {
        if (engine.getComponent<ECS::Life>(ent, ECS::LIFE)._hp <= 0) {
            auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
            details._toUpdate = false;
            if (details._type == entityType::SPACESHIP)
                createBonus(ent, engine);
        }
    }
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::PLAYER), engine.getEntites());
    if (entities.size() <= 0) {
        *_end = true;
        return;
    }
}

void ECS::winSystem::createBonus(const Entity ent, ECS::ECSEngine& engine)
{
    auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
    auto enti = engine.getNewEntity();

    engine.addComponent(enti, pos, ECS::POSITION);
    engine.addComponent(enti, ECS::Dimensions(16, 16), ECS::DIMENSIONS);
    engine.addComponent(enti, ECS::entityDetails(ITEMSPEED, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}