/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Velocity.hpp
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include "IComponents.hpp"

namespace ECS {
    struct Velocity : public IComponents {
        Velocity() = default;
        Velocity(const int x, const int y);
        Velocity(const Velocity& other) = default;
        Velocity& operator=(const Velocity& other) = default;
        ~Velocity() = default;
        int _vx;
        int _vy;
    };
}

#endif /* !VELOCITY_HPP_ */
