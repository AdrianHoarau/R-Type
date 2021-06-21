/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Lobby.hpp
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_


#include <memory>
#include <queue>
#include "Client.hpp"
#include "Buffer.hpp"

using clientPtr = std::shared_ptr<Client>;

class Lobby {
    public:
        enum lobbyState {
            FREE,
            INGAME,
        };
        Lobby(const std::string& name);
        Lobby(const Lobby& other) = default;
        Lobby& operator=(const Lobby& other) = default;
        void addClient(clientPtr& client);
        void removeClient(const clientPtr& client);
        void loadingLobby();
        bool isReadyToGo();
        void startGame(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer, const std::string& libPath);
        bool isRoomFull();
        std::string getName() const;
        bool hasClient(const clientPtr& client);
        std::vector<clientPtr>& getClients();
        std::vector<std::shared_ptr<ECS::playerNumber>>& getPlayers();
        ECS::playerNumber getPlayerNumber(const clientPtr& client);
        Lobby::lobbyState getState() const;
        std::queue<ECS::playerNumber>& getQueuePlayers();
        ~Lobby() = default;
    protected:
    private:
        void handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred);
        std::string _name;
        std::vector<std::shared_ptr<ECS::playerNumber>> _players;
        std::vector<clientPtr> _clients;
        std::queue<ECS::playerNumber> _available;
        lobbyState _state;
};

#endif /* !LOBBY_HPP_ */
