/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Bomb.hpp
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "IComponents.hpp"

namespace ECS {
    struct Bomb : public IComponents {
        Bomb();
        Bomb(const Bomb& other) = default;
        Bomb& operator=(const Bomb& other) = default;
        ~Bomb() = default;
        float _dt;
    };
}


#endif /* !BOMB_HPP_ */
