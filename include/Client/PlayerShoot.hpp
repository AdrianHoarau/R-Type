/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PlayerShoot
*/

#ifndef PLAYERSHOOT_HPP_
#define PLAYERSHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class PlayerShoot : public Graphic::Entity {
    public:
        PlayerShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        PlayerShoot(const PlayerShoot& other) = default;
        PlayerShoot& operator=(const PlayerShoot& other) = default;
        ~PlayerShoot() = default;
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !PLAYERSHOOT_HPP_ */
