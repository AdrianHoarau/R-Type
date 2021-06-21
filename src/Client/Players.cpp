/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Players.cpp
*/

#include "Players.hpp"

Players::Players(const entityType& type, const State& state) : _type(type), _state(state)
{
}

void Players::setState(const State& state)
{
    _state = state;
}

entityType Players::getType()const
{
    return (_type);
}

Players::State Players::getState()const
{
    return (_state);
}