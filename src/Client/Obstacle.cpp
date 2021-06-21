/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Obstacle
*/

#include "Obstacle.hpp"
#include <iostream>

Graphic::Obstacle::Obstacle(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, OBSTACLE, bonus, test, anime)
{
}

entityType Graphic::Obstacle::getType() const
{
    return _type;
}