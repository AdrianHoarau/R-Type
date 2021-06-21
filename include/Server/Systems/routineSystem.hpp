/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** routineSystem.hpp
*/

#ifndef ROUTINESYSTEM_HPP_
#define ROUTINESYSTEM_HPP_

#include "ASystem.hpp"
#include "Client.hpp"
#include "Position.hpp"
#include "entityDetails.hpp"
#include "BinaryProtocol.hpp"

namespace ECS {
    class routineSystem : public ASystem {
    public:
        routineSystem(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, std::vector<std::shared_ptr<Client>>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players);
        routineSystem(const routineSystem& other) = default;
        routineSystem& operator=(const routineSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        ~routineSystem() = default;
    private:
        void sendUpdates(const Entity ent, const entityDetails& details, const Position& position, ECS::ECSEngine& engine);
        void handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred);
        std::shared_ptr<boost::asio::ip::udp::socket> _socket;
        std::vector<std::shared_ptr<Client>> _clients;
        std::vector<std::shared_ptr<ECS::playerNumber>> _players;
        BinaryProtocol::Codec _binCodec;
    };
}

#endif /* !ROUTINESYSTEM_HPP_ */
