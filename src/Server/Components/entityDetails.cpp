/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** entityDetails.cpp
*/

#include "entityDetails.hpp"

ECS::entityDetails::entityDetails(const entityType type, const animationState state) : _type(type), _state(state), _toUpdate(true)
{
}