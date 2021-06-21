/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SpaceshipShoot
*/

#ifndef SPACESHIPSHOOT_HPP_
#define SPACESHIPSHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class SpaceshipShoot : public Graphic::Entity {
    public:
        SpaceshipShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        SpaceshipShoot(const SpaceshipShoot& other) = default;
        SpaceshipShoot& operator=(const SpaceshipShoot& other) = default;
        ~SpaceshipShoot() = default;
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !SPACESHIPSHOOT_HPP_ */
