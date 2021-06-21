/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AlienShoot
*/

#ifndef ALIENSHOOT_HPP_
#define ALIENSHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class AlienShoot : public Graphic::Entity {
    public:
        AlienShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        AlienShoot(const AlienShoot& other) = default;
        AlienShoot& operator=(const AlienShoot& other) = default;
        ~AlienShoot() = default;
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !ALIENSHOOT_HPP_ */
