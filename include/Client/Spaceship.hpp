/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Spaceship
*/

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "Entity.hpp"

namespace Graphic {
class Spaceship : public Graphic::Entity {
    public:
        Spaceship(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        Spaceship(const Spaceship& other) = default;
        Spaceship& operator=(const Spaceship& other) = default;
        ~Spaceship() = default;
        entityType getType()const;
    private:
    protected:
};
}
#endif /* !SPACESHIP_HPP_ */
