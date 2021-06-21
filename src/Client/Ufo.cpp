/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Ufo
*/

#include "Ufo.hpp"
#include <iostream>

Graphic::Ufo::Ufo(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, UFO, bonus, test, anime)
{
    sf::IntRect rect(0, 0, 33, 37);

    _animation.insert(std::make_pair(ANIMATION_0, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_1, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_2, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_3, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_4, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_5, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_6, rect));
    rect.left += 33;
    _animation.insert(std::make_pair(ANIMATION_8, rect));
}

entityType Graphic::Ufo::getType() const
{
    return _type;
}
