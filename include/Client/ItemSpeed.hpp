/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** itemSpeed.hpp
*/

#ifndef _ITEMSPEED_HPP_
#define _ITEMSPEED_HPP_

#include "Entity.hpp"

namespace Graphic {
class ItemSpeed : public Graphic::Entity {
    public:
        ItemSpeed(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        ItemSpeed(const ItemSpeed& other) = default;
        ItemSpeed& operator=(const ItemSpeed& other) = default;
        ~ItemSpeed() = default;
        entityType getType()const;
    private:
    protected:
};
}

#endif