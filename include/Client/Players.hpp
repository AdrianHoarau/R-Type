/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Players.hpp
*/

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_

#include "entityType.hpp"

class Players
{
public:
    enum State
    {
        ACTIVE,
        OFF,
        READY
    };
public:
    Players(const entityType& type, const State& state = OFF);
    Players(const Players& other) = default;
    Players& operator=(const Players& other) = default;
    ~Players() = default;
    void setState(const State&);
    State getState()const;
    entityType getType()const;

private:
    entityType _type;
    State _state;
};

#endif