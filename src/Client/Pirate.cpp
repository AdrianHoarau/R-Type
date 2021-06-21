/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Pirate
*/

#include "Pirate.hpp"
#include <iostream>

Graphic::Pirate::Pirate(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, PIRATE, bonus, test, anime)
{
    sf::IntRect rect(1, 0, 33, 34);

    _animation.insert(std::make_pair(ANIMATION_0, rect));
    rect.left = 34;
    _animation.insert(std::make_pair(ANIMATION_1, rect));
    rect.left = 67;
    _animation.insert(std::make_pair(ANIMATION_2, rect));
    rect.left = 100;
    _animation.insert(std::make_pair(ANIMATION_3, rect));
    rect.left = 133;
    _animation.insert(std::make_pair(ANIMATION_4, rect));
    rect.left = 166;
    _animation.insert(std::make_pair(ANIMATION_5, rect));

}

entityType Graphic::Pirate::getType() const
{
    return _type;
}
