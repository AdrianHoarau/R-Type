/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Spaceship
*/

#include "Spaceship.hpp"
#include <iostream>

Graphic::Spaceship::Spaceship(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, SPACESHIP, bonus, test, anime)
{
    sf::IntRect rect(0, 0, 65, 66);

    _animation.insert(std::make_pair(ANIMATION_0, rect));
    rect.left += 65;
    _animation.insert(std::make_pair(ANIMATION_1, rect));
    rect.left += 65;
    _animation.insert(std::make_pair(ANIMATION_2, rect));
    rect.left += 65;
    _animation.insert(std::make_pair(ANIMATION_3, rect));
    rect.left += 65;
    _animation.insert(std::make_pair(ANIMATION_4, rect));
}

entityType Graphic::Spaceship::getType() const
{
    return _type;
}
