/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pirate.hpp
*/

#ifndef PIRATE_HPP_
#define PIRATE_HPP_

#include "AMonster.hpp"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include "Life.hpp"
#include <map>
#include <vector>

class Pirate : public AMonster
{
    public:
        Pirate();
        Pirate(const Pirate& other) = default;
        Pirate& operator=(const Pirate& other) = default;
        void init(ECS::ECSEngine&);
        void update(const float dt, ECS::ECSEngine&);
        ~Pirate() = default;
    private:
    int _time;
    int _speed;
    std::vector<ECS::Position> _pPos;
    int _value;
    int _closest;
    ECS::Position _boss;
};

#endif /* !PIRATE_HPP_ */
