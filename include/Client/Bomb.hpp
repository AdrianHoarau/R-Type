/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** bomb.hpp
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Entity.hpp"

namespace Graphic {
class Bomb : public Graphic::Entity {
    public:
        Bomb(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        Bomb(const Bomb& other) = default;
        Bomb& operator=(const Bomb& other) = default;
        ~Bomb() = default;
        entityType getType()const;
    private:
    protected:
};
}

#endif