/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.cpp
*/

#include "Player.hpp"

Graphic::Player::Player(int id, const entityType& type, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, type, bonus, test, anime)
{
    sf::IntRect rect(0, 0, 33.2, 20);

    _animation.insert(std::make_pair(ANIMATION_1, rect));
    rect.left += 33.2;
    _animation.insert(std::make_pair(ANIMATION_2, rect));
    rect.left += 33.2;
    _animation.insert(std::make_pair(ANIMATION_0, rect));
    rect.left += 33.2;
    _animation.insert(std::make_pair(ANIMATION_3, rect));
    rect.left += 33.2;
    _animation.insert(std::make_pair(ANIMATION_4, rect));
}

entityType Graphic::Player::getType() const
{
    return _type;
}