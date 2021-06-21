/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ufo.cpp
*/

#include "Ufo.hpp"
#include <iostream>
#include <memory>
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include "Life.hpp"

Ufo::Ufo() : AMonster(), _time(0), _speed(5), _zone(0), _way(rand() % 2)
{

}

void Ufo::init(ECS::ECSEngine& engine)
{
    auto ent = engine.getNewEntity();

    _id = ent;
    engine.addComponent(ent, ECS::Position(1116, rand() % 700 + 100), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(0, 20), ECS::VELOCITY);
    engine.addComponent(ent, ECS::Dimensions(33, 37), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Life(1), ECS::LIFE);
    engine.addComponent(ent, ECS::entityDetails(entityType::UFO, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}

void Ufo::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::UFO && ent == _id) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
            if (_time % (100 / _speed) == 0) {
                vel._vx = -3;
                if (_way == false) {
                    if (_zone >= 50)
                        _way = true;
                    else {
                        vel._vy = 1;
                        _zone++;
                    }
                } else {
                    if (_zone <= - 50)
                        _way = false;
                    else {
                        vel._vy = -1;
                        _zone--;
                    }
                }
            }
            if (_animation == 0) {
                details._state = static_cast<animationState>(static_cast<int>(details._state) + 1);
                if (details._state == ANIMATION_9)
                    details._state = ANIMATION_0;
                _animation = 1;
            }
        }
    }
    if (_animation > 0)
        _animation++;
    if (_animation == 5)
        _animation = 0;
    _time++;
}

#if defined (_WIN32)

extern "C"  __declspec(dllexport)
void* entryPoint()
{
    return (new std::unique_ptr<Ufo>(new Ufo));
}

#else

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<Ufo>());
}

#endif
