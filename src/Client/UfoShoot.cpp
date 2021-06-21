/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** UfoShoot
*/

#include "UfoShoot.hpp"
#include <iostream>

Graphic::UfoShoot::UfoShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, UFO_SHOOT, bonus, test, anime)
{
}

entityType Graphic::UfoShoot::getType() const
{
    return _type;
}
