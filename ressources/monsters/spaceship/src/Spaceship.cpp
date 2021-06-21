/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** spaceship.cpp
*/

#include "Spaceship.hpp"
#include <iostream>
#include <memory>
#include "entityDetails.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include "Life.hpp"
#include "Bomb.hpp"

Spaceship::Spaceship() : AMonster(), _time(0), _speed(5), _way(rand() % 2), _firstBuf(false), _secondBuf(false)
{

}

void Spaceship::init(ECS::ECSEngine& engine)
{
    auto ent = engine.getNewEntity();

    _id = ent;
    engine.addComponent(ent, ECS::Position(1116, rand() % 400 + 200), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(0, 0), ECS::VELOCITY);
    engine.addComponent(ent, ECS::Dimensions(65, 66), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Life(10), ECS::LIFE);
    engine.addComponent(ent, ECS::Bomb(), ECS::BOMB);
    engine.addComponent(ent, ECS::entityDetails(entityType::SPACESHIP, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}

void Spaceship::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::SPACESHIP && ent == _id) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
            auto& hp = engine.getComponent<ECS::Life>(ent, ECS::LIFE);
            if (hp._hp < 8 && _firstBuf == false) {
                _speed *= 2;
                _firstBuf = true;
            }
            if (hp._hp < 3 && _secondBuf == false) {
                _speed *= 2;
                _secondBuf = true;
            }
            if (_time % (100 / _speed) == 0) {
                if (pos._x >= 950)
                    vel._vx -= 1;
                else {
                    vel._vx = 0;
                    if (_way == true) {
                        if (pos._y < 700)
                            vel._vy = 1;
                        else {
                            _way = false;
                            vel._vy = 0;
                        }
                    } else {
                        if (pos._y > 30)
                            vel._vy = -1;
                        else {
                            _way = true;
                            vel._vy = 0;
                        }
                    }
                }
                if (_time % (1000 / _speed) == 0) {
                    createShoot(pos, engine);
                }
            }
            if (_animation == 0) {
                details._state = static_cast<animationState>(static_cast<int>(details._state) + 1);
                if (details._state == ANIMATION_5)
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

void Spaceship::createShoot(const ECS::Position& pos, ECS::ECSEngine& engine)
{
    Entity ent = engine.getNewEntity();
    engine.addComponent(ent, pos, ECS::POSITION);
    engine.addComponent(ent, ECS::Dimensions(50, 15), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Velocity(-3, 0), ECS::VELOCITY);
    engine.addComponent(ent, ECS::entityDetails(SPACESHIP_SHOOT, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
    engine.addComponent(ent, ECS::Bomb(), ECS::BOMB);
}

#if defined (_WIN32)

extern "C"  __declspec(dllexport)
void* entryPoint()
{
    return (new std::unique_ptr<Spaceship>(new Spaceship));
}

#else

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<Spaceship>());
}

#endif
