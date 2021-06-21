/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "IComponents.hpp"
#include <boost/uuid/uuid.hpp>

namespace ECS {
    enum currentMovement {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        NONE,
    };
    enum playerNumber {
        P1,
        P2,
        P3,
        P4,
        SPEC,
    };
    struct Player : public IComponents {
        Player() = default;
        Player(const playerNumber player, const boost::uuids::uuid& uuid);
        Player(const Player& other) = default;
        Player& operator=(const Player& other) = default;
        ~Player() = default;
        playerNumber _player;
        currentMovement _direction;
        boost::uuids::uuid _uuid;
    };
}

#endif /* !PLAYER_HPP_ */
