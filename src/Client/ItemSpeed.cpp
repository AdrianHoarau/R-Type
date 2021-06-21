/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** itemSpeed.cpp
*/

#include "ItemSpeed.hpp"

Graphic::ItemSpeed::ItemSpeed(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, ITEMSPEED, bonus, test, anime)
{
    sf::IntRect rect(0, 0, 16, 16);

    _animation.insert(std::make_pair(ANIMATION_0, rect));
}

entityType Graphic::ItemSpeed::getType() const
{
    return _type;
}