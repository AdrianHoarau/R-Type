/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Lobby.cpp
*/

#include "Lobby.hpp"
#include <thread>
#include <iostream>
#include "gameLoop.hpp"
#include "Zipper.hpp"
#include "BinaryProtocol.hpp"
#include "boost/uuid/uuid_io.hpp"

Lobby::Lobby(const std::string& name) : _name(name), _state(FREE)
{
    _available.push(ECS::P1);
    _available.push(ECS::P2);
    _available.push(ECS::P3);
    _available.push(ECS::P4);
}

void Lobby::addClient(clientPtr& client)
{
    _clients.push_back(client);
    _players.push_back(std::make_shared<ECS::playerNumber>(_available.front()));
    _available.pop();
}

bool Lobby::isReadyToGo()
{

    for (auto it : Zipper::zip(_clients, _players)) {
        if (it.get<0>()->getState() != Client::READY && *it.get<1>() != ECS::SPEC)
            return (false);
    }
    return (true);
}

void Lobby::startGame(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer, const std::string& libPath)
{
    auto game = std::make_shared<gameLoop>();
    unsigned int playerIndex = 0;
    _state = INGAME;
    std::string toSend("131");
    BinaryProtocol::Codec binCodec;

    for (auto clt = _clients.begin(); clt != _clients.end(); clt++, playerIndex++) {
        if (*_players.at(playerIndex) == ECS::SPEC) {
            _clients.erase(clt);
        } else {
            socket->async_send_to(boost::asio::buffer(binCodec.serialize(binCodec.createPacket(toSend))), (*clt)->getEndpoint(),
            boost::bind(&Lobby::handleSend, this, toSend,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
            (*clt)->setState(Client::INGAME);
        }
    }
    game->prepareGame(_clients, _players, socket, buffer, libPath);
    std::thread gameThread(&gameLoop::run, game, std::ref(_clients), std::ref(_players), std::ref(_state), std::ref(socket));
    gameThread.detach();
}

void Lobby::removeClient(const clientPtr& client)
{
    unsigned int playerIndex = 0;

    for (auto clt = _clients.begin(); clt != _clients.end(); clt++, playerIndex++) {
        if ((*clt)->getUuid() == client->getUuid()) {
            if ((*clt)->getState() == Client::INGAME) {
                _available.push(*_players.at(playerIndex));
                *_players.at(playerIndex) = ECS::SPEC;
            } else {
                _available.push(*_players.at(playerIndex));
                _clients.erase(clt);
                _players.erase(_players.begin() + playerIndex);
                break;
            }
        }
    }
}

bool Lobby::isRoomFull()
{
    if (_available.size() <= 0)
        return (true);
    return (false);
}

void Lobby::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}

bool Lobby::hasClient(const clientPtr& client)
{
    for (auto& clt : _clients)
        if (client == clt)
            return (true);
    return (false);
}

ECS::playerNumber Lobby::getPlayerNumber(const clientPtr& client)
{
    for (auto it : Zipper::zip(_clients, _players)) {
        if (it.get<0>() == client)
            return (*it.get<1>());
    }
    return (ECS::SPEC);
}

Lobby::lobbyState Lobby::getState() const
{
    return (_state);
}

std::string Lobby::getName() const
{
    return (_name);
}

std::vector<clientPtr>& Lobby::getClients()
{
    return (_clients);
}

std::vector<std::shared_ptr<ECS::playerNumber>>& Lobby::getPlayers()
{
    return (_players);
}

std::queue<ECS::playerNumber>& Lobby::getQueuePlayers()
{
    return (_available);
}