/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** IEntity.hpp
*/


#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "entityType.hpp"

namespace Graphic {

class IEntity {
    public:
        virtual ~IEntity() = default;
        virtual void update(const sf::Vector2f& pos) = 0;
        virtual void update(int x, int y) = 0;
        virtual entityType getType()const = 0;
    protected:
    private:
};
}
#endif