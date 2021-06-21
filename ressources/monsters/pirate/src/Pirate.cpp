/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pirate.cpp
*/

#include "Pirate.hpp"

Pirate::Pirate() : AMonster(), _time(0), _speed(15), _value(0), _closest(-1), _boss(0, 0)
{

}

void Pirate::init(ECS::ECSEngine& engine)
{
    auto ent = engine.getNewEntity();

    _id = ent;
    engine.addComponent(ent, ECS::Position(rand() % 700 + 300, 0), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(0, 0), ECS::VELOCITY);
    engine.addComponent(ent, ECS::Dimensions(33, 34), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Life(5), ECS::LIFE);
    engine.addComponent(ent, ECS::entityDetails(entityType::PIRATE, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}

void Pirate::update(const float dt, ECS::ECSEngine& engine)
{
    std::map<unsigned int, ECS::Position> distance;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);


    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::P1 || details._type == entityType::P2 || details._type == entityType::P3 || details._type == entityType::P4) {
            _pPos.push_back(engine.getComponent<ECS::Position>(ent, ECS::POSITION));
        }
    }

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::PIRATE && ent == _id) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
            if (_time % (100 / _speed) == 0) {
                for (const auto& it: _pPos) {
                    _value = (it._x - pos._x) * (it._x - pos._x) + (it._y - pos._y) * (it._y - pos._y);
                    distance.insert(std::make_pair(_value, it));
                }
                for (auto& it: distance) {
                    if (it.first < _closest) {
                        _closest = it.first;
                        _boss = it.second;
                    }
                }
                if (_boss._x < pos._x) {
                    vel._vx = -1;
                    details._state = ANIMATION_0;
                }
                else if (_boss._x > pos._x) {
                    vel._vx = 1;
                    details._state = ANIMATION_3;
                } else
                    vel._vx = 0;

                if (_boss._y < pos._y)
                    vel._vy = -1;
                else if (_boss._y > pos._y)
                    vel._vy = 1;
                else
                    vel._vy = 0;
                _closest = -1;
                distance.clear();
            }
            if (_animation == 0) {
                details._state = static_cast<animationState>(static_cast<int>(details._state) + 1);
                if ((vel._vx < 0) && details._state == ANIMATION_2)
                    details._state = ANIMATION_0;
                else if ((vel._vx >= 0) && details._state == ANIMATION_5)
                    details._state = ANIMATION_3;
                _animation = 1;
            }
        }
    }
    if (_animation > 0)
        _animation++;
    if (_animation == 5)
        _animation = 0;
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::unique_ptr<Pirate>(new Pirate));
    }

#else

    extern "C" std::unique_ptr<IMonster> entryPoint()
    {
        return (std::make_unique<Pirate>());
    }

#endif
