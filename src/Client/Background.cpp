/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Background
*/

#include "Background.hpp"
#include <iostream>

Graphic::Background::Background(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, BACKGROUND, bonus, test, anime)
{
}

entityType Graphic::Background::getType() const
{
    return _type;
}