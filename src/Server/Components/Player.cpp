/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.cpp
*/

#include "Player.hpp"

ECS::Player::Player(const ECS::playerNumber player, const boost::uuids::uuid& uuid) : _player(player), _direction(ECS::NONE), _uuid(uuid)
{
}
