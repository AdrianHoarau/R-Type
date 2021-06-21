/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** eventSystem.cpp
*/

#include "eventSystem.hpp"
#include "ECSEngine.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include "entityDetails.hpp"
#include "Bomb.hpp"
#include <iostream>
#include <cstring>

ECS::eventSystem::eventSystem(const std::shared_ptr<Buffer>& buffer) : ECS::ASystem(), _buffer(buffer)
{
    _moves.insert(std::make_pair("Up", ECS::currentMovement::UP));
    _moves.insert(std::make_pair("Down", ECS::currentMovement::DOWN));
    _moves.insert(std::make_pair("Left", ECS::currentMovement::LEFT));
    _moves.insert(std::make_pair("Right", ECS::currentMovement::RIGHT));
}

void ECS::eventSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::PLAYER), engine.getEntites());

    for (auto& ent : entities) {
        ECS::Player& player = engine.getComponent<ECS::Player>(ent, ECS::PLAYER);
        handleEvent(engine, ent, player);
    }
}

void ECS::eventSystem::handleEvent(ECS::ECSEngine& engine, const Entity entity, ECS::Player& player)
{
    std::string event("");
    static int shoot = 0;

    if (_buffer->isDataAvailable(player._uuid) == true) {
        auto& events = _buffer->getData(player._uuid);
        event = (events.front());
        if (std::strcmp(event.c_str(), "Off") == 0) {
            engine.getComponent<ECS::entityDetails>(entity, ECS::ENTITY_DETAILS)._toUpdate = false;
        } else if (std::strcmp(event.c_str(), "Shoot") == 0 && shoot == 0) {
            createShoot(engine, entity);
            shoot = 1;
        } else {
            for (auto it = _moves.begin(); it != _moves.end(); ++it)
                if (std::strcmp(event.c_str(), it->first.c_str()) == 0)
                    player._direction = it->second;
        }
        events.erase(events.begin());
    }
    if (shoot > 0)
        shoot++;
    if (shoot == 20)
        shoot = 0;
}

void ECS::eventSystem::createShoot(ECS::ECSEngine& engine, const Entity entity)
{
    ECS::Position& pos = engine.getComponent<ECS::Position>(entity, ECS::POSITION);
    Entity ent = engine.getNewEntity();
    engine.addComponent(ent, pos, ECS::POSITION);
    engine.addComponent(ent, ECS::Dimensions(50, 15), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Velocity(3, 0), ECS::VELOCITY);
    engine.addComponent(ent, ECS::entityDetails(PLAYER_SHOOT, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
    engine.addComponent(ent, ECS::Bomb(), ECS::BOMB);
}