/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PlayerShoot
*/

#include "PlayerShoot.hpp"
#include <iostream>

Graphic::PlayerShoot::PlayerShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, PLAYER_SHOOT, bonus, test, anime)
{
    sf::IntRect rect(0, 0, 50, 15);

    _animation.insert(std::make_pair(ANIMATION_0, rect));
    rect.left += 50;
    _animation.insert(std::make_pair(ANIMATION_1, rect));
    rect.left += 50;
    _animation.insert(std::make_pair(ANIMATION_2, rect));
    rect.left += 50;
    _animation.insert(std::make_pair(ANIMATION_3, rect));
}

entityType Graphic::PlayerShoot::getType() const
{
    return _type;
}