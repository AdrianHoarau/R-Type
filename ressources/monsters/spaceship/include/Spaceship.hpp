/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** spaceship.hpp
*/

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "AMonster.hpp"
#include "Position.hpp"

class Spaceship : public AMonster
{
    public:
        Spaceship();
        Spaceship(const Spaceship& other) = default;
        Spaceship& operator=(const Spaceship& other) = default;
        void init(ECS::ECSEngine&);
        void update(const float dt, ECS::ECSEngine&);
        ~Spaceship() = default;
    private:
        void createShoot(const ECS::Position& pos, ECS::ECSEngine& engine);
        int _time;
        int _speed;
        bool _way;
        bool _firstBuf;
        bool _secondBuf;
};

#endif /* !SPACESHIP_HPP_ */
