/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AlienShoot
*/

#include "AlienShoot.hpp"
#include <iostream>

Graphic::AlienShoot::AlienShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, ALIEN_SHOOT, bonus, test, anime)
{
}

entityType Graphic::AlienShoot::getType() const
{
    return _type;
}