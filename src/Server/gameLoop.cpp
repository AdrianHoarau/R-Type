/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** gameLoop.cpp
*/

#include "gameLoop.hpp"
#include "movementSystem.hpp"
#include "eventSystem.hpp"
#include "routineSystem.hpp"
#include "winSystem.hpp"
#include "Zipper.hpp"
#include "monsterSystem.hpp"
#include "bombSystem.hpp"
#include "Bomb.hpp"
#include "collisionSystem.hpp"
#include <iostream>

gameLoop::gameLoop() : _end(std::make_shared<bool>())
{
}

void gameLoop::registerComponents()
{
    _engine.registerComponent<ECS::Position>(ECS::POSITION);
    _engine.registerComponent<ECS::Velocity>(ECS::VELOCITY);
    _engine.registerComponent<ECS::Player>(ECS::PLAYER);
    _engine.registerComponent<ECS::entityDetails>(ECS::ENTITY_DETAILS);
    _engine.registerComponent<ECS::Life>(ECS::LIFE);
    _engine.registerComponent<ECS::Bomb>(ECS::BOMB);
    _engine.registerComponent<ECS::Dimensions>(ECS::DIMENSIONS);

}

void gameLoop::registerSystems(std::vector<clientPtr>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players, const socketPtr& socket, const std::shared_ptr<Buffer>& buffer, const std::string& libPath)
{
    _engine.registerSystem<ECS::routineSystem>(socket, clients, players);
    _engine.registerSystem<ECS::eventSystem>(buffer);
    _engine.registerSystem<ECS::winSystem>(_end);
    _engine.registerSystem<ECS::monsterSystem>(libPath);
    _engine.registerSystem<ECS::collisionSystem>();
    _engine.registerSystem<ECS::bombSystem>();
    _engine.registerSystem<ECS::movementSystem>();
}

void gameLoop::prepareGame(std::vector<clientPtr>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players, const socketPtr& socket, const std::shared_ptr<Buffer>& buffer, const std::string& libPath)
{
    registerComponents();
    registerSystems(clients, players, socket, buffer, libPath);
    createPlayers(clients, players);
}

void gameLoop::run(std::vector<clientPtr>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players, Lobby::lobbyState& lobbyState, const socketPtr& socket)
{
    static std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::milliseconds time;
    unsigned int playerIndex = 0;
    BinaryProtocol::Codec binCodec;

    while (*_end == false) {
        end = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (time >= std::chrono::milliseconds(30)) {
            update(time.count());
            start = std::chrono::system_clock::now();
        }
    }
    for (auto clt = clients.begin(); clt != clients.end() && playerIndex != players.size(); clt++, playerIndex++) {
        if (*players.at(playerIndex) != ECS::SPEC) {
            (*clt)->setState(Client::INLOBBY);
            socket->async_send_to(boost::asio::buffer(binCodec.serialize(binCodec.createPacket("135"))), (*clt)->getEndpoint(),
            boost::bind(&gameLoop::handleSend, this, "135",
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        } else {
            (*clt)->setState(Client::NONE);
            clients.erase(clt);
            players.erase(players.begin() + playerIndex);
            clt--;
            playerIndex--;
        }
    }
    lobbyState = Lobby::FREE;
}

void gameLoop::update(const float dt)
{
    for (auto& system : _engine.getSystems())
        system->update(dt, _engine);
}

void gameLoop::createPlayers(std::vector<clientPtr>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players)
{
    int x = 50;
    int y = 100;

    std::map<ECS::playerNumber, ECS::Dimensions> pDimensions = {
        {ECS::P1, ECS::Dimensions(33, 20)},
        {ECS::P2, ECS::Dimensions(33, 20)},
        {ECS::P3, ECS::Dimensions(33, 20)},
        {ECS::P4, ECS::Dimensions(33, 20)},
    };

    for (auto it : Zipper::zip(clients, players)) {
        auto ent = _engine.getNewEntity();
        unsigned int pNumber = *it.get<1>();
        _engine.addComponent(ent, ECS::Position(x, y), ECS::POSITION);
        _engine.addComponent(ent, pDimensions[*it.get<1>()], ECS::DIMENSIONS);
        _engine.addComponent(ent, ECS::Velocity(5, 5), ECS::VELOCITY);
        _engine.addComponent(ent, ECS::Player(*it.get<1>(), it.get<0>()->getUuid()), ECS::PLAYER);
        _engine.addComponent(ent, ECS::entityDetails(static_cast<entityType>(pNumber), animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
        _engine.addComponent(ent, ECS::Life(3), ECS::LIFE);
        y += 200;
    }
}

void gameLoop::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}