/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** bomb
*/

#include "Bomb.hpp"

Graphic::Bomb::Bomb(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) :
Graphic::Entity(id, BOMB, bonus, test, anime)
{
    sf::IntRect rect(0, 0, 36, 30);

    _animation.insert(std::make_pair(ANIMATION_0, rect));
    rect.left = 36;
    _animation.insert(std::make_pair(ANIMATION_1, rect));
    rect.left = 36;
    _animation.insert(std::make_pair(ANIMATION_2, rect));
    rect.left = 36;
    _animation.insert(std::make_pair(ANIMATION_3, rect));
    rect.left = 36;
    _animation.insert(std::make_pair(ANIMATION_4, rect));
    rect.left = 36;
    _animation.insert(std::make_pair(ANIMATION_5, rect));
}

entityType Graphic::Bomb::getType() const
{
    return _type;
}