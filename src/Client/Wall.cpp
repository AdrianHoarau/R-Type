/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.cpp
*/

#include "Wall.hpp"
#include <iostream>

Graphic::Wall::Wall(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, WALL, bonus, test, anime)
{
}

entityType Graphic::Wall::getType() const
{
    return _type;
}