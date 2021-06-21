/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Entity.cpp
*/

#include "Entity.hpp"


Graphic::Entity::Entity(int id, const entityType& type, bool bonus, const sf::Vector2f& pos, const animationState& anime) : _id(id), _type(type),
_pos(pos), _bonus(bonus), _scale({1, 1}), _currentAnimation(anime)
{

}

void Graphic::Entity::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Entity::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

void Graphic::Entity::setscale(const sf::Vector2f& scale)
{
    _scale = scale;
}

entityType Graphic::Entity::getType() const
{
    return (_type);
}

sf::Vector2f Graphic::Entity::getPos() const
{
    return (_pos);
}

int Graphic::Entity::getId() const
{
    return (_id);
}

animationState Graphic::Entity::getCurrentAnimation() const
{
    return  _currentAnimation;
}

void Graphic::Entity::setAnimation(const animationState& anime)
{
    _currentAnimation = anime;
}

sf::IntRect Graphic::Entity::getRectAnime(const animationState& anime)
{
    for (std::map <animationState, sf::IntRect>::iterator it = _animation.begin(); it != _animation.end(); it++) {
        if ((it)->first == anime)
            return (it)->second;
    }
    return sf::IntRect(-1, -1, -1, -1);
}