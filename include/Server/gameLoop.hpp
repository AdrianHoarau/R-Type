/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** gameLoop.hpp
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "ECSEngine.hpp"
#include "Client.hpp"
#include "Buffer.hpp"
#include "Lobby.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>

using clientPtr = std::shared_ptr<Client>;
using socketPtr = std::shared_ptr<boost::asio::ip::udp::socket>;

class gameLoop
{
public:
    gameLoop();
    gameLoop(const gameLoop&) = default;
    gameLoop& operator=(const gameLoop&) = default;
    void run(std::vector<clientPtr>&, std::vector<std::shared_ptr<ECS::playerNumber>>&, Lobby::lobbyState&, const socketPtr&);
    void prepareGame(std::vector<clientPtr>&, std::vector<std::shared_ptr<ECS::playerNumber>>&, const socketPtr&, const std::shared_ptr<Buffer>&, const std::string&);
    ~gameLoop() = default;
private:
    void createPlayers(std::vector<clientPtr>&, std::vector<std::shared_ptr<ECS::playerNumber>>&);
    void update(const float);
    void handleSend(const std::string&, const boost::system::error_code&, std::size_t);
    void registerComponents();
    void registerSystems(std::vector<clientPtr>&, std::vector<std::shared_ptr<ECS::playerNumber>>&, const socketPtr&, const std::shared_ptr<Buffer>&, const std::string&);
    ECS::ECSEngine _engine;
    std::shared_ptr<Buffer> _buffer;
    std::shared_ptr<bool> _end;
};


#endif /* !GAMELOOP_HPP_ */
