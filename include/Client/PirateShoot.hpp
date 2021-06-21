/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PirateShoot
*/

#ifndef PIRATESHOOT_HPP_
#define PIRATESHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class PirateShoot : public Graphic::Entity {
    public:
        PirateShoot(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        PirateShoot(const PirateShoot& other) = default;
        PirateShoot& operator=(const PirateShoot& other) = default;
        ~PirateShoot() = default;
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !PIRATESHOOT_HPP_ */
