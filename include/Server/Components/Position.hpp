/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Position.hpp
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "IComponents.hpp"

namespace ECS {
    struct Position : public IComponents {
        Position() = default;
        Position(const int x, const int y);
        Position(const Position& other) = default;
        Position& operator=(const Position& other) = default;
        ~Position() = default;
        int _x;
        int _y;
    };
}

#endif /* !POSITION_HPP_ */
