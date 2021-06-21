/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Pirate
*/

#ifndef PIRATE_HPP_
#define PIRATE_HPP_

#include "Entity.hpp"

namespace Graphic {
class Pirate : public Graphic::Entity{
    public:
        Pirate(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        Pirate(const Pirate& other) = default;
        Pirate& operator=(const Pirate& other) = default;
        ~Pirate() = default;
        entityType getType()const;
    private:
    protected:
};
}
#endif /* !PIRATE_HPP_ */
